#include "types.h"
#include "constants.h"
#include "intrinsics.h"
#include "natives.h"
#include "common.h"
#include "gtac.h"
#include "util.h"
#include "gtac_util.h"
#include "network_main.h"

int Start_A_Network_Game_From_Single_Player()
{
#ifndef SUBTARGET
	PRINTSTRING("Just entered Start_A_Network_Game_From_Single_Player\n");
	FAKE_DEATHARREST();
	WAIT(0);
	WAIT(0);
	if (*(bool*)getGlobalPtrAtIndex(19))
	{
		if (!NETWORK_STORE_SINGLE_PLAYER_GAME())
		{
			return 0;
		}
	}
	SHUTDOWN_AND_LAUNCH_NETWORK_GAME(*(uint*)getGlobalPtrAtIndex(15));
	WAIT(0);
	return 1;
#elif SUBTARGET==SUBTARGET_TLAD
	PRINTSTRING("Just entered Start_A_Network_Game_From_Single_Player\n");
	FAKE_DEATHARREST();
	WAIT(0);
	WAIT(0);
	if (*(bool*)getGlobalPtrAtIndex(21))
	{
		if (!NETWORK_STORE_SINGLE_PLAYER_GAME())
		{
			return 0;
		}
	}
	SHUTDOWN_AND_LAUNCH_NETWORK_GAME(*(uint*)getGlobalPtrAtIndex(16));
	WAIT(0);
	return 1;
#elif SUBTARGET==SUBTARGET_TBOGT
	PRINTSTRING("Just entered Start_A_Network_Game_From_Single_Player\n");
	FAKE_DEATHARREST();
	WAIT(0);
	WAIT(0);
	if (*(bool*)getGlobalPtrAtIndex(21))
	{
		if (!NETWORK_STORE_SINGLE_PLAYER_GAME())
		{
			return 0;
		}
	}
	uint NextEpisode = *(uint*)getGlobalPtrAtIndex(16);
	if (GET_CURRENT_EPISODE() != NextEpisode)
	{
		if (NextEpisode == 0)
		{
			uint* p = (uint*)getPtrImmIndex(getGlobalPtrAtIndex(95), 396);
			if (*p != 0)
				*p = 0;
		}
		else if (NextEpisode == 1)
		{
			uint* p = (uint*)getPtrImmIndex(getGlobalPtrAtIndex(95), 396);
			if (*p != 13)
				*p = 13;
		}
	}
	SHUTDOWN_AND_LAUNCH_NETWORK_GAME(NextEpisode);
	WAIT(0);
	return 1;
#endif
}

int Start_A_Replay_From_Single_Player()
{
#ifndef SUBTARGET
	PRINTSTRING("Just entered Start_A_Replay_From_Single_Player\n");
	FAKE_DEATHARREST();
	WAIT(0);
	WAIT(0);
	ACTIVATE_REPLAY_MENU();
	if (*(bool*)getGlobalPtrAtIndex(19))
	{
		NETWORK_STORE_SINGLE_PLAYER_GAME();
	}
	return 0;
#elif SUBTARGET==SUBTARGET_TLAD
	PRINTSTRING("Just entered Start_A_Replay_From_Single_Player\n");
	FAKE_DEATHARREST();
	WAIT(0);
	WAIT(0);
	ACTIVATE_REPLAY_MENU();
	if (*(bool*)getGlobalPtrAtIndex(21))
	{
		NETWORK_STORE_SINGLE_PLAYER_GAME();
	}
	return 0;
#elif SUBTARGET==SUBTARGET_TBOGT
	PRINTSTRING("Just entered Start_A_Replay_From_Single_Player\n");
	FAKE_DEATHARREST();
	WAIT(0);
	WAIT(0);
	ACTIVATE_REPLAY_MENU();
	if (*(bool*)getGlobalPtrAtIndex(21))
	{
		NETWORK_STORE_SINGLE_PLAYER_GAME();
	}
	return 0;
#endif
}

