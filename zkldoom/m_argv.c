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


//#include <stdlib.h>

#include "doomtype.h"


//
// M_CheckParm
// Checks for the given parameter
// in the program's command line arguments.
// Returns the argument number (1 to argc-1)
// or 0 if not present
//

int M_CheckParmWithArgs(char *check, int num_args)
{
    // AAAAAAAAAAAAAAAAAAAAA remove any params, remove strcasecmp() as string function
    return 0;
}

//
// M_ParmExists
//
// Returns true if the given parameter exists in the program's command
// line arguments, false if not.
//

boolean M_ParmExists(char *check)
{
    return 0;
    // return M_CheckParm(check) != 0;
}

int M_CheckParm(char *check)
{
    return 0;
    //return M_CheckParmWithArgs(check, 0);
}

#define MAXARGVS        100

//
// Find a Response File
//

void M_FindResponseFile(void)
{
}

