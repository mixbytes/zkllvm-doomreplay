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

#ifndef __ZKLLVM__
#include <stdio.h>
#include <stdlib.h>
#endif


#include "doomtype.h"
#include "m_argv.h"

#include "doomreplay.h"
#include "doomgeneric.h"

#include "doom.h"

void D_DoomMain (__uint128_t n);
void dg_Create();


__attribute__((circuit)) int z_main(__uint128_t n)
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
    unsigned int n_inputs = 160;
    replay_data.n_frames = 160;

    replay_data.frames    = malloc(replay_data.n_frames*sizeof(frame_data_t));

    for (int f = 0; f < replay_data.n_frames; ++f) {
        for (int i = 0; i < dr_key_COUNT; ++i) {
            replay_data.frames[f].pressed[i] = 0;
        }
    }

    int cur_frame    = 0;
    for (int i = 0; i < n_inputs; ++i) {
        ++cur_frame;
    }

    replay_data.n_record = cur_frame;

    DR_Init(replay_data);

    dg_Create();
    
    D_DoomMain (n);
    return cur_frame;
}

void printInputs(__uint128_t value1) {
#ifndef __ZKLLVM__
    printf("[ ");
    printf("{\"field\": %" PRIu64 "%" PRIu64 "}", (uint64_t)(value1 >> 64), (uint64_t)value1);
    printf(" ]\n");
#endif
}


int main(int argc, char **argv) {

    // printInputs(64);
    //return 0;
    int a = z_main(64);
#ifndef __ZKLLVM__
    printf("z_main out: %d\n", a);
#endif
    return 0;
}











/*


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
