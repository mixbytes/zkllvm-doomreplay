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


#include "doomtype.h"

#define DEFAULT_RAM 6 /* MiB */
#define MIN_RAM     6  /* MiB */


static byte *AutoAllocMemory(int *size, int default_ram, int min_ram)
{
    byte *zonemem;

    // Allocate the zone memory.  This loop tries progressively smaller
    // zone sizes until a size is found that can be allocated.
    // If we used the -mb command line parameter, only the parameter
    // provided is accepted.

    zonemem = 0;

    while (zonemem == 0)
    {
        // We need a reasonable minimum amount of RAM to start.

        if (default_ram < min_ram)
        {
            return 0;
        }

        // Try to allocate the zone memory.

        *size = default_ram * 1024 * 1024;

        zonemem = malloc(*size);

        // Failed to allocate?  Reduce zone size until we reach a size
        // that is acceptable.

        if (zonemem == 0)
        {
            default_ram -= 1;
        }
    }

    return zonemem;
}



byte *I_ZoneBase (int *size)
{
    *size = DEFAULT_RAM * 1024 * 1024;
    return malloc(*size);
    
    // AAAAAAAAAAAAAAAAAAAAA
    // byte *zonemem;
    // int min_ram, default_ram;
    // int p;
    
    // default_ram = DEFAULT_RAM;
    // min_ram = MIN_RAM;
    // zonemem = AutoAllocMemory(size, default_ram, min_ram);
    
    //printf("zone memory: %p, %x allocated for zone\n", 
    //       zonemem, *size);

    // return zonemem;
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

void I_Error (char *error, ...)
{
}

boolean I_GetMemoryValue(unsigned int offset, void *value, int size)
{
}

