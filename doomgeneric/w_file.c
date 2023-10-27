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

// reading form sharded wad file (split to arrays of SHARD_SIZE)
unsigned int W_Read(wad_file_t *wad, unsigned int offset,
              void *buffer, unsigned int buffer_len)
{
    unsigned int shard_num = 0;
    unsigned int byte_index = 0;
    for (int i = 0; i < buffer_len; i++) {
        shard_num = (offset + i) / SHARD_SIZE;
        byte_index = offset + i - (shard_num * SHARD_SIZE); // instead of (offset + i) % SHARD_SIZE
        ((unsigned char *)buffer)[i] = wad_contents[shard_num][byte_index];
    }

    return buffer_len;
}

