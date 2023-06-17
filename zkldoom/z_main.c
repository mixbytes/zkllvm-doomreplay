//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 2005-2014 Simon Howard
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//	Main program, simply calls D_DoomMain high level loop.
//

#include <stdio.h>
#include <stdlib.h>                                                                                                                    

#include <strings.h> // for strlen

#include "m_argv.h"
#include "doomreplay.h"


/*[[circuit]] int main_circuit(int a) {
    int b = a + 10;
    return b;
}
*/




unsigned long prepare_inputs(const char * input, unsigned char *input_codes) {
    // string with inputs like 
    // ",,,,,,,,,,,,,,,,,,,,,,,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,r,r,r,r,f,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,f,f,f,f,f,f";
    unsigned long n_inputs = strlen(input);
    for (int i = 0; i < n_inputs; ++i) {
            switch (input[i]) {
                case ',': input_codes[i] = dr_key_SKIP; break;
                case 'x': input_codes[i] = dr_key_escape; break;
                case 'e': input_codes[i] = dr_key_enter; break;
                case 'l': input_codes[i] = dr_key_left; break;
                case 'r': input_codes[i] = dr_key_right; break;
                case 'u': input_codes[i] = dr_key_up; break;
                case 'd': input_codes[i] = dr_key_down; break;
                case 'a': input_codes[i] = dr_key_alt; break;
                case 's': input_codes[i] = dr_key_shift; break;
                case 'p': input_codes[i] = dr_key_use; break;
                case 'f': input_codes[i] = dr_key_fire; break;
                case 't': input_codes[i] = dr_key_tab; break;
                case 'y': input_codes[i] = dr_key_yes; break;
                case 'n': input_codes[i] = dr_key_no; break;
                case '<': input_codes[i] = dr_key_strafe_left; break;
                case '>': input_codes[i] = dr_key_strafe_right; break;
                case '0': input_codes[i] = dr_key_0; break;
                case '1': input_codes[i] = dr_key_1; break;
                case '2': input_codes[i] = dr_key_2; break;
                case '3': input_codes[i] = dr_key_3; break;
                case '4': input_codes[i] = dr_key_4; break;
                case '5': input_codes[i] = dr_key_5; break;
                case '6': input_codes[i] = dr_key_6; break;
                case '7': input_codes[i] = dr_key_7; break;
                case '8': input_codes[i] = dr_key_8; break;
                case '9': input_codes[i] = dr_key_9; break;
            };
    }
    return n_inputs;
}


// ALL GLOBAL STATE HERE

// All globals from "*.h" headers combined
#include "z_main.h"





// AAAA Globals from d_main.c

// will be moved to function inputs
const char *USER_INPUT = ",,,,,,,,,,,,,,,,,,,,,,,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,r,r,r,r,f,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,f,f,f,f,f,f";

static replay_data_t replay_data;

// Location where savegames are stored
char *          savegamedir;

// location of IWAD and WAD files
char *          iwadfile;

boolean		devparm;	// started game with -devparm
boolean         nomonsters;	// checkparm of -nomonsters
boolean         respawnparm;	// checkparm of -respawn
boolean         fastparm;	// checkparm of -fast

extern  boolean	inhelpscreens;

skill_t		startskill;
int             startepisode;
int		startmap;
boolean		autostart;
int             startloadgame;

boolean		advancedemo;

// Store demo, do not accept any inputs
boolean         storedemo;

// "BFG Edition" version of doom2.wad does not include TITLEPIC.
boolean         bfgedition;


char		wadfile[1024];		// primary wad file
char		mapdir[1024];           // directory of development maps


// If true, the main game loop has started.
// boolean         main_loop_started = false;

// int             show_endoom = 1;
















int main(int argc, char **argv)
{

    replay_data.framerate = 35;
    replay_data.n_start = 0;
    replay_data.n_record = 10*replay_data.framerate;
    replay_data.n_freeze = 0;
    replay_data.render_frame = 1;
    replay_data.render_input = 0;
    replay_data.render_username = 0;
    replay_data.n_frames = 1;
    
    unsigned char *input_codes = malloc(sizeof(unsigned char) * strlen(USER_INPUT));
    unsigned long n_inputs = prepare_inputs(USER_INPUT, input_codes);
    
    for (int i = 0; i < n_inputs; ++i) {
        switch (input_codes[i]) {
            case dr_key_SKIP: {
                        ++replay_data.n_frames;
                      } break;
        };
    }

    printf("[DEBUG] target n_frames: %d\n", replay_data.n_frames);
    
    replay_data.frames    = malloc(replay_data.n_frames*sizeof(frame_data_t));
    replay_data.usernames = malloc(replay_data.n_usernames*sizeof(username_data_t));

    for (int f = 0; f < replay_data.n_frames; ++f) {
        for (int i = 0; i < dr_key_COUNT; ++i) {
            replay_data.frames[f].pressed[i] = 0;
        }
    }

    int cur_frame    = 0;

    for (int i = 0; i < n_inputs; ++i) {
        frame_data_t    * frame    = replay_data.frames + cur_frame;
        if (input_codes[i] == dr_key_SKIP) {
            ++cur_frame;
        } else {
            frame->pressed[input_codes[i]] = 1;
        }
    }

    // AAAAAAA DR_Init() moved
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

    printf("\n\n======= DOOM REPLAY ===========\n");
    printf("Frames to simulate: %6d (%g seconds)\n", g_replay_data.n_frames, (float)(g_replay_data.n_frames)/TICRATE);
    printf("Start frame:        %6d (%g seconds)\n", g_replay_data.n_start,  (float)(g_replay_data.n_start)/TICRATE);
    printf("Frames to record:   %6d (%g seconds)\n", g_replay_data.n_record, (float)(g_replay_data.n_record)/TICRATE);
    printf("Framerate:          %6d\n", g_replay_data.framerate);
    printf("===============================\n");

    printf("[DEBUG] DR_init completed\n");
    // DR_Init(replay_data);

    // dg_Create();
	DG_ScreenBuffer = malloc(DOOMGENERIC_RESX * DOOMGENERIC_RESY * 4);
    printf("[DEBUG] dg_Create completed\n");



    // DoomMain();
    
    printf("[DEBUG] Z_Init: Init zone memory allocation daemon. \n");
    Z_Init ();

    nomonsters = 0;
    respawnparm = 0;
    fastparm = 0;
    devparm = 0;
	deathmatch = 0;
    
    modifiedgame = false;
    
    W_AddFile("mocked doom1.wad");
    exit(0);
    // Generate the WAD hash table.  Speed things up a bit.
    // HZ CCCCCCCCCCC check
    //W_GenerateHashTable();

    I_InitTimer();

    // get skill / episode / map from parms
    startskill = sk_medium;
    startepisode = 1;
    startmap = 1;
    autostart = false;

    timelimit = 0;

    // Not loading a game
    startloadgame = -1;

    R_Init ();

    P_Init ();

    D_CheckNetGame ();

    ST_Init ();

    // [AAAA] autostart
    autostart = 1;
    G_InitNew (startskill, startepisode, startmap);

    D_DoomLoop ();  // never returns



    return 0;
}




