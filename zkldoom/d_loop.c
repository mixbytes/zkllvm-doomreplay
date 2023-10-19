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
//     Main loop code.
//

#include <stdlib.h>
#include <string.h>

#include "doomfeatures.h"

#include "d_event.h"
#include "d_loop.h"
#include "d_ticcmd.h"

#include "i_system.h"
#include "i_timer.h"
#include "i_video.h"

#include "m_argv.h"
#include "m_fixed.h"

#include "net_client.h"
#include "net_gui.h"
#include "net_io.h"
#include "net_query.h"
#include "net_server.h"
#include "net_sdl.h"
#include "net_loop.h"

#include "doomreplay.h"

// The complete set of data for a particular tic.

// BBBBBBBBBBBBBBBB
void D_ProcessEvents(void);
void M_Ticker (void);
void G_BuildTiccmd (ticcmd_t* cmd, int maketic);
void G_Ticker (void);
extern ticcmd_t *netcmds;

// static void RunTic(ticcmd_t *cmds, boolean *ingame); - replaced with

//    { 
//        netcmds = cmds;                                                                                                                    
//        G_Ticker ();
//    }
//

typedef struct
{
    ticcmd_t cmds[NET_MAXPLAYERS];
    boolean ingame[NET_MAXPLAYERS];
} ticcmd_set_t;

//
// gametic is the tic about to (or currently being) run
// maketic is the tic that hasn't had control made for it yet
// recvtic is the latest tic received from the server.
//
// a gametic cannot be run until ticcmds are received for it
// from all players.
//

static ticcmd_set_t ticdata[BACKUPTICS];

// The index of the next tic to be made (with a call to BuildTiccmd).

static int maketic;

// The number of complete tics received from the server so far.

static int recvtic;

// The number of tics that have been run (using RunTic) so far.

int gametic;

// When set to true, a single tic is run each time TryRunTics() is called.
// This is used for -timedemo mode.

boolean singletics = false;

// Index of the local player.

static int localplayer;

// Used for original sync code.

static int      skiptics = 0;

// Reduce the bandwidth needed by sampling game input less and transmitting
// less.  If ticdup is 2, sample half normal, 3 = one third normal, etc.

int		ticdup;

// Amount to offset the timer for game sync.

fixed_t         offsetms;

// Use new client syncronisation code

static boolean  new_sync = true;

// Callback functions for loop code.

static loop_interface_t *loop_interface = NULL;

// Current players in the multiplayer game.
// This is distinct from playeringame[] used by the game code, which may
// modify playeringame[] when playing back multiplayer demos.

static boolean local_playeringame[NET_MAXPLAYERS];

// Requested player class "sent" to the server on connect.
// If we are only doing a single player game then this needs to be remembered
// and saved in the game settings.

static int player_class;


// 35 fps clock adjusted by offsetms milliseconds

static int GetAdjustedTime(void)
{
    int time_ms;

    time_ms = I_GetTimeMS();

    if (new_sync)
    {
	// Use the adjustments from net_client.c only if we are
	// using the new sync mode.

        time_ms += (offsetms / FRACUNIT);
    }

    return (time_ms * TICRATE) / 1000;
}

static boolean BuildNewTic(void)
{
    int	gameticdiv;
    ticcmd_t cmd;

    gameticdiv = gametic/ticdup;

    I_StartTic ();
    
    // BBBBBBBBBB  loop_interface->ProcessEvents();
    D_ProcessEvents();

    // Always run the menu

    // BBBBBBBBBBBBBBBBB loop_interface->RunMenu();
    M_Ticker();

    if (new_sync)
    {
       // If playing single player, do not allow tics to buffer
       // up very far

       // AAAAAAAAAAAAAAa if (!net_client_connected && maketic - gameticdiv > 2)
       if (maketic - gameticdiv > 2)
           return false;

       // Never go more than ~200ms ahead

       if (maketic - gameticdiv > 8)
           return false;
    }
    else
    {
       if (maketic - gameticdiv >= 5)
           return false;
    }

    memset(&cmd, 0, sizeof(ticcmd_t));
    
    // BBBBBBBBBBBBBBBB      loop_interface->BuildTiccmd(&cmd, maketic);
    G_BuildTiccmd(&cmd, maketic);

    ticdata[maketic % BACKUPTICS].cmds[localplayer] = cmd;
    ticdata[maketic % BACKUPTICS].ingame[localplayer] = true;

    ++maketic;

    return true;
}

//
// NetUpdate
// Builds ticcmds for console player,
// sends out a packet
//
int      lasttime;

void NetUpdate (void)
{
    int nowtime;
    int newtics;
    int	i;

    // If we are running with singletics (timing a demo), this
    // is all done separately.

    if (singletics)
        return;

    // check time
    nowtime = GetAdjustedTime() / ticdup;
    newtics = nowtime - lasttime;

    lasttime = nowtime;

    if (skiptics <= newtics)
    {
        newtics -= skiptics;
        skiptics = 0;
    }
    else
    {
        skiptics -= newtics;
        newtics = 0;
    }

    // build new ticcmds for console player

    for (i=0 ; i<newtics ; i++)
    {
        if (!BuildNewTic())
        {
            break;
        }
    }
}

static void D_Disconnected(void)
{
    // In drone mode, the game cannot continue once disconnected.

    // AAAAAAAAAAAAAA
    //if (drone)
    //{
    //    I_Error("Disconnected from server in drone mode.");
    //}

    // disconnected from server

    // AAAAAAAAAAAAAAAAAa
    //printf("Disconnected from server.\n");
}

