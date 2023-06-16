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

#include <stdio.h>
#include <strings.h>
//#include "doomtype.h"
//#include "i_system.h"
#include "m_argv.h"


#include <stdlib.h>                                                                                                                    
#include "doomreplay.h"


/*[[circuit]] int main_circuit(int a) {
    int b = a + 10;
    return b;
}
*/


char *USER_INPUT = ",,,,,,,,,,,,,,,,,,,,,,,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,r,r,r,r,f,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,u,f,f,f,f,f,f";


unsigned long prepare_inputs(char * input, unsigned char *input_codes) {
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



int main(int argc, char **argv)
{
    replay_data_t replay_data;

    replay_data.framerate = 35;
    replay_data.n_start = 0;
    replay_data.n_record = 10*replay_data.framerate;
    replay_data.n_freeze = 0;
    replay_data.render_frame = 1;
    replay_data.render_input = 0;
    replay_data.render_username = 0;
    replay_data.n_frames = 1;
    
    unsigned char *input_codes = malloc(sizeof(unsigned char) * strlen(USER_INPUT));
    unsigned int n_inputs = prepare_inputs(USER_INPUT, input_codes);
    
    for (int i = 0; i < n_inputs; ++i) {
        switch (input_codes[i]) {
            case dr_key_SKIP: {
                        ++replay_data.n_frames;
                      } break;
        };
    }

    printf("[DEBUG] target n_frames: %d %d\n", replay_data.n_frames);
    
    replay_data.frames    = malloc(replay_data.n_frames*sizeof(frame_data_t));
    replay_data.usernames = malloc(replay_data.n_usernames*sizeof(username_data_t));

    for (int f = 0; f < replay_data.n_frames; ++f) {
        for (int i = 0; i < dr_key_COUNT; ++i) {
            replay_data.frames[f].pressed[i] = 0;
        }
    }

    int cur_frame    = 0;
    int cur_username = 0;

    for (int i = 0; i < n_inputs; ++i) {
        frame_data_t    * frame    = replay_data.frames + cur_frame;
        if (input_codes[i] == dr_key_SKIP) {
            ++cur_frame;
        } else {
            frame->pressed[input_codes[i]] = 1;
        }
    }

    DR_Init(replay_data);

	dg_Create();

	D_DoomMain ();

    return 0;
}

