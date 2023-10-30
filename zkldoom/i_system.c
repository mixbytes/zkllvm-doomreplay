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
//

#include <stdlib.h>

#include "doomtype.h"

#define DEFAULT_RAM 6 /* MiB */
#define MIN_RAM     6  /* MiB */


byte *I_ZoneBase (int *size)
{
    *size = DEFAULT_RAM * 1024 * 1024;
    return malloc(*size);
}

// 
// I_ConsoleStdout
//
// Returns true if stdout is a real console, false if it is a file
//

boolean I_ConsoleStdout(void)
{
    return 0;
}


//
// I_Error
//

// void I_Error (char *error, ...)
//{
//}

boolean I_GetMemoryValue(unsigned int offset, void *value, int size)
{
}

