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
//	Handles WAD file header, directory, lump I/O.
//

#include <stdlib.h>

#ifndef __ZKLLVM__
#include <stdlib.h>
#include <string.h>
#endif

#include "doomtype.h"

#include "i_swap.h"
#include "i_system.h"
#include "i_video.h"
#include "m_misc.h"
#include "z_zone.h"

#include "w_wad.h"

//
// GLOBALS
//

// Location of each lump on disk.
lumpinfo_t **lumpinfo;
unsigned int numlumps = 0;

// Hash table for fast lookups
static lumpindex_t *lumphash;

// Variables for the reload hack: filename of the PWAD to reload, and the
// lumps from WADs before the reload file, so we can resent numlumps and
// load the file again.

//  AAAAAA static lumpinfo_t *reloadlumps = NULL;
//  AAAAAA static char *reloadname = NULL;
//  AAAAAA static int reloadlump = -1;



int own_strncasecmp( const char * s1, const char * s2, size_t n )
{
    while ( n && *s1 && ( *s1 == *s2 ) ) {
        ++s1; ++s2; --n;
    }
    if ( n == 0 ) {
        return 0;
    } else {
        return ( *(unsigned char *)s1 - *(unsigned char *)s2 );
    }
}

void own_strncpy( char* _dst, const char* _src, unsigned int _n )
{
   unsigned int i = 0;
   while(i++ != _n && (*_dst++ = *_src++));
}


// Hash function used for lump names.
unsigned int W_LumpNameHash(const char *s)
{
    // This is the djb2 string hash function, modded to work on strings
    // that have a maximum length of 8.

    unsigned int result = 5381;
    unsigned int i;

    for (i=0; i < 8 && s[i] != '\0'; ++i)
    {
        // result = ((result << 5) ^ result ) ^ toupper(s[i]); AAAAAAAAAAAAAAAAAAAA
        result = ((result << 5) ^ result ) ^ (s[i]);
    }

    return result;
}

//
// LUMP BASED ROUTINES.
//

//
// W_AddFile
// All files are optional, but at least one file must be
//  found (PWAD, if all required lumps are present).
// Files with a .wad extension are wadlink files
//  with multiple lumps.
// Other files are single lumps with the base filename
//  for the lump name.

#include "../zk_wad_hardcoded.h"

void W_AddFile (const char *filename)
{
    numlumps = ZK_NUMLUMPS;
    /*
    for (int i = 0; i < ZK_NUMLUMPS; ++i)
    {
        lumpinfo_t *lump_p = &(ZK_LUMPSTRUCTS[i]);
        printf("{.name = \"%s\", .position = %d, .size = %d, .next = %d}\n",                                                 
            lump_p->name, lump_p->position, lump_p->size, lump_p->next);   
        //lump_p->cache = &(ZK_LUMPBODIES[i]);
        //lumpinfo[i] = lump_p;//&ZK_LUMPSTRUCTS[i];
    }
    */

    /*
    wadinfo_t *header;
    lumpindex_t i;
    int length;
    int startlump;
    filelump_t *fileinfo;
    filelump_t *filerover;
    lumpinfo_t *filelumps;
    int numfilelumps;

	header = Z_Malloc(sizeof(wadinfo_t), PU_STATIC, 0);
    // WAD file
    W_Read(0, (unsigned char *)header, sizeof(wadinfo_t));

	header->numlumps = LONG(header->numlumps);

	header->infotableofs = LONG(header->infotableofs);
	length = header->numlumps*sizeof(filelump_t);

#ifndef __ZKLLVM__
    printf("Loading %d bytes of fileinfo\n", length);
#endif
	fileinfo = Z_Malloc(length, PU_STATIC, 0);

    W_Read(header->infotableofs, (unsigned char *)fileinfo, length);
	numfilelumps = header->numlumps;

    // Increase size of numlumps array to accomodate the new file.
    
    // AAAAAAAAAAAAAAA - fuck, calloc also initializes mem with zeroes (but it works in zkdoom)
    // filelumps = calloc(numfilelumps, sizeof(lumpinfo_t));
    unsigned int nsize = numfilelumps * sizeof(lumpinfo_t);
    filelumps = malloc(nsize);
    
    startlump = numlumps;
    numlumps += numfilelumps;
    // AAAAAAAAAAAAAAAAAAAAAAA
    // lumpinfo = I_Realloc(lumpinfo, numlumps * sizeof(lumpinfo_t *));
    lumpinfo = malloc(numlumps * sizeof(lumpinfo_t *));
    filerover = fileinfo;

    for (i = startlump; i < numlumps; ++i)
    {
        lumpinfo_t *lump_p = &filelumps[i - startlump];
        lump_p->position = LONG(filerover->filepos);
        lump_p->size = LONG(filerover->size);
        lump_p->cache = NULL;
        own_strncpy(lump_p->name, filerover->name, 8);
        lumpinfo[i] = lump_p;
        //printf("{.name = \"%s\", .position = %d, .size = %d, .next = 0}\n",                                                 
        //    filerover->name,filerover->filepos, filerover->size);   

        ++filerover;
    }

    Z_Free(fileinfo);

    if (lumphash != NULL)
    {
        Z_Free(lumphash);
        lumphash = NULL;
    }

    */
    return;
}


//
// W_CheckNumForName
// Returns -1 if name not found.
//

