#include "types.h"
#include "constants.h"
#include "intrinsics.h"
#include "natives.h"
#include "common.h"
#include "gtac.h"
#include "util.h"
#include "phone.h"
#include "gtac_util.h"
#include "network_main.h"

#define SPCOOP 0
#define GTAC_IV_OFFLINE_PARACHUTES_TBOGT 0

#if defined(SUBTARGET) && SUBTARGET==SUBTARGET_TBOGT
global(10530) int g_iPrisonSiren;

typedef struct PACKED
{
	int m_Unknown;//0-4
	int m_Unknown4;//4-8
	int m_rgData[21];
} tClientPlayerData;

global(2 + 1) tClientPlayerData g_rgClientPlayerData[32];
#endif

bool EnsureModelLoaded(uint Model)
{
	REQUEST_MODEL(Model);
	if (HAS_MODEL_LOADED(Model))
	{
		return 1;
	}
	return 0;
}

bool HostGame(networkGameConfig* pGameConfig)
{
	SET_HOST_MATCH_ON(false);
	if (pGameConfig->Gamemode == -1)
		return false;

	SET_LOADING_TEXT("Hosting...");

	if (pGameConfig->Gamemode == 8 && !NETWORK_GET_LAN_SESSION() && IS_PLAYER_ONLINE())
	{
		if (!NETWORK_HOST_RENDEZVOUS_E1(pGameConfig->Gamemode, pGameConfig->Slots, pGameConfig->Episode))
			return false;
	}
	else
	{
		if (!NETWORK_HOST_GAME_E1(pGameConfig->Gamemode, pGameConfig->Ranked != 0, pGameConfig->Slots, pGameConfig->Private, pGameConfig->Episode, pGameConfig->MaxTeams))
			return false;
	}

	while (NETWORK_HOST_GAME_PENDING())
		WAIT(0);

	if (!NETWORK_HOST_GAME_SUCCEEDED())
	{
		GTAC_LOG("NETWORK_HOST_GAME_SUCCEEDED - Failed");
		CleanupNet();
		return false;
	}

	SET_LOADING_TEXT("Network game pending...");
	while (IS_NETWORK_GAME_PENDING())
		WAIT(0);

	return true;
}

bool FindAndJoinGame(networkGameConfig* pGameConfig)
{
	GTAC_LOG("FindAndJoinGame");
	if (pGameConfig->Gamemode == -1)
		return false;
	SET_LOADING_TEXT("Searching...");
	NETWORK_FIND_GAME(pGameConfig->Gamemode, pGameConfig->Ranked, pGameConfig->Episode, pGameConfig->MaxTeams);
	while (NETWORK_FIND_GAME_PENDING())
		WAIT(0);
	int Count = NETWORK_GET_NUMBER_OF_GAMES();
	if (Count == 0)
	{
		GTAC_LOG("NETWORK_GET_NUMBER_OF_GAMES returned 0");
		return false;
	}
	SET_LOADING_TEXT("Joining...");
	if (!NETWORK_JOIN_GAME(0))
	{
		GTAC_LOG("NETWORK_JOIN_GAME - Failed");
		CleanupNet();
		return false;
	}
	while (NETWORK_JOIN_GAME_PENDING())
		WAIT(0);
	if (!NETWORK_JOIN_GAME_SUCCEEDED())
	{
		GTAC_LOG("NETWORK_JOIN_GAME_SUCCEEDED - Failed");
		CleanupNet();
		return false;
	}
	SET_LOADING_TEXT("Network game pending...");
	while (IS_NETWORK_GAME_PENDING())
		WAIT(0);
	return true;
}

bool JoinGame()
{
	SET_LOADING_TEXT("Joining...");
	if (!NETWORK_JOIN_GAME(GET_SERVER_ID()))
	{
		GTAC_LOG("NETWORK_JOIN_GAME - Failed");
		CleanupNet();
		return false;
	}
	while (NETWORK_JOIN_GAME_PENDING())
		WAIT(0);
	if (!NETWORK_JOIN_GAME_SUCCEEDED())
	{
		GTAC_LOG("NETWORK_JOIN_GAME_SUCCEEDED - Failed");
		CleanupNet();
		return false;
	}
	SET_LOADING_TEXT("Network game pending...");
	while (IS_NETWORK_GAME_PENDING())
		WAIT(0);
	return true;
}

