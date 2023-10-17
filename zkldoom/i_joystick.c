//
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
//       SDL Joystick code.
//

#ifdef ORIGCODE
#include "SDL.h"
#include "SDL_joystick.h"
#endif

#include <stdlib.h>
#include <string.h>

#include "doomtype.h"
#include "d_event.h"
#include "i_joystick.h"
#include "i_system.h"

#include "m_config.h"
#include "m_misc.h"

// When an axis is within the dead zone, it is set to zero.
// This is 5% of the full range:

#define DEAD_ZONE (32768 / 3)

#ifdef ORIGCODE
static SDL_Joystick *joystick = NULL;
#endif

// Configuration variables:

// Standard default.cfg Joystick enable/disable

static int usejoystick = 0;

// Joystick to use, as an SDL joystick index:

static int joystick_index = -1;

// Which joystick axis to use for horizontal movement, and whether to
// invert the direction:

static int joystick_x_axis = 0;
static int joystick_x_invert = 0;

// Which joystick axis to use for vertical movement, and whether to
// invert the direction:

static int joystick_y_axis = 1;
static int joystick_y_invert = 0;

// Which joystick axis to use for strafing?

static int joystick_strafe_axis = -1;
static int joystick_strafe_invert = 0;

// Virtual to physical button joystick button mapping. By default this
// is a straight mapping.
static int joystick_physical_buttons[NUM_VIRTUAL_BUTTONS] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9
};

void I_ShutdownJoystick(void)
{
}

#ifdef ORIGCODE
static boolean IsValidAxis(int axis)
{
    return true;
}
#endif

void I_InitJoystick(void)
{
}

#ifdef ORIGCODE
static boolean IsAxisButton(int physbutton)
{
    return false;
}

// Get the state of the given virtual button.

static int ReadButtonState(int vbutton)
{
        return 0;
}

// Get a bitmask of all currently-pressed buttons

static int GetButtonsState(void)
{
    return 0;
}

// Read the state of an axis, inverting if necessary.

static int GetAxisState(int axis, int invert)
{
    return 0;
}
#endif

void I_UpdateJoystick(void)
{
}

void I_BindJoystickVariables(void)
{
}

