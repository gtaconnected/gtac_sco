
#include "types.h"
#include "constants.h"
#include "intrinsics.h"
#include "natives.h"
#include "common.h"
#include "phone.h"
#include "network_main.h"
#include "util.h"

void CreateDefaultParkedCars()
{
#ifndef SUBTARGET
	CREATE_CAR_GENERATOR(2247.489, 756.1506, 4.8309, 0.0f, 2.0f, 3.0, VEHICLE_ANNIHILATOR, -1, -1, -1, -1, 1, 0, 0, &g_rgNetworkCarGenerators[0]);
	CREATE_CAR_GENERATOR(2230.762, 737.585, 4.8309, 0.0f, 2.0f, 3.0, VEHICLE_ANNIHILATOR, -1, -1, -1, -1, 1, 0, 0, &g_rgNetworkCarGenerators[1]);
	CREATE_CAR_GENERATOR(2213.966, 719.4022, 4.8309, 0.0f, 2.0f, 3.0f, VEHICLE_ANNIHILATOR, -1, -1, -1, -1, 1, 0, 0, &g_rgNetworkCarGenerators[2]);
	CREATE_CAR_GENERATOR(2133.43, 441.1531, 22.7132, 0.0f, 2.0f, 3.0f, VEHICLE_ANNIHILATOR, -1, -1, -1, -1, 1, 0, 0, &g_rgNetworkCarGenerators[3]);
	CREATE_CAR_GENERATOR(346.0789, -716.9597, 3.6918, 0.0f, 2.0f, 3.0f, VEHICLE_ANNIHILATOR, -1, -1, -1, -1, 1, 0, 0, &g_rgNetworkCarGenerators[4]);
	CREATE_CAR_GENERATOR(390.2143, -743.7241, 3.6918, 0.0f, 2.0f, 3.0f, VEHICLE_ANNIHILATOR, -1, -1, -1, -1, 1, 0, 0, &g_rgNetworkCarGenerators[5]);
	CREATE_CAR_GENERATOR(387.269, -701.7766, 3.6919, 0.0f, 2.0f, 3.0f, VEHICLE_ANNIHILATOR, -1, -1, -1, -1, 1, 0, 0, &g_rgNetworkCarGenerators[6]);
	CREATE_CAR_GENERATOR(414.4829, -657.2979, 3.6919, 0.0f, 2.0f, 3.0f, VEHICLE_ANNIHILATOR, -1, -1, -1, -1, 1, 0, 0, &g_rgNetworkCarGenerators[7]);
	CREATE_CAR_GENERATOR(-708.6783, 357.5022, 3.0723, 0.0f, 2.0f, 3.0f, VEHICLE_ANNIHILATOR, -1, -1, -1, -1, 1, 0, 0, &g_rgNetworkCarGenerators[8]);
	CREATE_CAR_GENERATOR(-2125.715, 145.0991, 17.7131, 0.0f, 2.0f, 3.0f, VEHICLE_ANNIHILATOR, -1, -1, -1, -1, 1, 0, 0, &g_rgNetworkCarGenerators[9]);
#endif
}

void EndSession()
{
	if (IS_NETWORK_GAME_RUNNING())
	{
#ifndef SUBTARGET
		g_bEndingSession = true;
#endif
		FAKE_DEATHARREST();
		if (NETWORK_IS_SESSION_STARTED())
		{
			DebugPrint("\n #### networkSetup.sch - NETWORK_IS_SESSION_STARTED is returning TRUE. ");
			if (NETWORK_END_SESSION())
			{
				DebugPrint("\n #### networkSetup.sch - called NETWORK_END_SESSION. ");
				while (NETWORK_END_SESSION_PENDING())
				{
					WAIT(0);
					DebugPrint("\n #### networkSetup.sch - NETWORK_END_SESSION_PENDING is returning TRUE. ");
#ifndef SUBTARGET
					g_bEndingSession = true;
#endif
				}
			}
		}
		if (!NETWORK_IS_RENDEZVOUS() || NETWORK_HAVE_ACCEPTED_INVITE())
		{
			NETWORK_LEAVE_GAME();
			DebugPrint("\n #### networkSetup.sch - called NETWORK_LEAVE_GAME(). ");
			while (NETWORK_LEAVE_GAME_PENDING())
			{
				WAIT(0);
				DebugPrint("\n #### networkSetup.sch - NETWORK_LEAVE_GAME_PENDING is returning TRUE. ");
#ifndef SUBTARGET
				g_bEndingSession = true;
#endif
			}
		}
		else
		{
			DebugPrint("\n #### networkSetup.sch - not leaving game as NETWORK_IS_RENDEZVOUS is returning TRUE. ");
		}
	}
	else
	{
		DebugPrint("\n #### networkSetup.sch - IS_NETWORK_GAME_RUNNING is returning FALSE no need to clean up. ");
	}
}

void StoreNetworkScriptValues()
{
	CreateSizedArray(int, ScriptValues, 10, 0);
	ScriptValues.items[0] = g_Cellphone.m_Unknown40;
	ScriptValues.items[1] = g_Cellphone.m_Unknown108;
	ScriptValues.items[2] = g_Cellphone.m_Unknown112;
	ScriptValues.items[3] = g_Cellphone.m_Unknown396;
	if (g_Cellphone.m_bIsHiDef)
		ScriptValues.items[4] = 1;
	else
		ScriptValues.items[4] = 0;
	if (g_Cellphone.m_Unknown524)
		ScriptValues.items[5] = 1;
	else
		ScriptValues.items[5] = 0;
	ScriptValues.items[6] = g_Cellphone.m_Unknown656;
	if (g_PhoneContacts[21].m_Entry.m_Unknown0)
		ScriptValues.items[7] = 1;
	else
		ScriptValues.items[7] = 0;
	STORE_SCRIPT_VALUES_FOR_NETWORK_GAME(&ScriptValues);
}

void Start_A_Network_Game_From_A_Network_Game()
{
#ifndef SUBTARGET
	if (g_bRecheckLan)
	{
		g_bRecheckLan = false;
		NETWORK_SET_LAN_SESSION(GET_ONLINE_LAN());
	}
#endif
#if defined(SUBTARGET) && SUBTARGET==SUBTARGET_TBOGT
	if (GET_CURRENT_EPISODE() != g_NextEpisode)
	{
		switch (g_NextEpisode)
		{
			case 0:
				if (g_Cellphone.m_Unknown396 != 0)
					g_Cellphone.m_Unknown396 = 0;
				break;
			case 1:
				if (g_Cellphone.m_Unknown396 != 13)
					g_Cellphone.m_Unknown396 = 13;
				break;
			default:
				break;
		}
	}
#endif
	SHUTDOWN_AND_LAUNCH_NETWORK_GAME(g_NextEpisode);
	WAIT(0);
	TERMINATE_THIS_SCRIPT();
}

int GetGameModeMaxSlots(uint GameMode)
{
	switch (GameMode)
	{
		case 13:
		case 14:
		case 15:
			return 4;
	}
	return 32;
}

void CleanupNet()
{
	if (IS_NETWORK_GAME_RUNNING())
	{
		FAKE_DEATHARREST();
		if (NETWORK_IS_SESSION_STARTED())
		{
			if (NETWORK_END_SESSION())
			{
				while (NETWORK_END_SESSION_PENDING())
					WAIT(0);
			}
		}
		NETWORK_LEAVE_GAME();
		while (NETWORK_LEAVE_GAME_PENDING())
			WAIT(0);
	}
	MARK_STREAMED_TXD_AS_NO_LONGER_NEEDED("network");
}
