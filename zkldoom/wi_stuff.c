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
//	Intermission screens.
//

//#include <stddef.h>

#include "z_zone.h"

#include "m_misc.h"
#include "m_random.h"

#include "deh_main.h"
#include "i_swap.h"
#include "i_system.h"

#include "w_wad.h"

#include "g_game.h"

#include "r_local.h"
#include "s_sound.h"

#include "doomstat.h"

// Data.
#include "sounds.h"

// Needs access to LFB.
#include "v_video.h"

#include "wi_stuff.h"

// slam background
void WI_slamBackground(void)
{
}

// The ticker is used to detect keys
//  because of timing issues in netgames.
boolean WI_Responder(event_t* ev)
{
    return false;
}


// Draws "<Levelname> Finished!"
void WI_drawLF(void)
{
}

// Draws "Entering <LevelName>"
void WI_drawEL(void)
{
}

void
WI_drawOnLnode
( int		n,
  patch_t*	c[] )
{
}



void WI_initAnimatedBack(void)
{
}

void WI_updateAnimatedBack(void)
{
}

void WI_drawAnimatedBack(void)
{
}

//
// Draws a number.
// If digits > 0, then use that many digits minimum,
//  otherwise only use as many as necessary.
// Returns new x position.
//

int
WI_drawNum
( int		x,
  int		y,
  int		n,
  int		digits )
{
    return 0;
}

void
WI_drawPercent
( int		x,
  int		y,
  int		p )
{
}

//
// Display level completion time and par,
//  or "sucks" message if overflow.
//
void
WI_drawTime
( int		x,
  int		y,
  int		t )
{
}


void WI_End(void)
{
}

void WI_initNoState(void)
{
}

void WI_updateNoState(void)
{
}
void WI_initShowNextLoc(void)
{
}

void WI_updateShowNextLoc(void)
{
}

void WI_drawShowNextLoc(void)
{
}

void WI_drawNoState(void)
{
}

int WI_fragSum(int playernum)
{
    return 0;
}
void WI_initDeathmatchStats(void)
{
}
void WI_updateDeathmatchStats(void)
{
}
void WI_drawDeathmatchStats(void)
{
}
void WI_initNetgameStats(void)
{
}
void WI_updateNetgameStats(void)
{
}
void WI_drawNetgameStats(void)
{
}

void WI_initStats(void)
{
}

void WI_updateStats(void){
}

void WI_drawStats(void)
{
}

void WI_checkForAccelerate(void)
{
}



// Updates stuff each tick
void WI_Ticker(void)
{
}

// Common load/unload function.  Iterates over all the graphics
// lumps to be loaded/unloaded into memory.

void WI_loadData(void)
{
}

void WI_unloadData(void)
{
}

void WI_Drawer (void)
{
}


void WI_initVariables(wbstartstruct_t* wbstartstruct)
{
}

void WI_Start(wbstartstruct_t* wbstartstruct)
{
}
