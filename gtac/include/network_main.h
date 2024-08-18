#pragma once

#ifndef SUBTARGET
global(10) bool g_bRestartNetworkGame;
global(11) bool g_bReturnToRendezvous;
global(12) bool g_bLeaveSession;
global(14) uint g_NextGameMode;
global(15) uint g_NextEpisode;
global(16) bool g_bRecheckLan;
global(65042) bool g_bEndingSession;
global(65043) int g_rgNetworkCarGenerators[10];
#elif SUBTARGET==SUBTARGET_TLAD
global(11) bool g_bRestartNetworkGame;
global(12) bool g_bReturnToRendezvous;
global(13) bool g_bLeaveSession;
global(16) uint g_NextEpisode;
#elif SUBTARGET==SUBTARGET_TBOGT
global(860) bool g_bRestartNetworkGame;
global(861) bool g_bReturnToRendezvous;
global(862) bool g_bLeaveSession;
global(865) uint g_NextEpisode;
#endif

typedef struct networkGameConfig_s
{
	int Count;
	int Gamemode;
	int Ranked;
	int Slots;
	int Private;
	int Episode;
	int MaxTeams;
	int AutoAim;
	int Police;
	int Blips;
	int Vehicles;
	int data[20];
} networkGameConfig;

extern void CreateDefaultParkedCars();
extern void EndSession();
extern void StoreNetworkScriptValues();
extern void Start_A_Network_Game_From_A_Network_Game();
extern int GetGameModeMaxSlots(uint GameMode);
extern void CleanupNet();