void UpdateFlow()
{
#ifndef SUBTARGET
	if (GET_GFWL_IS_RETURNING_TO_SINGLE_PLAYER())
	{
		SET_GFWL_IS_RETURNING_TO_SINGLE_PLAYER(0);
		if (GET_GFWL_HAS_SAFE_HOUSE())
		{
			NETWORK_STORE_SINGLE_PLAYER_GAME();
		}
	}
	else if (*(bool*)getGlobalPtrAtIndex(19) && (!GET_GFWL_HAS_SAFE_HOUSE()))
	{
		PRINTSTRING("\n [rw][gfwl]  \n");
		SET_GFWL_HAS_SAFE_HOUSE(1);
	}
	if (*(bool*)getGlobalPtrAtIndex(10)) // g_bWantToShutdownForNetworkGame
	{
		*(bool*)getGlobalPtrAtIndex(10) = 0;
		Start_A_Network_Game_From_Single_Player();
	}
	if (*(bool*)getGlobalPtrAtIndex(13)) // g_bStartReplay
	{
		*(bool*)getGlobalPtrAtIndex(13) = 0;
		Start_A_Replay_From_Single_Player();
	}
#elif SUBTARGET==SUBTARGET_TLAD
	if (GET_GFWL_IS_RETURNING_TO_SINGLE_PLAYER())
	{
		SET_GFWL_IS_RETURNING_TO_SINGLE_PLAYER(0);
		if (GET_GFWL_HAS_SAFE_HOUSE())
		{
			NETWORK_STORE_SINGLE_PLAYER_GAME();
		}
	}
	else if (*(bool*)getGlobalPtrAtIndex(21) && (!GET_GFWL_HAS_SAFE_HOUSE()))
	{
		PRINTSTRING("\n [rw][gfwl]  \n");
		SET_GFWL_HAS_SAFE_HOUSE(1);
	}
	if (*(bool*)getGlobalPtrAtIndex(11)) // g_bWantToShutdownForNetworkGame
	{
		*(bool*)getGlobalPtrAtIndex(11) = 0;
		Start_A_Network_Game_From_Single_Player();
	}
	if (*(bool*)getGlobalPtrAtIndex(14)) // g_bStartReplay
	{
		*(bool*)getGlobalPtrAtIndex(14) = 0;
		Start_A_Replay_From_Single_Player();
	}
#elif SUBTARGET==SUBTARGET_TBOGT
	if (*(bool*)getGlobalPtrAtIndex(11)) // g_bWantToShutdownForNetworkGame
	{
		*(bool*)getGlobalPtrAtIndex(11) = 0;
		Start_A_Network_Game_From_Single_Player();
	}
	if (*(bool*)getGlobalPtrAtIndex(14)) // g_bStartReplay
	{
		*(bool*)getGlobalPtrAtIndex(14) = 0;
		Start_A_Replay_From_Single_Player();
	}
#endif
}

void UpdatePlayerWeapons(Ped ped)
{
	UpdateWeaponOfPed(ped, WEAPON_KNIFE);
	UpdateWeaponOfPed(ped, WEAPON_MOLOTOV);
	UpdateWeaponOfPed(ped, WEAPON_DEAGLE);
	UpdateWeaponOfPed(ped, WEAPON_SHOTGUN);
	UpdateWeaponOfPed(ped, WEAPON_MP5);
	UpdateWeaponOfPed(ped, WEAPON_AK47);
}

