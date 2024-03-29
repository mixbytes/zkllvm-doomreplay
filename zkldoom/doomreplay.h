#ifndef DOOM_REPLAY_H
#define DOOM_REPLAY_H

typedef unsigned char dr_keys_t[32];

typedef enum {
    dr_key_escape = 0,
    dr_key_enter,
    dr_key_left,
    dr_key_right,
    dr_key_up,
    dr_key_down,
    dr_key_alt,
    dr_key_shift,
    dr_key_use,
    dr_key_fire,
    dr_key_tab,
    dr_key_yes,
    dr_key_no,
    dr_key_strafe_left,
    dr_key_strafe_right,
    dr_key_0,
    dr_key_1,
    dr_key_2,
    dr_key_3,
    dr_key_4,
    dr_key_5,
    dr_key_6,
    dr_key_7,
    dr_key_8,
    dr_key_9,
    // careful with new "dr_key_SKIP" and filling all pressed keys (uses dr_key_COUNT) in z_main.c
    dr_key_SKIP,
    dr_key_COUNT,
} dr_keys_e;

typedef struct __attribute__((packed)) {
    dr_keys_t pressed;
} frame_data_t;

typedef struct __attribute__((packed)) {
    int frame_start;
    int len;
    char buf[32];
} username_data_t;

typedef struct __attribute__((packed)) {
    int n_frames;
    int n_usernames;
    int n_start;
    int n_record;
    int n_freeze;
    int framerate;
    int render_frame;
    int render_input;
    int render_username;

    frame_data_t    * frames;
    username_data_t * usernames;

    const char * fname_output;
} replay_data_t;

void DR_Init        (replay_data_t replay_data);
int  DR_NeedRender  (int f);
void DR_ProcessInput();
void DR_UpdateTime  (void);

#endif //DOOM_REPLAY_H
