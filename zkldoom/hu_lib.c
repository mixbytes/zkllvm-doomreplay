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
// DESCRIPTION:  heads-up text and input code
//


// #include <ctype.h>

#include "doomdef.h"
#include "doomkeys.h"

#include "v_video.h"
#include "i_swap.h"

#include "hu_lib.h"
#include "r_local.h"
#include "r_draw.h"

// boolean : whether the screen is always erased
#define noterased viewwindowx

void HUlib_init(void)
{
}

void HUlib_clearTextLine(hu_textline_t* t)
{
}

void
HUlib_initTextLine
( hu_textline_t*	t,
  int			x,
  int			y,
  patch_t**		f,
  int			sc )
{
}

boolean
HUlib_addCharToTextLine
( hu_textline_t*	t,
  char			ch )
{
}

boolean HUlib_delCharFromTextLine(hu_textline_t* t)
{
}

void
HUlib_drawTextLine
( hu_textline_t*	l,
  boolean		drawcursor )
{

}


// sorta called by HU_Erase and just better darn get things straight
void HUlib_eraseTextLine(hu_textline_t* l)
{
}

void
HUlib_initSText
( hu_stext_t*	s,
  int		x,
  int		y,
  int		h,
  patch_t**	font,
  int		startchar,
  boolean*	on )
{
}

void HUlib_addLineToSText(hu_stext_t* s)
{
}

void
HUlib_addMessageToSText
( hu_stext_t*	s,
  char*		prefix,
  char*		msg )
{
}

void HUlib_drawSText(hu_stext_t* s)
{
}

void HUlib_eraseSText(hu_stext_t* s)
{
}

void
HUlib_initIText
( hu_itext_t*	it,
  int		x,
  int		y,
  patch_t**	font,
  int		startchar,
  boolean*	on )
{
}


// The following deletion routines adhere to the left margin restriction
void HUlib_delCharFromIText(hu_itext_t* it)
{
}

void HUlib_eraseLineFromIText(hu_itext_t* it)
{
}

// Resets left margin as well
void HUlib_resetIText(hu_itext_t* it)
{
}

void
HUlib_addPrefixToIText
( hu_itext_t*	it,
  char*		str )
{
}

// wrapper function for handling general keyed input.
// returns true if it ate the key
boolean
HUlib_keyInIText
( hu_itext_t*	it,
  unsigned char ch )
{
    return true; // ate the key
}

void HUlib_drawIText(hu_itext_t* it)
{
}

void HUlib_eraseIText(hu_itext_t* it)
{
}

