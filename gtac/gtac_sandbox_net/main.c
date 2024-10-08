#include "types.h"
#include "constants.h"
#include "intrinsics.h"
#include "natives.h"
#include "common.h"
#include "gtac.h"
#include "util.h"
#include "gtac_util.h"

#define MAX_PLAYERS 32

/*
void RegisterRandomCharactersBrains()
{
    REGISTER_WORLD_POINT_SCRIPT_BRAIN("Arnaud1", 100.0);
    REGISTER_WORLD_POINT_SCRIPT_BRAIN("Arnaud2", 100.0);
    REGISTER_WORLD_POINT_SCRIPT_BRAIN("Margot1", 100.0);
    REGISTER_WORLD_POINT_SCRIPT_BRAIN("Margot2", 100.0);
    REGISTER_WORLD_POINT_SCRIPT_BRAIN("Daisy1", 100.0);
}

void RegisterBrains()
{
    ALLOCATE_SCRIPT_TO_OBJECT( "puzzle_launcher", 691499124, 100, 10.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "puzzle_launcher", -386570734, 100, 10.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "bowl_trigger", 1071999466, 100, 25.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "darts_launcher", 33267265, 100, 50.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "ATMobj", 943099328, 100, 30.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "ATMobj", 1646518682, 100, 30.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "ATMobj", -1707894766, 100, 30.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "CarWash", -582605513, 100, 50.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "ambBarrier", 21350196, 100, 100.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "till", -1321409645, 100, 100.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "vendor", 526100790, 100, 80.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "vendor", 1914818237, 100, 80.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "vendor", 1139438163, 100, 80.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "burgerVendor", 381327348, 100, 80.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "nutVendor", 1179300952, 100, 80.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "magVendor", -2047685421, 100, 80.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "magVendor", -1654925163, 100, 80.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "telescope", -1028473, 100, 2.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "sprunk", -2033273140, 100, 50.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "sprunk", -1702863313, 100, 50.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "computerStreamed", -681677032, 100, 3.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "computerStreamed", -1699088948, 100, 3.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "computerStreamed", -1185959097, 100, 3.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "computerStreamed", -805425417, 100, 5.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "pool_table", -1693860173, 100, 50.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "pool_table", 1823613694, 100, 50.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "pool_table", -1570172664, 100, 50.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "ambTV", -1618524073, 100, 80.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "ambTV", -1058927856, 100, 80.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "ambTV", 1243139908, 100, 80.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "ambTV", 900769396, 100, 80.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "ambTV", -1336305346, 100, 80.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "ambClubLights", 1005973733, 100, 50.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "ambClubLights", 1781111577, 100, 50.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "ambClubLights", -21824081, 100, 50.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "ambFunFair", -601413519, 100, 100.00000000, -1 );
    ALLOCATE_SCRIPT_TO_OBJECT( "air_hockey", 1948842064, 100, 50.00000000, -1 );
    RegisterRandomCharactersBrains();
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambATMQ", 50.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "EmpireTelescope", 80.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "EmpireDown", 80.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambTaxiHail", 50.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "copbootsearch", 80.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambgerry3doorlock", 5.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambSaveBed", 50.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambWardrobe", 25.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambnightclubext", 150.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "gunLockup", 50.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "gunLockupCT", 50.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambBar", 100.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "TollBooth", 200.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambBridgePatrol", 200.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambTunnelCops", 200.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambHotel", 50.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "foodServer", 80.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambInternetCafe", 50.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambCargoHoldDoors", 100.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambJerseyDocksGates", 100.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambBouncer", 150.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambStripClub", 60.00000000 );
    ALLOCATE_SCRIPT_TO_OBJECT( "ambPoleDancer", -132862690, 100, 50.00000000, -1 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambNightclubBM", 100.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambNightclubM9", 100.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambNightclubHC", 100.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambHomelandCordon", 200.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambChurchDoors", 100.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambLiftDoors", 100.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambToiletDoors", 25.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambJimsLocks", 100.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambPolRdBlk", 200.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "Ambblkhawk", 200.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambhelicopter", 200.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "Manhat_heli_tours", 200.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "drinking", 110.00000000 );
    SET_STATE_OF_CLOSEST_DOOR_OF_TYPE( 377940039, 892, 65092, 16, 1, 0.00000000 );
    SET_STATE_OF_CLOSEST_DOOR_OF_TYPE( -532546678, 892, 65095, 16, 1, 0.00000000 );
    SET_STATE_OF_CLOSEST_DOOR_OF_TYPE( 58767393, 24, 810, 15, 1, 0.00000000 );
    SET_STATE_OF_CLOSEST_DOOR_OF_TYPE( 422470524, 21, 810, 15, 1, 0.00000000 );
    SET_STATE_OF_CLOSEST_DOOR_OF_TYPE( 58767393, 12, 64877, 15, 1, 0.00000000 );
    SET_STATE_OF_CLOSEST_DOOR_OF_TYPE( 422470524, 9, 64877, 15, 1, 0.00000000 );
    SET_STATE_OF_CLOSEST_DOOR_OF_TYPE( -160085103, 65255, 1355, 26, 1, 0.00000000 );
    SET_STATE_OF_CLOSEST_DOOR_OF_TYPE( -160085103, 65261, 1360, 26, 1, 0.00000000 );
    SET_STATE_OF_CLOSEST_DOOR_OF_TYPE( -1452339441, 64535, 1223, 29, 1, 0 );
    SET_STATE_OF_CLOSEST_DOOR_OF_TYPE( -1452339441, 63582, 65475, 7, 1, 0.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "AmbWindowLift", 200.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "bowling_lane", 100.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambAirpotarea", 200.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambUNarea", 200.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambShowroom", 75.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "cablecars", 75.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambSecurityCameras", 100.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambPrisonWanted", 200.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambFoodEating", 100.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "ambDrinking", 100.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "FightClubLauncher", 50.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "golf_launcher", 100.00000000 );
    REGISTER_WORLD_POINT_SCRIPT_BRAIN( "raceSPLAUNCHER", 50.00000000 );
    ALLOCATE_SCRIPT_TO_RANDOM_PED( "garbage_trucks", 1136499716, 100, 0 );
    ALLOCATE_SCRIPT_TO_RANDOM_PED( "ambbeggar", -1080673049, 100, 1 );
    ALLOCATE_SCRIPT_TO_RANDOM_PED( "ambbeggar", -1827421800, 100, 1 );
    ALLOCATE_SCRIPT_TO_RANDOM_PED( "ambbeggar", -142386662, 100, 1 );
    ALLOCATE_SCRIPT_TO_RANDOM_PED( "ambpimpnpros", 552542187, 100, 1 );
    ALLOCATE_SCRIPT_TO_RANDOM_PED( "ambpimpnpros", 996267216, 100, 1 );
    ALLOCATE_SCRIPT_TO_RANDOM_PED( "ambdealer", 1448755353, 100, 1 );
    ALLOCATE_SCRIPT_TO_RANDOM_PED( "ambpreacher", 495499562, 100, 1 );
    ALLOCATE_SCRIPT_TO_RANDOM_PED( "ambpreacher", 379171768, 100, 1 );
    ALLOCATE_SCRIPT_TO_RANDOM_PED( "ambbusker", -1188246269, 100, 1 );
}*/