//
// Invoked by the network engine when a complete set of ticcmds is
// available.
//

void D_ReceiveTic(ticcmd_t *ticcmds, boolean *players_mask)
{
    int i;

    // Disconnected from server?

    if (ticcmds == NULL && players_mask == NULL)
    {
        D_Disconnected();
        return;
    }

    for (i = 0; i < NET_MAXPLAYERS; ++i)
    {
        // AAAAAAAAAAA if (!drone && i == localplayer)
        if (i == localplayer)
        {
            // This is us.  Don't overwrite it.
        }
        else
        {
            ticdata[recvtic % BACKUPTICS].cmds[i] = ticcmds[i];
            ticdata[recvtic % BACKUPTICS].ingame[i] = players_mask[i];
        }
    }

    ++recvtic;
}

//
// Start game loop
//
// Called after the screen is set but before the game starts running.
//
void D_StartGameLoop(void)
{
    lasttime = GetAdjustedTime() / ticdup;
}

void D_StartNetGame(net_gamesettings_t *settings,
                    netgame_startup_callback_t callback)
{
    settings->consoleplayer = 0;
	settings->num_players = 1;
	settings->player_classes[0] = player_class;
	settings->new_sync = 0;
	settings->extratics = 1;
	settings->ticdup = 1;

	ticdup = settings->ticdup;
	new_sync = settings->new_sync;
}

boolean D_InitNetGame(net_connect_data_t *connect_data)
{
    boolean result = false;

    // Call D_QuitNetGame on exit:

    // AAAAAAAAAAAAAAAAAA
    // I_AtExit(D_QuitNetGame, true);

    player_class = connect_data->player_class;

    return result;
}


//
// D_QuitNetGame
// Called before quitting to leave a net game
// without hanging the other players
//
void D_QuitNetGame (void)
{
}

static int GetLowTic(void)
{
    int lowtic;

    lowtic = maketic;

    return lowtic;
}

static int frameon;
static int frameskip[4];
static int oldnettics;

// Returns true if there are players in the game:

// When using ticdup, certain values must be cleared out when running
// the duplicate ticcmds.

static void TicdupSquash(ticcmd_set_t *set)
{
    ticcmd_t *cmd;
    unsigned int i;
    
    for (i = 0; i < NET_MAXPLAYERS ; ++i)
    {
        cmd = &set->cmds[i];
        cmd->chatchar = 0;
        if (cmd->buttons & BT_SPECIAL)
            cmd->buttons = 0;
    }
}

// When running in single player mode, clear all the ingame[] array
// except the local player.

static void SinglePlayerClear(ticcmd_set_t *set)
{
    unsigned int i;

    for (i = 0; i < NET_MAXPLAYERS; ++i)
    {
        if (i != localplayer)
        {
            set->ingame[i] = false;
        }
    }
}

//
// TryRunTics
//

void TryRunTics (void)
{
    int	i;
    int	lowtic;
    int	entertic;
    static int oldentertics;
    int realtics;
    int	availabletics;
    int	counts;

    // update the artificial clock
    // AAAAAAAAAAA BBBBBBBBBBb
    DR_UpdateTime();

    // get real tics
    entertic = I_GetTime() / ticdup;
    realtics = entertic - oldentertics;
    oldentertics = entertic;

    // in singletics mode, run a single tic every time this function
    // is called.
    
    if (singletics)
    {
        BuildNewTic();
    }
    else
    {
        // CCCCCC this used
        NetUpdate ();
    }

    lowtic = GetLowTic();

    availabletics = lowtic - gametic/ticdup;

    // decide how many tics to run

    if (new_sync)
    {
	counts = availabletics;
    }
    else
    {
        // decide how many tics to run
        if (realtics < availabletics-1)
            counts = realtics+1;
        else if (realtics < availabletics)
            counts = realtics;
        else
            counts = availabletics;

        if (counts < 1)
            counts = 1;
    }

    if (counts < 1)
	counts = 1;
    
    // wait for new tics if needed
    while (lowtic < gametic/ticdup + counts)
    {
	    NetUpdate ();
        // AAAAAAAAAAAAAAAa
        DR_UpdateTime();
        lowtic = GetLowTic();

	if (lowtic < gametic/ticdup)
	    I_Error ("TryRunTics: lowtic < gametic");

        // Don't stay in this loop forever.  The menu is still running,
        // so return to update the screen

	if (I_GetTime() / ticdup - entertic > 0)
	{
        // AAAAAAAAAAAAAAAAAAAAAAAAAAA
        // I don't think there is any point to return here.
        // Instead - continue and exit the loop
        continue;
        // return;
	}
        I_Sleep(1);
    }
    

    // run the count * ticdup dics
    while (counts--)
    {
        ticcmd_set_t *set;

        set = &ticdata[(gametic / ticdup) % BACKUPTICS];

        SinglePlayerClear(set);

	for (i=0 ; i<ticdup ; i++)
	{
        if (gametic/ticdup > lowtic)
            I_Error ("gametic>lowtic");

        memcpy(local_playeringame, set->ingame, sizeof(local_playeringame));

        // BBBBBBBBBBBBBBBBBBB loop_interface->RunTic(set->cmds, set->ingame);
        netcmds = set->cmds;                                                                                                                    
        G_Ticker ();

        gametic++;

        // modify command for duplicated tics

        TicdupSquash(set);
	}

	NetUpdate ();	// check for new console commands
    }
}

//void D_RegisterLoopCallbacks(loop_interface_t *i)
//{
//    loop_interface = i;
//}