void SinglePlayer()
{
	uint InitialThread = LoadScript("initial", 1024);
	WAIT(0);
	while (IS_THREAD_ACTIVE(InitialThread)) WAIT(0);

	// BUG FIX: We don't want terrorist attack messages
	CLEAR_NEWS_SCROLLBAR();

	// Clear scenario blocking areas to be safe
	FLUSH_SCENARIO_BLOCKING_AREAS();

	SET_INT_STAT(STAT_ISLANDS_UNLOCKED, 3);
	SWITCH_ROADS_ON(540.11150000, 1447.76600000, 8.65554200, 598.03060000, 1528.56000000, 20.00804000);

	SWITCH_AMBIENT_PLANES(TRUE);
	SWITCH_GARBAGE_TRUCKS(TRUE);
	SWITCH_RANDOM_BOATS(TRUE);
	SWITCH_RANDOM_TRAINS(TRUE);
	ALLOW_EMERGENCY_SERVICES(TRUE);
	SET_CREATE_RANDOM_COPS(TRUE);
	SET_MAX_WANTED_LEVEL(6);
	SET_PED_DENSITY_MULTIPLIER(1.0f);
	SET_CAR_DENSITY_MULTIPLIER(1.0f);
	SET_TIME_OF_DAY(0, 0);
	UNLOCK_LAZLOW_STATION();
	FORCE_NEXT_STATION_LAZLOW(false);

	UpdatePlayerWeapons(GetPlayerPed());

	SetPlayerEnabled(GET_PLAYER_ID(), true);

	SET_PLAYER_CONTROL(GetPlayerIndex(), true);

	SET_GAME_CAM_HEADING(0.0f);

	REMOVE_IPL("Shipintro");
	PICKUPS_PASS_TIME(9999999);

#if 0
	REQUEST_MODEL(VEHICLE_ROM);
	//REQUEST_MODEL(PED_IG_ROMAN);

	while (!HAS_MODEL_LOADED(VEHICLE_ROM) /*|| !HAS_MODEL_LOADED(PED_IG_ROMAN)*/) WAIT(0);

	Vehicle c;
	CREATE_CAR(VEHICLE_ROM, 757.0331f, -215.885f, 4.6191f, &c, TRUE);
	CHANGE_CAR_COLOUR(c, 0, 1);
	SET_EXTRA_CAR_COLOURS(c, 1, 0);
	SET_CAR_STRONG(c, 1);
	SET_VEH_HAS_STRONG_AXLES(c, 1);
	SET_VEHICLE_DIRT_LEVEL(c, 15.9f);
	CHANGE_CAR_COLOUR(c, 0, 0);
	SET_EXTRA_CAR_COLOURS(c, 1, 0);
	SET_CAR_HEADING(c, 338.0f);
	SET_CAR_ON_GROUND_PROPERLY(c);

#if 0
	Ped Roman;
	CREATE_CHAR(RELATIONSHIP_GROUP_MISSION_3, PED_IG_ROMAN, 769.3871f, -259.3301f, 4.5813f, &Roman, TRUE);
	SET_CHAR_HEADING(Roman, 329.54f);
	SET_CHAR_SUFFERS_CRITICAL_HITS(Roman, FALSE);
	SET_CHAR_CANT_BE_DRAGGED_OUT(Roman, TRUE);
	SET_CHAR_NEVER_TARGETTED(Roman, TRUE);
	SET_CHAR_MAX_TIME_IN_WATER(Roman, 10.0f);
	SET_CHAR_MAX_TIME_UNDERWATER(Roman, 10.0f);

	SET_CHAR_COMPONENT_VARIATION(Roman, 0, 0, 0);
	SET_CHAR_COMPONENT_VARIATION(Roman, 0, 1, 0);
	SET_CHAR_COMPONENT_VARIATION(Roman, 0, 2, 0);
	SET_CHAR_COMPONENT_VARIATION(Roman, 0, 5, 0);
	SET_CHAR_COMPONENT_VARIATION(Roman, 0, 4, 0);
	SET_CHAR_COMPONENT_VARIATION(Roman, 0, 3, 0);
	SET_CHAR_COMPONENT_VARIATION(Roman, 0, 7, 0);
	CLEAR_CHAR_PROP(Roman, 0);
	CLEAR_CHAR_PROP(Roman, 1);

	SET_CHAR_STAY_IN_CAR_WHEN_JACKED(Roman, TRUE);
	SET_CHAR_RELATIONSHIP_GROUP(Roman, 23);
	SET_RELATIONSHIP(0, 23, 0);
	SET_ROMANS_MOOD(3);
	WARP_CHAR_INTO_CAR_AS_PASSENGER(Roman, c, 0);
	SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(Roman, FALSE);
	SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN(Roman, FALSE);
	SET_CHAR_SUFFERS_CRITICAL_HITS(Roman, TRUE);

	MARK_CAR_AS_NO_LONGER_NEEDED(&c);
#endif

	MARK_MODEL_AS_NO_LONGER_NEEDED(VEHICLE_ROM);
	//MARK_MODEL_AS_NO_LONGER_NEEDED(PED_IG_ROMAN);
#endif

	SET_TIME_OF_DAY(4, 30);

	FadeIn(1000);
}

void main()
{
	THIS_SCRIPT_IS_SAFE_FOR_NETWORK_GAME();

	SinglePlayer();

	while (true)
	{
		UpdateFlow();

		WAIT(100);
	}

	TERMINATE_THIS_SCRIPT();
}