void CreateDefaultObjects()
{
    //RegisterBrains();

#if 0
	// Church door 1
	Object Object1;
	CREATE_OBJECT_NO_OFFSET(1845915705, -281.0644, -283.7, 15.8764, &Object1, 0);
	SET_OBJECT_HEADING(Object1, 90.0);
	FREEZE_OBJECT_POSITION(Object1, 1);

	// Church door 2
	Object Object2;
	CREATE_OBJECT_NO_OFFSET(-631715616, -281.0644, -280.7064, 15.8764, &Object2, 0);
	SET_OBJECT_HEADING(Object2, 90.0);
	FREEZE_OBJECT_POSITION(Object2, 1);

	// Bruice's door
	Object Object3;
	CREATE_OBJECT_NO_OFFSET(639246688, 864.32, -121.645, 7.4, &Object3, 0);
	SET_OBJECT_HEADING(Object3, 90.0);
	SET_OBJECT_DYNAMIC(Object3, 0);
	FREEZE_OBJECT_POSITION(Object3, 1);

	// Museum
	Object Object4;
	CREATE_OBJECT_NO_OFFSET(1312423945, -123.7264, 772.0226, 35.0513, &Object4, 0);
	SET_OBJECT_COORDINATES(Object4, -123.7264, 772.0226, 35.0513);
	SET_OBJECT_HEADING(Object4, 0.0);
	SET_OBJECT_DYNAMIC(Object4, 0);
	FREEZE_OBJECT_POSITION(Object4, 1);

	if (GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT("coop_swatasslt") == 0)
	{
		// Petrovic's plane
		Object Object5;
		CREATE_OBJECT_NO_OFFSET(223915744, 2394.496, 175.899, 5.858, &Object5, 0);
		SET_OBJECT_ROTATION(Object5, 0.0, 235., 240.375);
		SET_OBJECT_DYNAMIC(Object5, 0);
		FREEZE_OBJECT_POSITION(Object5, 1);
	}
#endif
}