bool JoinSummons()
{
	SET_LOADING_TEXT("Joining...");
	if (!NETWORK_JOIN_SUMMONS())
	{
		GTAC_LOG("NETWORK_JOIN_SUMMONS - Failed");
		CleanupNet();
		return false;
	}
	while (NETWORK_JOIN_GAME_PENDING())
		WAIT(0);
	NETWORK_CLEAR_SUMMONS();
	if (!NETWORK_JOIN_GAME_SUCCEEDED())
	{
		GTAC_LOG("NETWORK_JOIN_GAME_SUCCEEDED - Failed");
		CleanupNet();
		return false;
	}
	SET_LOADING_TEXT("Network game pending...");
	while (IS_NETWORK_GAME_PENDING())
		WAIT(0);
	return true;
}

bool HostGameGTAC()
{
	SET_LOADING_TEXT("Hosting...");
	if (!NETWORK_HOST_GAME_GTAC())
	{
		GTAC_LOG("NETWORK_HOST_GAME_GTAC - Failed");
		CleanupNet();
		return false;
	}
	while (NETWORK_HOST_GAME_PENDING())
		WAIT(0);
	if (!NETWORK_HOST_GAME_SUCCEEDED())
	{
		GTAC_LOG("NETWORK_HOST_GAME_SUCCEEDED - Failed");
		return false;
	}
	SET_LOADING_TEXT("Network game pending...");
	while (IS_NETWORK_GAME_PENDING())
		WAIT(0);
	LAUNCH_LOCAL_PLAYER_IN_NETWORK_GAME();
	NETWORK_START_SESSION();
	SET_LOADING_TEXT("Starting session...");
	while (NETWORK_START_SESSION_PENDING())
		WAIT(0);
	return true;
}

void SetNetworkPlayer()
{
	if (GET_PLAYERSETTINGS_MODEL_CHOICE() != (GetCharModel(GetPlayerChar())))
	{
		REQUEST_MODEL(GET_PLAYERSETTINGS_MODEL_CHOICE());
		LOAD_ALL_OBJECTS_NOW();
		while (!EnsureModelLoaded(GET_PLAYERSETTINGS_MODEL_CHOICE()))
			WAIT(0);
		CHANGE_PLAYER_MODEL(GetPlayer(), GET_PLAYERSETTINGS_MODEL_CHOICE());
//#ifdef SUBTARGET
		if (IS_CHAR_MALE(GetPlayerChar()) && GET_CURRENT_EPISODE() != 0)
			SET_ANIM_GROUP_FOR_CHAR(GetPlayerChar(), "Move_player");
//#endif
		MARK_MODEL_AS_NO_LONGER_NEEDED(GET_PLAYERSETTINGS_MODEL_CHOICE());
	}
	SET_PLAYERSETTINGS_MODEL_VARIATIONS_CHOICE(GetPlayer());
	SET_VOICE_ID_FROM_HEAD_COMPONENT(GetPlayerChar(), 0, IS_CHAR_MALE(GetPlayerChar()));
}

void NetworkSetup()
{
	GTAC_LOG("NetworkSetup");

	if (!IS_CHAR_DEAD(GetPlayerChar()))
	{
		REMOVE_ALL_CHAR_WEAPONS(GetPlayerChar());
		SET_CHAR_HEALTH(GetPlayerChar(), 300);
		CLEAR_WANTED_LEVEL(GetPlayer());
	}
	//SetNetworkPlayer();

	//SetPlayerEnabled(GET_PLAYER_ID(), false);

	// Restore any phone config singleplayer gave us
	RestorePhoneScriptValues();

	// Enable Zit!
	g_Cellphone.m_bZit = 1;

#if 0
	if (GET_CURRENT_EPISODE() == 0)
	{
		// Normally netgame doesn't do this
		InitialLogic();
	}
#endif

#if defined(SUBTARGET) && SUBTARGET==SUBTARGET_TBOGT
	// Fix for the siren at the prison
	g_iPrisonSiren = -1;
#endif

	g_bLeaveSession = false;

	SET_INT_STAT(STAT_ISLANDS_UNLOCKED, 3);
	SET_MAX_WANTED_LEVEL(6);
	UNLOCK_LAZLOW_STATION();
	FORCE_NEXT_STATION_LAZLOW(false);

	if (GET_CURRENT_EPISODE() == 0)
	{
		LoadScript("stunt", 1024);
		ALLOW_STUNT_JUMPS_TO_TRIGGER(true);
	}
}

