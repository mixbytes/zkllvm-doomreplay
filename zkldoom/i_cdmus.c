//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 1993-2008 Raven Software
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
//
// SDL implementation of the Hexen CD interface.
//

#include <stdio.h>

#ifdef ORIGCODE
#include "SDL.h"
#include "SDL_cdrom.h"
#endif

#include "doomtype.h"

#include "i_cdmus.h"

#ifdef ORIGCODE
static SDL_CD *cd_handle = NULL;
static char *startup_error = NULL;
static const char *cd_name = NULL;
#endif

int cd_Error;

int I_CDMusInit(void)
{
#ifdef ORIGCODE
    int drive_num = 0;

    // The initialize function is re-invoked when the CD track play cheat
    // is used, so use the opportunity to call SDL_CDStatus() to update
    // the status of the drive.

    if (cd_handle == NULL)
    {
        if (SDL_Init(SDL_INIT_CDROM) < 0)
        {
            startup_error = "Failed to init CD subsystem.";
            cd_Error = 1;
            return -1;
        }

        // TODO: config variable to control CDROM to use.

        cd_handle = SDL_CDOpen(drive_num);

        if (cd_handle == NULL)
        {
            startup_error = "Failed to open CD-ROM drive.";
            cd_Error = 1;
            return -1;
        }

        cd_name = SDL_CDName(drive_num);
    }

    if (SDL_CDStatus(cd_handle) == CD_ERROR)
    {
        startup_error = "Failed to read CD status.";
        cd_Error = 1;
        return -1;
    }

    if (!CD_INDRIVE(cd_handle->status))
    {
        startup_error = "No CD in drive.";
        cd_Error = 1;
        return -1;
    }

    cd_Error = 0;
#endif
    return 0;
}

// We cannot print status messages inline during startup, they must
// be deferred until after I_CDMusInit has returned.

void I_CDMusPrintStartup(void)
{
}

int I_CDMusPlay(int track)
{
	return 0;
}

int I_CDMusStop(void)
{
	return 0;
}

int I_CDMusResume(void)
{
	return 0;
}

int I_CDMusSetVolume(int volume)
{
    cd_Error = 0;

    return 0;
}

int I_CDMusFirstTrack(void)
{
	return 0;
}

int I_CDMusLastTrack(void)
{
	return 0;
}

int I_CDMusTrackLength(int track_num)
{
	return 0;
}

