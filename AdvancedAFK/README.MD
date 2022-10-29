# AdvancedAFK.inc

A new more advanced version of the afk.inc.

## Requirements
**y_iterate** and **y_timers**
> Can be found in the YSI library.
> https://github.com/pawn-lang/YSI-Includes

|                |Example                          |Returns                        |Required                        |
|----------------|-------------------------------|-----------------------------|-----------------------------|
|AdvancedAFK_Init          |`AdvancedAFK_Init();`            |Updates the players status             | in OnGameModeInit 
|IsPlayerPaused|`IsPlayerPaused(playerid);`            |Boolean            |X            |
|OnPlayerPause|`OnPlayerPause(playerid);`            |Boolean            |X            |
|GetPlayerPausedTime          |`GetPlayerPausedTime(playerid);`            |0 or time since the user is afk (in seconds)             | X        
|AdvancedAFK_Update          |`AdvancedAFK_Update(playerid);`            |Updates the players status             | in OnPlayerUpdate       
