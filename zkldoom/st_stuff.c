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
//	Status bar code.
//	Does the face/direction indicator animatin.
//	Does palette indicators as well (red pain/berserk, bright pickup)
//

#include <stddef.h>

#include "i_system.h"
#include "i_video.h"
#include "z_zone.h"
#include "m_misc.h"
#include "m_random.h"
#include "w_wad.h"

#include "deh_main.h"
#include "deh_misc.h"
#include "doomdef.h"
#include "doomkeys.h"

#include "g_game.h"

#include "st_stuff.h"
#include "st_lib.h"
#include "r_local.h"

#include "p_local.h"
#include "p_inter.h"

#include "am_map.h"
#include "m_cheat.h"

#include "s_sound.h"

// Needs access to LFB.
#include "v_video.h"

// State.
#include "doomstat.h"

// Data.
#include "dstrings.h"
#include "sounds.h"

//
// STATUS BAR CODE
//
void ST_Stop(void);

void ST_refreshBackground(void)
{
}


// Respond to keyboard input events,
//  intercept cheats.
boolean
ST_Responder (event_t* ev)
{
  return false; // AAAAAAAAAAAAAAAA
}


//
// This is a not-very-pretty routine which handles
//  the face states and their timing.
// the precedence of expressions is:
//  dead > evil grin > turned head > straight ahead
//
void ST_updateFaceWidget(void)
{
}

void ST_updateWidgets(void)
{
}

void ST_Ticker (void)
{
}

void ST_doPaletteStuff(void)
{
}

void ST_drawWidgets(boolean refresh)
{
}

void ST_doRefresh(void)
{
}

void ST_diffDraw(void)
{
}

void ST_Drawer (boolean fullscreen, boolean refresh)
{
}

//typedef void (*load_callback_t)(char *lumpname, patch_t **variable); 

// Iterates through all graphics to be loaded or unloaded, along with
// the variable they use, invoking the specified callback function.

//static void ST_loadUnloadGraphics(load_callback_t callback)
//{
//}

void ST_loadGraphics(void)
{
}

void ST_loadData(void)
{
}

void ST_unloadGraphics(void)
{
}

void ST_unloadData(void)
{
}

void ST_initData(void)
{
}



void ST_createWidgets(void)
{
}

void ST_Start (void)
{
}

void ST_Stop (void)
{
}

void ST_Init (void)
{
}

