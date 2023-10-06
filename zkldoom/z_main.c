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


void D_DoomMain (__uint128_t tics_inputs[64]);
void dg_Create();

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




__attribute__((circuit)) int z_main(int n_inputs)
{
    replay_data_t replay_data;
    
    replay_data.framerate = 35;
    replay_data.n_start = 0;
    replay_data.n_freeze = 0;
    replay_data.render_frame = 1;
    replay_data.render_input = 0;
    replay_data.render_username = 0;
    replay_data.n_frames = 1;
    
    // AAAAAAAAAAAAAAAAAAAAAA
    n_inputs = 160;
    replay_data.n_frames = 160;

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
        ++cur_frame;
            /*
            switch ((char)user_input[i]) {
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
            */
    }

    replay_data.n_record = cur_frame;

    DR_Init(replay_data);

    dg_Create();

    // AAAAAAAAAAAAAAAA
    __uint128_t tics_inputs[64];


/*INP*/ tics_inputs[0] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x10\x00\x00\x00";
/*INP*/ tics_inputs[1] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x10\x00\x00\x00";
/*INP*/ tics_inputs[2] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x10\x00\x00\x00";
/*INP*/ tics_inputs[3] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x10\x00\x00\x00";
/*INP*/ tics_inputs[4] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x10\x00\x00\x00";
/*INP*/ tics_inputs[5] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x10\x00\x00\x00";
/*INP*/ tics_inputs[6] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x10\x00\x00\x00";
/*INP*/ tics_inputs[7] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x10\x00\x00\x00";
/*INP*/ tics_inputs[8] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x10\x00\x00\x00";
/*INP*/ tics_inputs[9] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x10\x00\x00\x00";
/*INP*/ tics_inputs[10] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x10\x00\x00\x00";
/*INP*/ tics_inputs[11] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x10\x00\x00\x00";
/*INP*/ tics_inputs[12] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x10\x00\x00\x00";
/*INP*/ tics_inputs[13] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x10\x00\x00\x00";
/*INP*/ tics_inputs[14] = *(__uint128_t*) "\x00\x00\x00\x00\x00\x00\x00\x00\xad\x00\x00\x00\x11\x00\x00\x00";
/*INP*/ tics_inputs[15] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x10\x00\x00\x00";
/*INP*/ tics_inputs[16] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x38\x00\x00\x00";
/*INP*/ tics_inputs[17] = *(__uint128_t*) "\xac\x00\x00\x00\xac\x00\x00\x00\xac\x00\x00\x00\x40\x00\x00\x00";
/*INP*/ tics_inputs[18] = *(__uint128_t*) "\xac\x00\x00\x00\xac\x00\x00\x00\xac\x00\x00\x00\x78\x00\x00\x00";
/*INP*/ tics_inputs[19] = *(__uint128_t*) "\xac\x00\x00\x00\xac\x00\x00\x00\xac\x00\x00\x00\x80\x00\x00\x00";
/*INP*/ tics_inputs[20] = *(__uint128_t*) "\xac\x00\x00\x00\xac\x00\x00\x00\xac\x00\x00\x00\x88\x00\x00\x00";
/*INP*/ tics_inputs[21] = *(__uint128_t*) "\x00\x00\x00\x00\x00\x00\x00\x00\xad\x00\x00\x00\x91\x00\x00\x00";
/*INP*/ tics_inputs[22] = *(__uint128_t*) "\xac\x00\x00\x00\xac\x00\x00\x00\xac\x00\x00\x00\x90\x00\x00\x00";
/*INP*/ tics_inputs[23] = *(__uint128_t*) "\xac\x00\x00\x00\xac\x00\x00\x00\xac\x00\x00\x00\x98\x00\x00\x00";
/*INP*/ tics_inputs[24] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\xa0\x00\x00\x00";
/*INP*/ tics_inputs[25] = *(__uint128_t*) "\x00\x00\x00\x00\x00\x00\x00\x00\xac\x00\x00\x00\xc9\x00\x00\x00";
/*INP*/ tics_inputs[26] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\xd8\x00\x00\x00";
/*INP*/ tics_inputs[27] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\xe0\x00\x00\x00";
/*INP*/ tics_inputs[28] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\xe8\x00\x00\x00";
/*INP*/ tics_inputs[29] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\xf0\x00\x00\x00";
/*INP*/ tics_inputs[30] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\xf8\x00\x00\x00";
/*INP*/ tics_inputs[31] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x00\x01\x00\x00";
/*INP*/ tics_inputs[32] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x08\x01\x00\x00";
/*INP*/ tics_inputs[33] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x10\x01\x00\x00";
/*INP*/ tics_inputs[34] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\x18\x01\x00\x00";
/*INP*/ tics_inputs[35] = *(__uint128_t*) "\xac\x00\x00\x00\xac\x00\x00\x00\xac\x00\x00\x00\x20\x01\x00\x00";
/*INP*/ tics_inputs[36] = *(__uint128_t*) "\x00\x00\x00\x00\x00\x00\x00\x00\xac\x00\x00\x00\x49\x01\x00\x00";
/*INP*/ tics_inputs[37] = *(__uint128_t*) "\xae\x00\x00\x00\xae\x00\x00\x00\xae\x00\x00\x00\x78\x01\x00\x00";
/*INP*/ tics_inputs[38] = *(__uint128_t*) "\xae\x00\x00\x00\xae\x00\x00\x00\xae\x00\x00\x00\xb0\x01\x00\x00";
/*INP*/ tics_inputs[39] = *(__uint128_t*) "\x00\x00\x00\x00\x00\x00\x00\x00\xad\x00\x00\x00\xb1\x01\x00\x00";
/*INP*/ tics_inputs[40] = *(__uint128_t*) "\xae\x00\x00\x00\xae\x00\x00\x00\xae\x00\x00\x00\xb8\x01\x00\x00";
/*INP*/ tics_inputs[41] = *(__uint128_t*) "\xae\x00\x00\x00\xae\x00\x00\x00\xae\x00\x00\x00\xc0\x01\x00\x00";
/*INP*/ tics_inputs[42] = *(__uint128_t*) "\xae\x00\x00\x00\xae\x00\x00\x00\xae\x00\x00\x00\xc8\x01\x00\x00";
/*INP*/ tics_inputs[43] = *(__uint128_t*) "\xae\x00\x00\x00\xae\x00\x00\x00\xae\x00\x00\x00\xd0\x01\x00\x00";
/*INP*/ tics_inputs[44] = *(__uint128_t*) "\x20\x00\x00\x00\x20\x00\x00\x00\x20\x00\x00\x00\xd8\x01\x00\x00";
/*INP*/ tics_inputs[45] = *(__uint128_t*) "\x00\x00\x00\x00\x00\x00\x00\x00\x20\x00\x00\x00\xf9\x01\x00\x00";
/*INP*/ tics_inputs[46] = *(__uint128_t*) "\x20\x00\x00\x00\x20\x00\x00\x00\x20\x00\x00\x00\x28\x02\x00\x00";
/*INP*/ tics_inputs[47] = *(__uint128_t*) "\x00\x00\x00\x00\x00\x00\x00\x00\xae\x00\x00\x00\x31\x02\x00\x00";
/*INP*/ tics_inputs[48] = *(__uint128_t*) "\x00\x00\x00\x00\x00\x00\x00\x00\x20\x00\x00\x00\x51\x02\x00\x00";
/*INP*/ tics_inputs[49] = *(__uint128_t*) "\xac\x00\x00\x00\xac\x00\x00\x00\xac\x00\x00\x00\x68\x02\x00\x00";
/*INP*/ tics_inputs[50] = *(__uint128_t*) "\x20\x00\x00\x00\x20\x00\x00\x00\x20\x00\x00\x00\x68\x02\x00\x00";
/*INP*/ tics_inputs[51] = *(__uint128_t*) "\x00\x00\x00\x00\x00\x00\x00\x00\x20\x00\x00\x00\x89\x02\x00\x00";
/*INP*/ tics_inputs[52] = *(__uint128_t*) "\x20\x00\x00\x00\x20\x00\x00\x00\x20\x00\x00\x00\xa0\x02\x00\x00";
/*INP*/ tics_inputs[53] = *(__uint128_t*) "\x00\x00\x00\x00\x00\x00\x00\x00\xac\x00\x00\x00\xa9\x02\x00\x00";
/*INP*/ tics_inputs[54] = *(__uint128_t*) "\x00\x00\x00\x00\x00\x00\x00\x00\x20\x00\x00\x00\xc1\x02\x00\x00";
/*INP*/ tics_inputs[55] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\xe0\x02\x00\x00";
/*INP*/ tics_inputs[56] = *(__uint128_t*) "\x20\x00\x00\x00\x20\x00\x00\x00\x20\x00\x00\x00\xe0\x02\x00\x00";
/*INP*/ tics_inputs[57] = *(__uint128_t*) "\x00\x00\x00\x00\x00\x00\x00\x00\x20\x00\x00\x00\xf1\x02\x00\x00";
/*INP*/ tics_inputs[58] = *(__uint128_t*) "\xae\x00\x00\x00\xae\x00\x00\x00\xae\x00\x00\x00\x08\x03\x00\x00";
/*INP*/ tics_inputs[59] = *(__uint128_t*) "\x00\x00\x00\x00\x00\x00\x00\x00\xad\x00\x00\x00\x11\x03\x00\x00";
/*INP*/ tics_inputs[60] = *(__uint128_t*) "\xae\x00\x00\x00\xae\x00\x00\x00\xae\x00\x00\x00\x38\x03\x00\x00";
/*INP*/ tics_inputs[61] = *(__uint128_t*) "\xae\x00\x00\x00\xae\x00\x00\x00\xae\x00\x00\x00\x48\x03\x00\x00";
/*INP*/ tics_inputs[62] = *(__uint128_t*) "\x00\x00\x00\x00\x00\x00\x00\x00\xae\x00\x00\x00\x49\x03\x00\x00";
/*INP*/ tics_inputs[63] = *(__uint128_t*) "\xad\x00\x00\x00\xad\x00\x00\x00\xad\x00\x00\x00\xf8\x03\x00\x00";






	D_DoomMain (tics_inputs);
    return cur_frame;
}