lumpindex_t W_CheckNumForName(const char *name)
{
    lumpindex_t i;
    // Do we have a hash table yet?

    if (lumphash != NULL)
    {
        int hash;

        // We do! Excellent.

        hash = W_LumpNameHash(name) % numlumps;
        for (i = lumphash[hash]; i != -1; i = ZK_LUMPSTRUCTS[i].next)
        {
            if (!own_strncasecmp(ZK_LUMPSTRUCTS[i].name, name, 8))
            {
                return i;
            }
        }
    }
    else
    {
        // We don't have a hash table generate yet. Linear search :-(
        //
        // scan backwards so patch lump files take precedence

        for (i = numlumps - 1; i >= 0; --i)
        {
            if (!own_strncasecmp(ZK_LUMPSTRUCTS[i].name, name, 8))
            {
                return i;
            }
        }
    }

    // TFB. Not found.

    return -1;
}




//
// W_GetNumForName
// Calls W_CheckNumForName, but bombs out if not found.
//
lumpindex_t W_GetNumForName(const char *name)
{
    lumpindex_t i;

    i = W_CheckNumForName (name);

    return i;
}


//
// W_LumpLength
// Returns the buffer size needed to load the given lump.
//
int W_LumpLength(lumpindex_t lump)
{
    return ZK_LUMPSTRUCTS[lump].size;
}



//
// W_ReadLump
// Loads the lump into the given buffer,
//  which must be >= W_LumpLength().
//
void W_ReadLump(lumpindex_t lump, void *dest)
{
    lumpinfo_t *l;
    l = &(ZK_LUMPSTRUCTS[lump]);
    for(int i =0; i< l->size; i++) {
        *(unsigned char *)(dest + i) = ZK_LUMPBODIES[lump][i];
    }
    //W_Read(l->position, (unsigned char *)dest, l->size);
}




//
// W_CacheLumpNum
//
// Load a lump into memory and return a pointer to a buffer containing
// the lump data.
//
// 'tag' is the type of zone memory buffer to allocate for the lump
// (usually PU_STATIC or PU_CACHE).  If the lump is loaded as 
// PU_STATIC, it should be released back using W_ReleaseLumpNum
// when no longer needed (do not use Z_ChangeTag).
//

void *W_CacheLumpNum(lumpindex_t lumpnum, int tag)
{
    // AAAAAAAAA  - same read, we don't have a cache
    lumpinfo_t *l;
    l = &(ZK_LUMPSTRUCTS[lumpnum]);
    byte *result = malloc(l->size);
    for(int i =0; i < l->size; i++) {
        *(unsigned char *)(result + i) = ZK_LUMPBODIES[lumpnum][i];
    }
    return result;

    /*
    byte *result;
    lumpinfo_t *lump;
    lump = lumpinfo[lumpnum];

    // Get the pointer to return.  If the lump is in a memory-mapped
    // file, we can just return a pointer to within the memory-mapped
    // region.  If the lump is in an ordinary file, we may already
    // have it cached; otherwise, load it into memory.

    if (lump->cache != NULL)
    {
        // Already cached, so just switch the zone tag.

        result = lump->cache;
        Z_ChangeTag(lump->cache, tag);
    }
    else
    {
        // Not yet loaded, so load it now

        lump->cache = Z_Malloc(W_LumpLength(lumpnum), tag, &lump->cache);
	    W_ReadLump (lumpnum, lump->cache);
        result = lump->cache;
    }
    return result;
    */
}



//
// W_CacheLumpName
//
void *W_CacheLumpName(const char *name, int tag)
{
    return W_CacheLumpNum(W_GetNumForName(name), tag);
}

// 
// Release a lump back to the cache, so that it can be reused later 
// without having to read from disk again, or alternatively, discarded
// if we run out of memory.
//
// Back in Vanilla Doom, this was just done using Z_ChangeTag 
// directly, but now that we have WAD mmap, things are a bit more
// complicated ...
//

void W_ReleaseLumpNum(lumpindex_t lumpnum)
{
    return;

    lumpinfo_t *lump;

    lump = lumpinfo[lumpnum];

    Z_ChangeTag(lump->cache, PU_CACHE);
}

void W_ReleaseLumpName(const char *name)
{
    W_ReleaseLumpNum(W_GetNumForName(name));
}

// Generate a hash table for fast lookups

void W_GenerateHashTable(void)
{
    lumpindex_t i;

    // Free the old hash table, if there is one:
    if (lumphash != NULL)
    {
        Z_Free(lumphash);
    }

    // Generate hash table
    if (numlumps > 0)
    {
        lumphash = Z_Malloc(sizeof(lumpindex_t) * numlumps, PU_STATIC, NULL);

        for (i = 0; i < numlumps; ++i)
        {
            lumphash[i] = -1;
        }

        for (i = 0; i < numlumps; ++i)
        {
            unsigned int hash;

            hash = W_LumpNameHash(ZK_LUMPSTRUCTS[i].name) % numlumps;

            // Hook into the hash table

            ZK_LUMPSTRUCTS[i].next = lumphash[hash];
            lumphash[hash] = i;
        }
    }

    // All done!
}

const char *W_WadNameForLump(const lumpinfo_t *lump)
{
	return "hz.wad"; //AAAAAAAAAAAAAA M_BaseName(lump->wad_file->path);
}

boolean W_IsIWADLump(const lumpinfo_t *lump)
{
	return true; // AAAAAAAAAA lump->wad_file == lumpinfo[0]->wad_file;
}