void Initial()
{
	UNLOCK_LAZLOW_STATION();
	FORCE_NEXT_STATION_LAZLOW(false);
	ALLOW_GAME_TO_PAUSE_FOR_STREAMING(true);
	DISPLAY_PLAYER_NAMES(true);
	NETWORK_SET_HEALTH_RETICULE_OPTION(true);
	SWITCH_ARROW_ABOVE_BLIPPED_PICKUPS(1);
	REGISTER_SCRIPT_WITH_AUDIO(1);
	SET_ROCKET_LAUNCHER_FREEBIE_IN_HELI(1);
	USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR(1);
	SET_NO_RESPRAYS(0);

	EnablePopulation(false);

	SET_REDUCE_PED_MODEL_BUDGET(false);
	SET_REDUCE_VEHICLE_MODEL_BUDGET(false);
	SET_DITCH_POLICE_MODELS(false);

	//SET_SCENARIO_PED_DENSITY_MULTIPLIER(1, 1);
	SET_CREATE_RANDOM_COPS(true);

	CreateDefaultObjects();

	// Disable traffic at the airpot (it looks wrong in mp)
	SWITCH_ROADS_OFF(2351.24100000, 72.54793, 2.297226, 2227.933, 57.00667, 17.17584);
	SWITCH_ROADS_OFF(2227.93300000, 57.00667, 17.17584, 2116.494, 94.63986, 3.832578);
	SWITCH_ROADS_OFF(2116.49400000, 94.63986, 3.832578, 2134.089, 147.5496, 13.00724);
	SWITCH_ROADS_OFF(2351.24100000, 72.54793, 2.297226, 2367.599, 146.7534, 13.58018);
	SWITCH_ROADS_OFF(2398.44000000, 263.9303, 3.03577, 2425.464, 229.4469, 14.43351);
	SWITCH_ROADS_OFF(2463.91400000, 166.8288, -6.629227, 2385.221, 263.269, 22.66073);

	// Just to be safe
	FLUSH_SCENARIO_BLOCKING_AREAS();

	//ADD_SCENARIO_BLOCKING_AREA(-1184.825, -502.3984, 0.406377, -895.2747, -320.9838, 22.06192); // Prison
	//ADD_SCENARIO_BLOCKING_AREA(2047.142, 36.41048, -8.88823, 2852.104, 880.1101, 36.31237); // Airport
	//ADD_SCENARIO_BLOCKING_AREA(-1180, 470, 0, -1050, 630, 15); // Ferries
	//ADD_SCENARIO_BLOCKING_AREA(-415, -999, 0, -400, -980, 15); // Happiness island

	//DONT_DISPATCH_COPS_FOR_PLAYER(GET_PLAYER_ID(), true);
	//SWITCH_POLICE_HELIS(false);

	// Enable parked cars only
	//DISABLE_CAR_GENERATORS(false, false);
	//FORCE_GENERATE_PARKED_CARS_TOO_CLOSE_TO_OTHERS(0);
	//SET_PARKED_CAR_DENSITY_MULTIPLIER(1);
}

void SetupNetwork()
{
	if (BeginServerCode())
	{
		SET_SYNC_WEATHER_AND_GAME_TIME(false);

		if (!NETWORK_IS_SESSION_STARTED())
		{
			NETWORK_START_SESSION();
			while (NETWORK_START_SESSION_PENDING())
				WAIT(0);
		}

		EndServerCode();
	}
}

void UpdateNetworkGame()
{
	if (BeginServerCode())
	{
		for (int I = 0; I < MAX_PLAYERS; I++)
		{
			if (PLAYER_WANTS_TO_JOIN_NETWORK_GAME(I))
			{
				TELL_NET_PLAYER_TO_START_PLAYING(I, 0);
			}
		}

		EndServerCode();
	}
}

void Update()
{
	if (IS_NETWORK_GAME_RUNNING())
		UpdateNetworkGame();

	if (!IS_NETWORK_GAME_RUNNING())
	{
		if (!LOCAL_PLAYER_IS_READY_TO_START_PLAYING())
		{
			SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
			TERMINATE_THIS_SCRIPT();
		}
	}

	if (LOCAL_PLAYER_IS_READY_TO_START_PLAYING())
		LAUNCH_LOCAL_PLAYER_IN_NETWORK_GAME();
}

void main()
{
	THIS_SCRIPT_IS_SAFE_FOR_NETWORK_GAME();
	ALLOW_THIS_SCRIPT_TO_BE_PAUSED(false);

	Initial();

	if (IS_NETWORK_GAME_RUNNING())
		SetupNetwork();

	while (true)
	{
		WAIT(0);

		Update();
	}

	TERMINATE_THIS_SCRIPT();
}
