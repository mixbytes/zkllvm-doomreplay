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

//#include "config.h"

#include "doomtype.h"
//#include <stdio.h>
#include "m_argv.h"


#include <stdlib.h>                                                                                                                    
#include "doomreplay.h"
#include "doomgeneric.h"

#include "doom.h"

void D_DoomMain (void);                                                                                                                
void dg_Create();

//#define USER_INPUT_LENGTH 118
//char USER_INPUT[118] = ",,,,,,,,,,,,,,,,,,,,,,,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,r,r,r,r,f,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,f,f,f,f,f,f";

char USER_INPUT[] = 
"u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,"
"u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,"
"r,r,r,r,r,r,r,r,r,r,r,r,"
"su,su,su,su,su,su,su,su,su,su,su,su,su,su,su,su"
"su,su,su,su,su,su,su,su,su,su,su,su,su,su,su,su"
"su,su,su,su,su,su,su,su,su,su,su,su,su,su,su,su"
"su,su,su,su,su,su,su,su,su,su,su,su,su,su,su,su"
"su,su,su,su,su,su,su,su,su,su,su,su,su,su,su,su"
"su,su,su,su,su,su,su,su,su,su,su,su,su,su,su,su"
"r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,"
"p,"
"r,r,r,r,r,"
"su,su,su,su,su,su,su,su,su,su,su,su,su,su,su,su"
"su,su,su,su,su,su,su,su,su,su,su,su,su,su,su,su"
"l,l,l,l,l,l,l,l"
"su,su,su,su,su,su,su,su,su,su,su,su,su,su,su,su"
"su,su,su,su,su,su,su,su,su,su,su,su,su"
",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"
"sd,sd,sd,sd,sd"
"r,r,r,r"
"f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f"
"f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f"
"f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f"
"f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f"
"f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f"
",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"
",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"
",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"
"sd,sd,sd,sd,sd,sd,sd,sd,sd,sd,sd,sd,sd,sd,sd,sd"
;

__attribute__((circuit)) int z_main(int n_inputs, int m)
{
    
    replay_data_t replay_data;

    replay_data.framerate = 35;
    replay_data.n_start = 0;
    replay_data.n_freeze = 0;
    replay_data.render_frame = 1;
    replay_data.render_input = 0;
    replay_data.render_username = 0;
    replay_data.n_frames = 1;

    for (int i = 0; i < n_inputs; i++) {
        if (USER_INPUT[i] == ',') {
            replay_data.n_frames++;
        }
    }
    
    replay_data.frames    = malloc(replay_data.n_frames*sizeof(frame_data_t));
    
    for (int f = 0; f < replay_data.n_frames; ++f) {
        for (int i = 0; i < dr_key_COUNT; ++i) {
            replay_data.frames[f].pressed[i] = 0;
        }
    }

    int cur_frame    = 0;
    int cur_username = 0;
    for (int i = 0; i < n_inputs; ++i) {
        frame_data_t    * frame    = replay_data.frames + cur_frame;

            switch (USER_INPUT[i]) {
                case ',': ++cur_frame;                             break;
                case 'x': frame->pressed[dr_key_escape]       = 1; break;
                case 'e': frame->pressed[dr_key_enter]        = 1; break;
                case 'l': frame->pressed[dr_key_left]         = 1; break;
                case 'r': frame->pressed[dr_key_right]        = 1; break;
                case 'u': frame->pressed[dr_key_up]           = 1; break;
                case 'd': frame->pressed[dr_key_down]         = 1; break;
                case 'a': frame->pressed[dr_key_alt]          = 1; break;
                case 's': frame->pressed[dr_key_shift]        = 1; break;
                case 'p': frame->pressed[dr_key_use]          = 1; break;
                case 'f': frame->pressed[dr_key_fire]         = 1; break;
                case 't': frame->pressed[dr_key_tab]          = 1; break;
                case 'y': frame->pressed[dr_key_yes]          = 1; break;
                case 'n': frame->pressed[dr_key_no]           = 1; break;
                case '<': frame->pressed[dr_key_strafe_left]  = 1; break;
                case '>': frame->pressed[dr_key_strafe_right] = 1; break;
                case '0': frame->pressed[dr_key_0]            = 1; break;
                case '1': frame->pressed[dr_key_1]            = 1; break;
                case '2': frame->pressed[dr_key_2]            = 1; break;
                case '3': frame->pressed[dr_key_3]            = 1; break;
                case '4': frame->pressed[dr_key_4]            = 1; break;
                case '5': frame->pressed[dr_key_5]            = 1; break;
                case '6': frame->pressed[dr_key_6]            = 1; break;
                case '7': frame->pressed[dr_key_7]            = 1; break;
                case '8': frame->pressed[dr_key_8]            = 1; break;
                case '9': frame->pressed[dr_key_9]            = 1; break;
            };
    }
    
    replay_data.n_record = cur_frame;

    DR_Init(replay_data);

    dg_Create();

	D_DoomMain ();

}



unsigned long prepare_inputs(char * input, unsigned char *input_codes) {
    // string with inputs like 
    // ",,,,,,,,,,,,,,,,,,,,,,,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,r,r,r,r,f,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,f,f,f,f,f,f";
    unsigned long n_inputs = sizeof(input);
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


int main(int argc, char **argv) {
    int a = z_main(sizeof(USER_INPUT),11);
    return 0;
}


