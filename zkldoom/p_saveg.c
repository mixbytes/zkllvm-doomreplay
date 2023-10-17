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
//	Archiving: SaveGame I/O.
//


#include "dstrings.h"
#include "deh_main.h"
#include "i_system.h"
#include "z_zone.h"
#include "p_local.h"
#include "p_saveg.h"

// State.
#include "doomstat.h"
#include "g_game.h"
#include "m_misc.h"
#include "r_state.h"

#define SAVEGAME_EOF 0x1d
#define VERSIONSIZE 16 

int savegamelength;
boolean savegame_error;

// Get the filename of a temporary file to write the savegame to.  After
// the file has been successfully saved, it will be renamed to the 
// real file.

char *P_TempSaveGameFile(void)
{
    return "tmpfuck.dsg";
}

// Get the filename of the save game file to use for the specified slot.

char *P_SaveGameFile(int slot)
{
    return "fuck.dsg";
}

// Endian-safe integer read/write functions

static byte saveg_read8(void)
{
    return 0;
}

static void saveg_write8(byte value)
{
}

static short saveg_read16(void)
{
    return 0;
}

static void saveg_write16(short value)
{
}

static int saveg_read32(void)
{
    return 0;
}

static void saveg_write32(int value)
{
}

// Pad to 4-byte boundaries

static void saveg_read_pad(void)
{
}

static void saveg_write_pad(void)
{
}


// Pointers

static void *saveg_readp(void)
{
}

static void saveg_writep(void *p)
{
}

// Enum values are 32-bit integers.

#define saveg_read_enum saveg_read32
#define saveg_write_enum saveg_write32

//
// Structure read/write functions
//

//
// mapthing_t
//

static void saveg_read_mapthing_t(mapthing_t *str)
{
}

static void saveg_write_mapthing_t(mapthing_t *str)
{
}

//
// actionf_t
// 

static void saveg_read_actionf_t(actionf_t *str)
{
}

static void saveg_write_actionf_t(actionf_t *str)
{
}

//
// think_t
//
// This is just an actionf_t.
//

#define saveg_read_think_t saveg_read_actionf_t
#define saveg_write_think_t saveg_write_actionf_t

//
// thinker_t
//

static void saveg_read_thinker_t(thinker_t *str)
{
}

static void saveg_write_thinker_t(thinker_t *str)
{
}

//
// mobj_t
//

static void saveg_read_mobj_t(mobj_t *str)
{
}

static void saveg_write_mobj_t(mobj_t *str)
{
}


//
// ticcmd_t
//

static void saveg_read_ticcmd_t(ticcmd_t *str)
{
}

static void saveg_write_ticcmd_t(ticcmd_t *str)
{
}

//
// pspdef_t
//

static void saveg_read_pspdef_t(pspdef_t *str)
{
}

static void saveg_write_pspdef_t(pspdef_t *str)
{
}

//
// player_t
//

static void saveg_read_player_t(player_t *str)
{
}

static void saveg_write_player_t(player_t *str)
{
}


//
// ceiling_t
//

static void saveg_read_ceiling_t(ceiling_t *str)
{
}

static void saveg_write_ceiling_t(ceiling_t *str)
{
}

//
// vldoor_t
//

static void saveg_read_vldoor_t(vldoor_t *str)
{
}

static void saveg_write_vldoor_t(vldoor_t *str)
{
}

//
// floormove_t
//

static void saveg_read_floormove_t(floormove_t *str)
{
}

static void saveg_write_floormove_t(floormove_t *str)
{
}

//
// plat_t
//

static void saveg_read_plat_t(plat_t *str)
{
}

static void saveg_write_plat_t(plat_t *str)
{
}

//
// lightflash_t
//

static void saveg_read_lightflash_t(lightflash_t *str)
{
}

static void saveg_write_lightflash_t(lightflash_t *str)
{
}

//
// strobe_t
//

static void saveg_read_strobe_t(strobe_t *str)
{
}

static void saveg_write_strobe_t(strobe_t *str)
{
}

//
// glow_t
//

static void saveg_read_glow_t(glow_t *str)
{
}

static void saveg_write_glow_t(glow_t *str)
{
}

//
// Write the header for a savegame
//

void P_WriteSaveGameHeader(char *description)
{
}

// 
// Read the header for a savegame
//

boolean P_ReadSaveGameHeader(void)
{
}

//
// Read the end of file marker.  Returns true if read successfully.
// 

boolean P_ReadSaveGameEOF(void)
{
    int value;

    value = saveg_read8();

    return value == SAVEGAME_EOF;
}

//
// Write the end of file marker
//

void P_WriteSaveGameEOF(void)
{
}

//
// P_ArchivePlayers
//
void P_ArchivePlayers (void)
{
}



//
// P_UnArchivePlayers
//
void P_UnArchivePlayers (void)
{
}


//
// P_ArchiveWorld
//
void P_ArchiveWorld (void)
{
}



//
// P_UnArchiveWorld
//
void P_UnArchiveWorld (void)
{
}





//
// Thinkers
//
typedef enum
{
    tc_end,
    tc_mobj

} thinkerclass_t;


//
// P_ArchiveThinkers
//
void P_ArchiveThinkers (void)
{
}



//
// P_UnArchiveThinkers
//
void P_UnArchiveThinkers (void)
{
}


//
// P_ArchiveSpecials
//
enum
{
    tc_ceiling,
    tc_door,
    tc_floor,
    tc_plat,
    tc_flash,
    tc_strobe,
    tc_glow,
    tc_endspecials

} specials_e;	



//
// Things to handle:
//
// T_MoveCeiling, (ceiling_t: sector_t * swizzle), - active list
// T_VerticalDoor, (vldoor_t: sector_t * swizzle),
// T_MoveFloor, (floormove_t: sector_t * swizzle),
// T_LightFlash, (lightflash_t: sector_t * swizzle),
// T_StrobeFlash, (strobe_t: sector_t *),
// T_Glow, (glow_t: sector_t *),
// T_PlatRaise, (plat_t: sector_t *), - active list
//
void P_ArchiveSpecials (void)
{
}


//
// P_UnArchiveSpecials
//
void P_UnArchiveSpecials (void)
{
}

