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

//#include "doomtype.h"
//#include "i_system.h"
#include "m_argv.h"


#include <stdlib.h>                                                                                                                    
#include <string.h>                                                                                                                    
#include "doomreplay.h"
//
// D_DoomMain()
// Not a globally visible function, just included for source reference,
// calls all startup code, parses command line options.
//

void D_DoomMain (void);

void M_FindResponseFile(void);

void dg_Create();

/*
[[circuit]] int main_circuit(int a) {
    int b = a + 10;
    return b;
}
*/

int main(int argc, char **argv)
{
    // save arguments

    myargc = argc;
    myargv = argv;


    replay_data_t replay_data;

    int pidx_input     = M_CheckParmWithArgs("-input",     1);
    int pidx_nstart    = M_CheckParmWithArgs("-nstart",    1);
    int pidx_nrecord   = M_CheckParmWithArgs("-nrecord",   1);
    int pidx_nfreeze   = M_CheckParmWithArgs("-nfreeze",   1);

    if (!pidx_input) {
        fprintf(stderr, "Input file must be provided via '-input'\n");
        return -1;
    }

    replay_data.fname_output = "zkltest.mp4";

    // framerate
    replay_data.framerate = 35;

    // start recording after n frames
    replay_data.n_start = -1;

    // n frames to record
    replay_data.n_record = 10*replay_data.framerate;

    // n frames to freeze the last frame
    replay_data.n_freeze = 0;

    // render the current frame on the screen ?
    replay_data.render_frame = 1;

    replay_data.render_input = 0;
    
    replay_data.render_username = 0;

    replay_data.n_frames = 1;
    replay_data.n_usernames = 1;
    
    const char * param_input = myargv[pidx_input + 1];

    FILE *f = fopen(param_input, "rb");
    if (!f) {
        fprintf(stderr, "Cannot read input file '%s'\n", param_input);
        return -2;
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

    char *input = malloc(fsize + 1);
    fread(input, 1, fsize, f);
    fclose(f);


    int in_username = 0;
    for (int i = 0; i < fsize; ++i) {
        switch (input[i]) {
            case ',': {
                          if (in_username == 0) {
                              ++replay_data.n_frames;
                          }
                      } break;
        };
    }

    if (replay_data.n_start == -1) {
        replay_data.n_start = replay_data.n_frames - replay_data.n_record;
    }

    replay_data.frames    = malloc(replay_data.n_frames*sizeof(frame_data_t));
    replay_data.usernames = malloc(replay_data.n_usernames*sizeof(username_data_t));

    for (int f = 0; f < replay_data.n_frames; ++f) {
        for (int i = 0; i < dr_key_COUNT; ++i) {
            replay_data.frames[f].pressed[i] = 0;
        }
    }

    for (int i = 0; i < replay_data.n_usernames; ++i) {
        replay_data.usernames[i].len    = 0;
        replay_data.usernames[i].buf[0] = 0;
    }

    int cur_frame    = 0;
    int cur_username = 0;

    for (int i = 0; i < fsize; ++i) {
        frame_data_t    * frame    = replay_data.frames + cur_frame;
        username_data_t * username = replay_data.usernames + cur_username;

            switch (input[i]) {
                case '#': {
                              in_username = 1;
                              cur_username++;
                              replay_data.usernames[cur_username].frame_start = cur_frame;
                          } break;
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

    DR_Init(replay_data);

	dg_Create();

	D_DoomMain ();

    return 0;
}

