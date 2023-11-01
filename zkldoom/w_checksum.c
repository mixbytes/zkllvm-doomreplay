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
//       Generate a checksum of the WAD directory.
//

#include <stdlib.h>

#include "m_misc.h"
#include "sha1.h"
#include "w_checksum.h"
#include "w_wad.h"

static int num_open_wadfiles = 0;

static int GetFileNumber()
{
    return 1;
}

static void ChecksumAddLump(sha1_context_t *sha1_context, lumpinfo_t *lump)
{
    char buf[9];
    for (int i=0; i< 9; i++) {
        buf[i] = lump->name[i];
    }
    buf[9] = 0;
    // M_StringCopy(buf, lump->name, sizeof(buf));
    SHA1_UpdateString(sha1_context, buf);
}

void W_Checksum(sha1_digest_t digest)
{
    sha1_context_t sha1_context;
    unsigned int i;

    SHA1_Init(&sha1_context);

    num_open_wadfiles = 0;

    // Go through each entry in the WAD directory, adding information
    // about each entry to the SHA1 hash.

    for (i=0; i<numlumps; ++i)
    {
        ChecksumAddLump(&sha1_context, &lumpinfo[i]);
    }
    
    SHA1_Final(digest, &sha1_context);
}

