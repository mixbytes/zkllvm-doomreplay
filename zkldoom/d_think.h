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
//  MapObj data. Map Objects or mobjs are actors, entities,
//  thinker, take-your-pick... anything that moves, acts, or
//  suffers state changes of more or less violent nature.
//


#ifndef __D_THINK__
#define __D_THINK__

#include <stddef.h>

//
// Experimental stuff.
// To compile this as "ANSI C with classes"
//  we will need to handle the various
//  action functions cleanly.
//
typedef  void (*actionf_v)();
typedef  void (*actionf_p1)( void* );
typedef  void (*actionf_p2)( void*, void* );

typedef union
{
  actionf_v	acv;
  actionf_p1	acp1;
  actionf_p2	acp2;

} actionf_t;





// Historically, "think_t" is yet another
//  function pointer to a routine to handle
//  an actor.
typedef actionf_t  think_t;


// Doubly linked list of actors.
typedef struct thinker_s
{
    struct thinker_s*	prev;
    struct thinker_s*	next;
    // CCCCCCCCCCCCCCCCCCCCCCCCCCC - remove funcptrs
    think_t		function;
    int func_id;
    
} thinker_t;

#define F_FUNC_NULL NULL
#define F_FUNC_DEAD -1
#define F_FUNC_ZERO 0

#define F_T_MoveFloor 1
#define F_T_PlatRaise 2
#define F_T_FireFlicker 3
#define F_T_LightFlash 4
#define F_T_StrobeFlash 5
#define F_T_Glow 6
#define F_P_MobjThinker 7
#define F_T_VerticalDoor 8
#define F_T_MoveCeiling 9


void dispatch_thinker_func(int action, void * ptr);

#endif