void SetupAfterNetworkGameRunning(bool bNetworkMain)
{
	if (!bNetworkMain)
	{
		// will get issues if network TXD isn't loaded so load it
		REQUEST_STREAMED_TXD("network", true);
		while (!HAS_STREAMED_TXD_LOADED("network"))
			WAIT(0);
	}

	// core scripts
	if (!bNetworkMain)
		LoadScript("initialnet", 1024);
	//LoadScript("computerNEWS", 1024);

	LoadScript("ambControlLoader", 1024);
#if !defined(SUBTARGET) || SUBTARGET==SUBTARGET_TBOGT
	LoadScript("ambDebug", 1024);
#endif

#if defined(SUBTARGET) && SUBTARGET==SUBTARGET_TBOGT && GTAC_IV_OFFLINE_PARACHUTES_TBOGT
	//LoadScript("baseJumpLauncher", 1024);
	//LoadScript("parachuteLauncher", 1024);
	LoadScript("parachuteLauncher_mp", 1024);
	LoadScript("baseJumpLauncher_mp", 1024);
	g_rgClientPlayerData[GET_PLAYER_ID()].m_Unknown4 = 5;
#endif

	int GameMode = NETWORK_GET_GAME_MODE();
	if (GameMode != 8 && GameMode != 16)
		return;

#if 1
	ALLOCATE_SCRIPT_TO_OBJECT("puzzle_launcher", 691499124, 100, 10.00000000, -1);
	ALLOCATE_SCRIPT_TO_OBJECT("puzzle_launcher", -386570734, 100, 10.00000000, -1);

	ALLOCATE_SCRIPT_TO_OBJECT("ambTV", -1618524073, 100, 80.00000000, -1);
	ALLOCATE_SCRIPT_TO_OBJECT("ambTV", -1058927856, 100, 80.00000000, -1);
	ALLOCATE_SCRIPT_TO_OBJECT("ambTV", 1243139908, 100, 80.00000000, -1);
	ALLOCATE_SCRIPT_TO_OBJECT("ambTV", 900769396, 100, 80.00000000, -1);
	ALLOCATE_SCRIPT_TO_OBJECT("ambTV", -1336305346, 100, 80.00000000, -1);
	ALLOCATE_SCRIPT_TO_OBJECT("ambClubLights", 1005973733, 100, 50.00000000, -1);
	ALLOCATE_SCRIPT_TO_OBJECT("ambClubLights", 1781111577, 100, 50.00000000, -1);
	ALLOCATE_SCRIPT_TO_OBJECT("ambClubLights", -21824081, 100, 50.00000000, -1);

	REGISTER_WORLD_POINT_SCRIPT_BRAIN("EmpireTelescope", 80.0);
	REGISTER_WORLD_POINT_SCRIPT_BRAIN("EmpireDown", 80.0);
	//REGISTER_WORLD_POINT_SCRIPT_BRAIN("ambHotel", 50.0);
	//REGISTER_WORLD_POINT_SCRIPT_BRAIN("ambChurchDoors", 100.0);
	//REGISTER_WORLD_POINT_SCRIPT_BRAIN("ambToiletDoors", 25.0);
	REGISTER_WORLD_POINT_SCRIPT_BRAIN("cablecars", 75.0);
#endif

#if 0
	//ALLOCATE_SCRIPT_TO_RANDOM_PED("garbage_trucks", 1136499716, 100, 0);
	ALLOCATE_SCRIPT_TO_RANDOM_PED("ambbeggar", -1080673049, 100, 1);
	ALLOCATE_SCRIPT_TO_RANDOM_PED("ambbeggar", -1827421800, 100, 1);
	ALLOCATE_SCRIPT_TO_RANDOM_PED("ambbeggar", -142386662, 100, 1);
	ALLOCATE_SCRIPT_TO_RANDOM_PED("ambpimpnpros", 552542187, 100, 1);
	ALLOCATE_SCRIPT_TO_RANDOM_PED("ambpimpnpros", 996267216, 100, 1);
	ALLOCATE_SCRIPT_TO_RANDOM_PED("ambdealer", 1448755353, 100, 1);
	ALLOCATE_SCRIPT_TO_RANDOM_PED("ambpreacher", 495499562, 100, 1);
	ALLOCATE_SCRIPT_TO_RANDOM_PED("ambpreacher", 379171768, 100, 1);
	ALLOCATE_SCRIPT_TO_RANDOM_PED("ambbusker", -1188246269, 100, 1);
#endif
}

