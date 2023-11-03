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
// DESCRIPTION:  none
//


#include "i_sound.h"
#include "i_system.h"

#include "doomfeatures.h"
#include "deh_str.h"

#include "doomstat.h"
#include "doomtype.h"

#include "sounds.h"
#include "s_sound.h"

#include "m_misc.h"
#include "m_random.h"
#include "m_argv.h"

#include "p_local.h"
#include "w_wad.h"
#include "z_zone.h"

void S_Init(int sfxVolume, int musicVolume)
{  
}

void S_Shutdown(void)
{
}

//
// Per level startup code.
// Kills playing sounds at start of level,
//  determines music if any, changes music.
//

void S_Start(void)
{
}        

void S_StopSound(mobj_t *origin)
{
}

void S_StartSound(void *origin_p, int sfx_id)
{
}        

void S_PauseSound(void)
{
}

void S_ResumeSound(void)
{
}

void S_UpdateSounds(mobj_t *listener)
{
}

void S_SetMusicVolume(int volume)
{
}

void S_SetSfxVolume(int volume)
{
}

void S_StartMusic(int m_id)
{
}

void S_ChangeMusic(int musicnum, int looping)
{
}

boolean S_MusicPlaying(void)
{
    return false; //I_MusicIsPlaying();
}

void S_StopMusic(void)
{
}

