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
//	WAD I/O functions.
//

#include <stddef.h>
#include "config.h"

#include "doomtype.h"
#include "m_argv.h"

#include "w_file.h"
#include "../doom1_wad_hardcopy.h"

unsigned int W_Read(wad_file_t *wad, unsigned int offset,
              void *buffer, unsigned int buffer_len)
{
    int i = 0;
    for (i = 0; i < buffer_len; i++) {
        ((char *)buffer)[i] = wad_contents[offset + i];
    }

    return buffer_len;
}