void GTACJoin()
{
	if (GTAC_IS_MULTIPLAYER_GAME())
	{
		GTAC_JOIN();

		// Is this needed?
		while (!GTAC_IS_JOINED())
			WAIT(0);
	}
}

bool ShouldLoadPrisoner()
{
	if (!IS_NETWORK_GAME_RUNNING())
		return false;

	if (!IS_NETWORK_PLAYER_ACTIVE(GET_PLAYER_ID()))
		return false;

	if (IS_CHAR_IN_ZONE(GetPlayerChar(), "ALSCF"))
		return true;

	return false;
}

void UpdatePrisoners()
{
	bool bRequestedPrisoner = false;
	if (ShouldLoadPrisoner())
	{
		if (!bRequestedPrisoner)
		{
			REQUEST_MODEL(PED_M_Y_PRISON); // Allow prisoners to spawn in MP
			bRequestedPrisoner = true;
		}
	}
	else
	{
		if (bRequestedPrisoner)
		{
			MARK_MODEL_AS_NO_LONGER_NEEDED(PED_M_Y_PRISON);
			bRequestedPrisoner = false;
		}
	}
}

void NetworkMain(bool bRestarted, bool bLoadedSavedGame)
{
	GTAC_LOG("NetworkMain");

#if SPCOOP
	if (!IS_NETWORK_SESSION())
	{
		GTAC_LOG("SP COOP?");
		TERMINATE_THIS_SCRIPT();
	}
#endif

	ALLOW_THIS_SCRIPT_TO_BE_PAUSED(false);
	SET_INT_STAT(363, 3);
	SET_STAT_FRONTEND_NEVER_VISIBLE(363);
//#ifdef SUBTARGET
	SET_HIDE_WEAPON_ICON(false);
	FORCE_NOISE_OFF(false);
//#endif
	SET_GPS_REMAINS_WHEN_TARGET_REACHED_FLAG(false);
	SET_NO_RESPRAYS(0);
	SWITCH_RANDOM_TRAINS(false); // Trains must default off in network sessions

#if SPCOOP
	// SP coop
	if (IS_NETWORK_SESSION())
		FadeOut(0);
#else
	FadeOut(0);
#endif

	// BUG FIX: We don't want terrorist attack messages
	CLEAR_NEWS_SCROLLBAR();

	// Clear scenario blocking areas to be safe
	FLUSH_SCENARIO_BLOCKING_AREAS();

	g_bRestartNetworkGame = false;
	g_bReturnToRendezvous = false;
	g_bLeaveSession = false;
	g_NextEpisode = GET_CURRENT_EPISODE();

#if SPCOOP
	// SP coop
	if (IS_NETWORK_SESSION())
	{
		NetworkSetup();
	}
	else
	{
		GTAC_LOG("SP COOP?");
		//SetPlayerEnabled(GET_PLAYER_ID(), true);
	}
#else
	NetworkSetup();
#endif

	NETWORK_SET_LAN_SESSION(GET_ONLINE_LAN());

	networkGameConfig GameConfig;

	//if (GTAC_IS_MULTIPLAYER_GAME())
	{
		if (NETWORK_HAVE_SUMMONS()) // Summons
		{
			GTAC_LOG("We have summons...");

			SET_HOST_MATCH_ON(false);
			SET_START_FROM_FILTER_MENU(false);

			JoinSummons();
		}
		else if (GET_START_FROM_FILTER_MENU()) // Join match
		{
			GTAC_LOG("Start from filter menu...");

			SET_HOST_MATCH_ON(false);
			SET_START_FROM_FILTER_MENU(false);
			NETWORK_CLEAR_SUMMONS();

			if (!JoinGame())
				goto Host;
		}
		else if (GET_HOST_MATCH_ON()) // Host match
		{
Host:
			GTAC_LOG("Host match...");

			SET_HOST_MATCH_ON(false);
			SET_START_FROM_FILTER_MENU(false);
			NETWORK_CLEAR_SUMMONS();

			NETWORK_RESTORE_GAME_CONFIG(&GameConfig);
			HostGame(&GameConfig);
		}
		else // Quick match
		{
			GTAC_LOG("Quick match...");

			SET_HOST_MATCH_ON(false);
			SET_START_FROM_FILTER_MENU(false);
			NETWORK_CLEAR_SUMMONS();

			NETWORK_RESTORE_GAME_CONFIG(&GameConfig);

#if 0
			char szBuffer[16];
			itos((char*)szBuffer, GameConfig.Gamemode, 64);

			GTAC_LOG(szBuffer);
#endif

			if (!FindAndJoinGame(&GameConfig))
			{
				WAIT(0);
				HostGame(&GameConfig);
			}
		}
	}
	if (IS_NETWORK_GAME_RUNNING() && IS_THIS_MACHINE_THE_SERVER())
	{
#if 0
		if (!NETWORK_IS_RENDEZVOUS() && !NETWORK_IS_SESSION_ADVERTISE())
			NETWORK_ADVERTISE_SESSION(true);
		if (!NETWORK_IS_TVT() && !NETWORK_IS_GAME_RANKED())
			NETWORK_SET_SESSION_INVITABLE(true);
#else
		if (!NETWORK_IS_SESSION_ADVERTISE())
			NETWORK_ADVERTISE_SESSION(true);
		NETWORK_SET_SESSION_INVITABLE(true);
#endif
	}

	SET_GTAC_LOADING_TEXT();

	int GameMode = NETWORK_GET_GAME_MODE();

	if (GameMode == -1 || GameMode >= 30) // network_main won't fire our gamemode, so do it now
	{
		GameConfig.Episode = GET_CURRENT_EPISODE();

		SetupAfterNetworkGameRunning(false);

		// Start the gamemode
		if (GameMode == 30)
		{
			StartGTACScript("gtac_custom_net");
		}
		else if (GameMode == -1 || GameMode == 31 || GameMode == 32)
		{
			if (GameMode == -1)
			{
				HostGameGTAC();
			}

			StartGTACScript("gtac_sandbox_net");
			//LoadScript("party_mode", 20240);

#if 0
			vector3 vecPos = {-310.001f, 945.603f, 14.3728f};
			//vector3 vecPos = {-612.159f, -933.031f, 4.842f};

			SET_CHAR_COORDINATES_NO_OFFSET(GetPlayerPed(), vecPos.x, vecPos.y, vecPos.z);
			SET_CHAR_HEADING(GetPlayerPed(), 180.0f);

			SetPlayerEnabled(GET_PLAYER_ID(), true);

			REQUEST_COLLISION_AT_POSN(vecPos.x, vecPos.y, vecPos.z);
			CLEAR_CHAR_TASKS_IMMEDIATELY(GetPlayerChar());
			SET_CHAR_HEALTH(GetPlayerChar(), 300);
			REMOVE_ALL_CHAR_WEAPONS(GetPlayerChar());
			CLEAR_WANTED_LEVEL(GetPlayer());
			SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN(GetPlayerChar(), false);
			SET_GAME_CAM_HEADING(0.0f);

			FadeIn(1000);

			//LoadScript("party_mode", 20240);
#endif
		}

		StartGTACScript("gtac_network_main");
	}
	else
	{
		SET_LOADING_TEXT("Loading GameMode...");

		// Fire up original network_main
		LoadScript("network_main", 1024);

		// Give network_main some time to "init"
		WAIT(10);

		SetupAfterNetworkGameRunning(true);

		// network_main.sco will take care of everything from here on out
		//TERMINATE_THIS_SCRIPT();
	}

	GTACJoin();

#if 0
	if (!IS_NETWORK_GAME_RUNNING())
	{
		WAIT(100);

		GiveContact(21, false); // ZiT!
	}
#endif

	while (true)
	{
		// Enable Zit!
		g_Cellphone.m_bZit = 1;

		if (HAS_GAMER_CHANGED_NETWORK_MODEL_SETTINGS())
		{
			SetNetworkPlayer();
		}

#if 0
		// Trains fine if 1 player
		if (GET_NUMBER_OF_PLAYERS() <= 1)
			SWITCH_RANDOM_TRAINS(true);
		else
			SWITCH_RANDOM_TRAINS(false);
#endif

		UpdatePrisoners();

		WAIT(100);
	}

	TERMINATE_THIS_SCRIPT();
}

void main(bool bRestarted, bool bLoadedSavedGame)
{
	THIS_SCRIPT_IS_SAFE_FOR_NETWORK_GAME();

	if (GTAC_IS_NETWORK_SESSION())
		NetworkMain(bRestarted, bLoadedSavedGame);
	else
		StartGTACScript("gtac_freeroam_sp");

	// Keep gtac.sco running so the C++ side can use this script
	while (true)
	{
		WAIT(1000);
	}

	TERMINATE_THIS_SCRIPT();
}
