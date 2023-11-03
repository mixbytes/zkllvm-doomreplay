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

