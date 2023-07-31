#include "doomkeys.h"
#include "doomgeneric.h"
#include "doomreplay.h"

#include "dr_font.h"

#include "i_timer.h"

#include <time.h>
#include <stdio.h>
// #include <unistd.h>
#include <string.h>

#include <stdbool.h>

#define KEYQUEUE_SIZE 16

static unsigned short s_KeyQueue[KEYQUEUE_SIZE];
static unsigned int   s_KeyQueueWriteIndex = 0;
static unsigned int   s_KeyQueueReadIndex  = 0;

static FILE * g_fp = NULL;

static clock_t g_t_start = 0;

static const int64_t g_dt    = 35000;
static const int64_t g_dt_gs = (g_dt/5)/TICRATE; // ensure at least 5 updates per frame

static int64_t g_time_gs     = 0; // current time
static int32_t g_frame_id    = 0; // frame index
static int32_t g_username_id = 0; // username index

static dr_keys_t g_pressed_last;
static dr_keys_t g_key_map;
static replay_data_t g_replay_data;

static void renderText(uint32_t * screen, const char * text, int xoffs, int yoffs, int ecol) {
    int n = strlen(text);
    if (n) {
        uint32_t col = 0x0000FF00;
        for (int i = 0; i < n; ++i) {
            for (int y = 0; y < FONT_SIZE_Y; ++y) {
                for (int x = 0; x < FONT_SIZE_X; ++x) {
                    col = kFontRaster[(int)text[i]][y*FONT_SIZE_X + x];
                    if (col) {
                        if (ecol == 0) col = col << 8; // green
                        if (ecol == 1) col = (((29*col)/255) << 16) | (((161*col)/255) << 8) | ((242*col)/255); // blue
                        screen[(yoffs + y)*DOOMGENERIC_RESX + (i*FONT_SIZE_X + xoffs + x)] = col;
                    }
                }
            }
        }
    }
}

static void addConvertedKeyToQueue(int pressed, unsigned char key) {
    unsigned short keyData = (pressed << 8) | key;

    s_KeyQueue[s_KeyQueueWriteIndex] = keyData;
    s_KeyQueueWriteIndex++;
    s_KeyQueueWriteIndex %= KEYQUEUE_SIZE;
}

void DR_Init(replay_data_t replay_data) {
    // __builtin_dump_struct(&replay_data, &printf);

    g_key_map[dr_key_escape      ] = KEY_ESCAPE;
    g_key_map[dr_key_enter       ] = KEY_ENTER;
    g_key_map[dr_key_left        ] = KEY_LEFTARROW;
    g_key_map[dr_key_right       ] = KEY_RIGHTARROW;
    g_key_map[dr_key_up          ] = KEY_UPARROW;
    g_key_map[dr_key_down        ] = KEY_DOWNARROW;
    g_key_map[dr_key_alt         ] = KEY_LALT;
    g_key_map[dr_key_shift       ] = KEY_RSHIFT;
    g_key_map[dr_key_use         ] = KEY_USE;
    g_key_map[dr_key_fire        ] = KEY_FIRE;
    g_key_map[dr_key_tab         ] = KEY_TAB;
    g_key_map[dr_key_yes         ] = 'y';
    g_key_map[dr_key_no          ] = 'n';
    g_key_map[dr_key_strafe_left ] = KEY_STRAFE_L;
    g_key_map[dr_key_strafe_right] = KEY_STRAFE_R;
    g_key_map[dr_key_0           ] = '0';
    g_key_map[dr_key_1           ] = '1';
    g_key_map[dr_key_2           ] = '2';
    g_key_map[dr_key_3           ] = '3';
    g_key_map[dr_key_4           ] = '4';
    g_key_map[dr_key_5           ] = '5';
    g_key_map[dr_key_6           ] = '6';
    g_key_map[dr_key_7           ] = '7';
    g_key_map[dr_key_8           ] = '8';
    g_key_map[dr_key_9           ] = '9';

    g_replay_data = replay_data;

    for (int i = 0; i < dr_key_COUNT; ++i) {
        g_pressed_last[i] = 0;
    }

   
#ifndef __ZKLLVM__        
    printf("\n\n======= DOOM REPLAY ===========\n");
    printf("Frames to simulate: %6d (%g seconds)\n", g_replay_data.n_frames, (float)(g_replay_data.n_frames)/TICRATE);
    printf("Start frame:        %6d (%g seconds)\n", g_replay_data.n_start,  (float)(g_replay_data.n_start)/TICRATE);
    printf("Frames to record:   %6d (%g seconds)\n", g_replay_data.n_record, (float)(g_replay_data.n_record)/TICRATE);
    printf("Framerate:          %6d\n", g_replay_data.framerate);
    printf("Render frame idx:   %6d\n", g_replay_data.render_frame);
    printf("Render input:       %6d\n", g_replay_data.render_input);
    printf("Render username:    %6d\n", g_replay_data.render_username);
    printf("===============================\n");
#endif
}

