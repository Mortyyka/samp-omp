/*

    Auto AFK Detect v2.1
    Originaly made by: Mihai (Mihaitza. - BBGaming.ro)
    Modified by Mortyyka at 2022/10/29 - 11PM CEST

    Functions:
        - IsPlayerPaused(playerid) - Boolean, returns true or false based on the users AFK status
        - TimeSincePaused(playerid) - returns the time since the user is afk


*/
 
new bool:PlayerAFK[MAX_PLAYERS]; // Set player variable [0-NOT-AFK | 1-AFK]
new AFKDetect[MAX_PLAYERS]; // Set current date/time to player from OnPlayerUpdate(OPU)
new bool: FunctionCall[2][MAX_PLAYERS]; // Helps not to repeat OnPlayerPause or/and OnPlayerUnpause
new playerAName[50]; //Player name
new AFKTime[MAX_PLAYERS];
 
#include <a_samp>
#include <YSI_Data\y_iterate>
 
#if defined _AFKDETECT_INC
        #endinput
#endif
#define _AFKDETECT_INC
 
forward OnPlayerPause(playerid);
forward OnPlayerUnpause(playerid);
forward AFKChecker();
 
public OnPlayerUpdate(playerid)
{
        AFKDetect[playerid] = gettime();
    #if defined VFUNC_OnPlayerUpdate
        return VFUNC_OnPlayerUpdate(playerid);
    #else
        return 1;
    #endif
}
#if defined VFUNC_OnPlayerUpdate
    forward VFUNC_OnPlayerUpdate(playerid);
#endif
#if defined _ALS_OnPlayerUpdate
    #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate VFUNC_OnPlayerUpdate
 
public OnPlayerDisconnect(playerid, reason)
{
    if(PlayerAFK[playerid] == true && FunctionCall[1][playerid] == false)
    {
        GetPlayerName(playerid, playerAName,sizeof(playerAName)),
        PlayerAFK[playerid] = false;
        printf("[resume] %s is no longer AFK because he left the game. (%d seconds)",playerAName,gettime()-AFKTime[playerid]);
        FunctionCall[1][playerid] = true;
        FunctionCall[0][playerid] = false;
        AFKTime[playerid] = 0;
        CallLocalFunction("OnPlayerUnpause", "i", playerid);
    }
    #if defined VFUNC_OnPlayerDisconnect
        return VFUNC_OnPlayerDisconnect(playerid, reason);
    #else
        return 1;
    #endif
}
#if defined VFUNC_OnPlayerDisconnect
    forward VFUNC_OnPlayerDisconnect(playerid, reason);
#endif
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect VFUNC_OnPlayerDisconnect
 
public OnGameModeInit()
{
    SetTimer("AFKChecker",1000,true);
    #if defined VFUNC_OnGameModeInit
        return VFUNC_OnGameModeInit();
    #else
        return 1;
    #endif
}
#if defined VFUNC_OnGameModeInit
    forward VFUNC_OnGameModeInit();
#endif
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit VFUNC_OnGameModeInit
public AFKChecker()
{
    foreach(new p : Player)
    {
        if(gettime()-AFKDetect[p] > 5)
        {
            if(PlayerAFK[p] == false && FunctionCall[0][p] == false)
            {
                GetPlayerName(p, playerAName,sizeof(playerAName));
                PlayerAFK[p] = true;
                CallLocalFunction("OnPlayerPause", "i", p);
                printf("[pause] %s is now AFK.",playerAName);
                FunctionCall[0][p] = true;
                FunctionCall[1][p] = false;
                AFKTime[p] = gettime();
            }
        }
        else
        {
            if(PlayerAFK[p] == true && FunctionCall[1][p] == false)
            {
                GetPlayerName(p, playerAName,sizeof(playerAName));
                PlayerAFK[p] = false;
                CallLocalFunction("OnPlayerUnpause", "i", p);
                printf("[resume] %s is no longer AFK. (%d seconds)",playerAName,gettime()-AFKTime[p]);
                FunctionCall[1][p] = true;
                FunctionCall[0][p] = false;
                AFKTime[p] = gettime()-AFKTime[p];
            }
        }
    }
    return 1;
}
bool:IsPlayerPaused(playerid)
{
    if(PlayerAFK[playerid] == true) return true;
    else return false;
}
 
stock TimeSincePaused(playerid) {
    if(PlayerAFK[playerid] == true) return gettime()-AFKTime[playerid];
    else return AFKTime[playerid];
}
