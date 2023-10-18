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
//
// DESCRIPTION:  the automap code
//


#include "deh_main.h"

#include "z_zone.h"
#include "doomkeys.h"
#include "doomdef.h"
#include "st_stuff.h"
#include "p_local.h"
#include "w_wad.h"

#include "m_cheat.h"
#include "m_controls.h"
#include "m_misc.h"
#include "i_system.h"

// Needs access to LFB.
#include "v_video.h"

// State.
#include "doomstat.h"
#include "r_state.h"

// Data.
#include "dstrings.h"

#include "am_map.h"

boolean    	automapactive = false;


typedef struct
{
    int x, y;
} fpoint_t;

typedef struct
{
    fpoint_t a, b;
} fline_t;

typedef struct
{
    fixed_t		x,y;
} mpoint_t;

typedef struct
{
    mpoint_t a, b;
} mline_t;

typedef struct
{
    fixed_t slp, islp;
} islope_t;

// Calculates the slope and slope according to the x-axis of a line
// segment in map coordinates (with the upright y-axis n' all) so
// that it can be used with the brain-dead drawing stuff.


void
AM_getIslope
( mline_t*	ml,
  islope_t*	is )
{
}

//
//
//
void AM_activateNewScale(void)
{
}

//
//
//
void AM_saveScaleAndLoc(void)
{
}

//
//
//
void AM_restoreScaleAndLoc(void)
{
}

//
// adds a marker at the current location
//
void AM_addMark(void)
{
}

//
// Determines bounding box of all vertices,
// sets global variables controlling zoom range.
//
void AM_findMinMaxBoundaries(void)
{
}


//
//
//
void AM_changeWindowLoc(void)
{
}


//
//
//
void AM_initVariables(void)
{
}

//
// 
//
void AM_loadPics(void)
{
}

void AM_unloadPics(void)
{
}

void AM_clearMarks(void)
{
}

//
// should be called at the start of every level
// right now, i figure it out myself
//
void AM_LevelInit(void)
{
}




//
//
//
void AM_Stop (void)
{
}

//
//
//
void AM_Start (void)
{
}

//
// set the window scale to the maximum size
//
void AM_minOutWindowScale(void)
{
}

//
// set the window scale to the minimum size
//
void AM_maxOutWindowScale(void)
{
}


//
// Handle events (user inputs) in automap mode
//
boolean
AM_Responder
( event_t*	ev )
{
    return false;
}


//
// Zooming
//
void AM_changeWindowScale(void)
{
}


//
//
//
void AM_doFollowPlayer(void)
{
}

//
//
//
void AM_updateLightLev(void)
{
}


//
// Updates on Game Tick
//
void AM_Ticker (void)
{
}


//
// Clear automap frame buffer.
//
void AM_clearFB(int color)
{
}


//
// Automap clipping of lines.
//
// Based on Cohen-Sutherland clipping algorithm but with a slightly
// faster reject and precalculated slopes.  If the speed is needed,
// use a hash algorithm to handle  the common cases.
//
boolean
AM_clipMline
( mline_t*	ml,
  fline_t*	fl )
{
    return false;
}
#undef DOOUTCODE


//
// Classic Bresenham w/ whatever optimizations needed for speed
//
void
AM_drawFline
( fline_t*	fl,
  int		color )
{
}


//
// Clip lines, draw visible part sof lines.
//
void
AM_drawMline
( mline_t*	ml,
  int		color )
{
}



//
// Draws flat (floor/ceiling tile) aligned grid lines.
//
void AM_drawGrid(int color)
{
}

//
// Determines visible lines, draws them.
// This is LineDef based, not LineSeg based.
//
void AM_drawWalls(void)
{
}


//
// Rotation in 2D.
// Used to rotate player arrow line character.
//
void
AM_rotate
( fixed_t*	x,
  fixed_t*	y,
  angle_t	a )
{
}

void
AM_drawLineCharacter
( mline_t*	lineguy,
  int		lineguylines,
  fixed_t	scale,
  angle_t	angle,
  int		color,
  fixed_t	x,
  fixed_t	y )
{
}

void AM_drawPlayers(void)
{
}

void
AM_drawThings
( int	colors,
  int 	colorrange)
{
}

void AM_drawMarks(void)
{
}

void AM_drawCrosshair(int color)
{
}

void AM_Drawer (void)
{
}
