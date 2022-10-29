/*

    AdvancedAFK by Mortyyka
    Version: 1.0

    AdvancedAFK is an include that allows you to indicate whether a player is AFK or not.
    This project is open source under the MIT license.
    Contributions are welcome.

    Changes between AdvancedAFK and AFKDetect v2.0 made by Mihai
    - AdvancedAFK does not use the OnPlayerUpdate Callback anymore, which means the useer has to call the function in his own script.

*/

// Variables that are used in the include
new bool:AAFK_pPaused[MAX_PLAYERS],
AAFK_pPausedTime[MAX_PLAYERS],
playerName[MAX_PLAYER_NAME];

// The basic include for all Pawn based SA:MP/Open.MP projects
#include <a_samp>

#define YSI_NO_HEAP_MALLOC

// There is no need to make this more complex than it is because it'll give the user an error if they don't have the include.
// y_iterate and y_timers is part of the YSI library.
#include <YSI_Data\y_iterate>
#include <YSI_Coding\y_timers>


#if defined _AdvancedAFK_INC
        #endinput
#endif
#define _AdvancedAFK_INC


forward OnPlayerPause(playerid, paused);

// This timer is used to check if the player is paused or not.
timer AdvancedAFK_Check[1000]()
{
    foreach(new p: Player)
	{
		AAFK_pPausedTime[p]++;
		if(AAFK_pPausedTime[p] == 2)
		{
			CallLocalFunction("OnPlayerPause", "dd", p, 1);
			AAFK_pPaused[p] = true;
		}
	}
}

// This function is required to be called in the OnGameModeInit callback. Otherwise the include will not work.
stock AdvancedAFK_Init()
{
	repeat AdvancedAFK_Check();
    printf("AdvancedAFK by Mortyyka initialized.");

    return 1;
}

// This function is called when the player pauses or unpauses.
// You can use this function in your own script with the OnPlayerPause callback.
stock AdvancedAFK_Update(playerid)
{
	if(AAFK_pPaused[playerid])
	{
		CallLocalFunction("OnPlayerPause", "dd", playerid, 0);
		AAFK_pPaused[playerid] = false;
	}

	AAFK_pPausedTime[playerid] = 0;
}


// This callback is used to set the player's paused state in case of a disconnect.
public OnPlayerDisconnect(playerid, reason)
{

    if(AAFK_pPaused[playerid])
    {
        GetPlayerName(playerid, playerName,sizeof(playerName)),
        AAFK_pPaused[playerid] = false;
        printf("[resume] %s is no longer AFK because he left the game. (%d seconds)",playerName,AAFK_pPausedTime[playerid]);
        AAFK_pPausedTime[playerid] = 0;
    }
    
    #if defined AAFK_OnPlayerDisconnect
        return AAFK_OnPlayerDisconnect(playerid, reason);
    #else
        return 1;
    #endif
}
#if defined AAFK_OnPlayerDisconnect
    forward AAFK_OnPlayerDisconnect(playerid, reason);
#endif
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect AAFK_OnPlayerDisconnect


// This function can be used to check if the player is paused or not.
stock bool:IsPlayerPaused(playerid)
{
    return AAFK_pPaused[playerid];
}


// This function will return a time in seconds that the player has been paused.
stock GetPlayerPausedTime(playerid)
{
    return AAFK_pPausedTime[playerid];
}

