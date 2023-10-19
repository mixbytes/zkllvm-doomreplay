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
//	Game completion, final screen animation.
//


// Functions.
#include "deh_main.h"
#include "i_system.h"
#include "i_swap.h"
#include "z_zone.h"
#include "v_video.h"
#include "w_wad.h"
#include "s_sound.h"

// Data.
#include "d_main.h"
#include "dstrings.h"
#include "sounds.h"

#include "doomstat.h"
#include "r_state.h"

void F_StartFinale (void)
{
}

boolean F_Responder (event_t *event)
{
    return false;
}


//
// F_Ticker
//
void F_Ticker (void)
{
}



//
// F_TextWrite
//

// #include "hu_stuff.h"
// extern	patch_t *hu_font[HU_FONTSIZE];


void F_TextWrite (void)
{
}

//
// Final DOOM 2 animation
// Casting by id Software.
//   in order of appearance
//

//
// F_StartCast
//
void F_StartCast (void)
{
}


//
// F_CastTicker
//
void F_CastTicker (void)
{
}


//
// F_CastResponder
//

boolean F_CastResponder (event_t* ev)
{
}


void F_CastPrint (char* text)
{

}


//
// F_CastDrawer
//

void F_CastDrawer (void)
{
}


//
// F_DrawPatchCol
//
void
F_DrawPatchCol
( int		x,
  patch_t*	patch,
  int		col )
{
}


//
// F_BunnyScroll
//
void F_BunnyScroll (void)
{
}

static void F_ArtScreenDrawer(void)
{
}

//
// F_Drawer
//
void F_Drawer (void)
{
}