int main(int argc, char **argv) {
    int a = z_main(120);
    return 0;
}

/*


#include <stdio.h>
const unsigned int INT_MAX=0xffffffff;
#define VVV 42

__attribute__((circuit)) unsigned int Dijkstra(unsigned int st, unsigned int end) {

     //int GR[VVV][VVV] = {
     //   {0, 1, 4, 0, 2, 0},
     //   {0, 0, 0, 9, 0, 0},
     //   {4, 0, 0, 7, 0, 0},
     //   {0, 9, 7, 0, 0, 2},
     //   {0, 0, 0, 0, 0, 8},
     //   {0, 0, 0, 0, 0, 0}
     //};

    // fill graph with values
    unsigned int GR[VVV][VVV];
    unsigned int randstate = 0;

    // #define VVV 8
    for(int i = 0; i < VVV; i++) {
        for (int j = i; j < VVV; j++) {
            // randstate = 1664525 * randstate + 1013904223; // common values used in linear congruential generators
            randstate = 3 * randstate + 5; // test
            if (i==j) {
                GR[i][j] = 0;
            } else {
                GR[i][j] = randstate;// % 99;
                GR[j][i] = GR[i][j];
            }
        }
    }
    for(int i = 0; i < VVV; i++) {
        // 1st node is connected to each others onlyt through node 0
        if (i != 0) {
            GR[1][i] = 0; 
            GR[i][1] = 0;
        }
    }


#ifndef __ZKLLVM__
    for(int i = 0; i < VVV; i++) {
        for (int j = 0; j < VVV; j++) {
            printf("\t %03d", GR[i][j]);
        }
        printf("\n");
    }
#endif

    // calculate "distance" between each node with another 
    unsigned int distance[VVV], count, index, i, u;
    unsigned int visited[VVV];
    for (i=0; i<VVV; i++) {
        distance[i]=INT_MAX;
        visited[i]=0;
    }
    distance[st]=0;
    for (count=0; count<VVV-1; count++) {
        int min=INT_MAX;
        for (i=0; i<VVV; i++)
            if (!visited[i] && distance[i]<=min) {
                min=distance[i]; index=i;
            }
        u=index;
        visited[u]=1;

        for (i=0; i<VVV; i++)
            if (!visited[i] && GR[u][i] && distance[u]!=INT_MAX && distance[u] + GR[u][i] < distance[i])
                distance[i]=distance[u]+GR[u][i];
    }
#ifndef __ZKLLVM__
    printf("Cost from start %d to each other:\n", st);
    for (i=0; i<VVV; i++) {
        if (distance[i]!=INT_MAX) {
            printf("\tfrom %d to %d: %d\n", st, i, distance[i]);
        } else {
            printf("\tfrom %d to %d: (blocked)\n", st, i);
        }
    }
#endif
    return distance[end];
}

int main(int argc, char **argv) {
    unsigned int start = 2;
    unsigned int end = 1;
    int distance = Dijkstra(start, end);
    printf("Distance from %d to %d: %d\n\n", start, end, distance);
    return 0;
}


*/