void DR_ProcessInput() {
    if (g_frame_id < g_replay_data.n_start + g_replay_data.n_record && g_frame_id < g_replay_data.n_frames) {
        for (int i = 0; i < dr_key_COUNT; ++i) {
           
            if (g_replay_data.frames[g_frame_id].pressed[i] != g_pressed_last[i]) {
                int pressed = g_pressed_last[i] ? 0 : 1;
                addConvertedKeyToQueue(pressed, g_key_map[i]);
            } else {
                int pressed = g_replay_data.frames[g_frame_id].pressed[i];
                if (pressed) addConvertedKeyToQueue(pressed, g_key_map[i]);
            }
        }

        memcpy(g_pressed_last, g_replay_data.frames[g_frame_id].pressed, sizeof(dr_keys_t));
    }
}

int DR_NeedRender(int f) {
    return g_frame_id >= g_replay_data.n_start - f;
}

void DR_UpdateTime() {
    g_time_gs += g_dt_gs;
}

void DG_DrawFrame() {

    // printf("frame = %d\n", g_frame_id);
    // printf("frame = %d, time = %d, x = %d, diff = %d\n",
    //       g_frame_id, g_time_gs/(g_dt/1000), g_time_gs/g_dt_gs, g_time_gs/g_dt_gs - g_frame_id);

    if (g_frame_id == 0) {
        g_t_start = clock();
    }

    g_frame_id++;

    if (g_frame_id >= g_replay_data.n_start + g_replay_data.n_record || g_frame_id >= g_replay_data.n_frames) {
#ifndef __ZKLLVM__        
        printf("Terminating ..\n");
#endif
        exit(0);
    }
    
    const int n_frames_stats = 1000;
    if (g_frame_id % n_frames_stats == 0) {
#ifndef __ZKLLVM__        
        printf("frame = %d, speed = %.2f frames/sec\n", g_frame_id, n_frames_stats/(((double)(clock() - g_t_start))/CLOCKS_PER_SEC));
#endif
        g_t_start = clock();
    }
}

void DG_SleepMs(uint32_t ms) {
    // noop
}

uint32_t DG_GetTicksMs() {
    return g_time_gs/(g_dt/1000);
}

int DG_GetKey(int* pressed, unsigned char* doomKey) {
    if (s_KeyQueueReadIndex == s_KeyQueueWriteIndex){
        //key queue is empty
        return 0;
    } else {
        unsigned short keyData = s_KeyQueue[s_KeyQueueReadIndex];
        s_KeyQueueReadIndex++;
        s_KeyQueueReadIndex %= KEYQUEUE_SIZE;

        *pressed = keyData >> 8;
        *doomKey = keyData & 0xFF;

        return 1;
    }

    return 0;
}

void DG_SetWindowTitle(const char * title) {}
