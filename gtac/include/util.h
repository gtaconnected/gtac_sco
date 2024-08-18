/*	---------------------------------------------------------------
	 This header contains GTAIV/EFLC PC script common functions.

	 This file is a part of scocl project (C) Alexander Blade 2011
	---------------------------------------------------------------  */

#pragma once

#include "natives.h"
#include "constants.h"

Player GetPlayerIndex(void)
{
	return GET_PLAYER_ID();
}

Ped GetPlayerPed(void)
{
	Ped playerped = INVALID_HANDLE;
	if ( PLAYER_HAS_CHAR(GetPlayerIndex()) )
		GET_PLAYER_CHAR(GetPlayerIndex(), &playerped);
	return playerped;
}

Ped GetPlayerChar(void)
{
	Ped pPed;

	GET_PLAYER_CHAR(CONVERT_INT_TO_PLAYERINDEX(GET_PLAYER_ID()), &pPed);
	return pPed;
}

Ped GetPlayerCharFromIndex(int i)
{
	Ped pPed;

	GET_PLAYER_CHAR(CONVERT_INT_TO_PLAYERINDEX(i), &pPed);
	return pPed;
}

Player GetPlayerFromIndex(int i)
{
	return CONVERT_INT_TO_PLAYERINDEX(i);
}

Player GetPlayer(void)
{
	return CONVERT_INT_TO_PLAYERINDEX(GET_PLAYER_ID());
}

void SetPlayerEnabled(int PlayerIndex, bool bEnabled)
{
	SET_PLAYER_CONTROL_FOR_NETWORK(GetPlayerFromIndex(PlayerIndex), bEnabled, 0);
	if (bEnabled)
	{
		if (!IS_CHAR_VISIBLE(GetPlayerCharFromIndex(PlayerIndex)))
		{
			SET_CHAR_VISIBLE(GetPlayerCharFromIndex(PlayerIndex), 1);
		}
		if (!IS_CHAR_IN_ANY_CAR(GetPlayerCharFromIndex(PlayerIndex)))
		{
			SET_CHAR_COLLISION(GetPlayerCharFromIndex(PlayerIndex), 1);
		}
		FREEZE_CHAR_POSITION(GetPlayerCharFromIndex(PlayerIndex), 0);
		SET_CHAR_NEVER_TARGETTED(GetPlayerCharFromIndex(PlayerIndex), 0);
		SET_PLAYER_INVINCIBLE(GetPlayerFromIndex(PlayerIndex), 0);
	}
	else
	{
		if (IS_CHAR_VISIBLE(GetPlayerCharFromIndex(PlayerIndex)))
		{
			SET_CHAR_VISIBLE(GetPlayerCharFromIndex(PlayerIndex), 0);
		}
		SET_CHAR_COLLISION(GetPlayerCharFromIndex(PlayerIndex), 0);
		FREEZE_CHAR_POSITION(GetPlayerCharFromIndex(PlayerIndex), 1);
		SET_CHAR_NEVER_TARGETTED(GetPlayerCharFromIndex(PlayerIndex), 1);
		SET_PLAYER_INVINCIBLE(GetPlayerFromIndex(PlayerIndex), 1);
		REMOVE_PTFX_FROM_PED(GetPlayerCharFromIndex(PlayerIndex));
		if (!IS_CHAR_FATALLY_INJURED(GetPlayerCharFromIndex(PlayerIndex)))
		{
			CLEAR_CHAR_TASKS_IMMEDIATELY(GetPlayerCharFromIndex(PlayerIndex));
		}
	}
}

uint GetCharModel(Ped Char)
{
	uint Model;

	GET_CHAR_MODEL(Char, &Model);
	return Model;
}

bool BeginServerCode()
{
	if (IS_THIS_MACHINE_THE_SERVER())
	{
		SET_THIS_MACHINE_RUNNING_SERVER_SCRIPT(true);
		return true;
	}
	return false;
}

void EndServerCode()
{
	SET_THIS_MACHINE_RUNNING_SERVER_SCRIPT(false);
}

void SetAdvertiseSession(bool bAdvertise)
{
	if (IS_THIS_MACHINE_THE_SERVER())
	{
		if (NETWORK_IS_SESSION_ADVERTISE() != bAdvertise)
		{
			NETWORK_ADVERTISE_SESSION(bAdvertise);
		}
	}
}

uint GetWeaponTypeModel(int WeaponType)
{
	uint Model;
	GET_WEAPONTYPE_MODEL(WeaponType, &Model);
	return Model;
}

void UpdateWeaponOfPed(Ped ped, Weapon weapon)
{
	if (HAS_CHAR_GOT_WEAPON(ped, weapon))
	{
		SET_CHAR_AMMO(ped, weapon, AMMO_MAX);    
	} 	else
	{
		GIVE_WEAPON_TO_CHAR(ped, weapon, AMMO_MAX, FALSE);	
	}
}

uint LoadScript(char* name, uint stacksize)
{
	REQUEST_SCRIPT(name);
	while (!HAS_SCRIPT_LOADED(name)) WAIT(0);
	uint script = START_NEW_SCRIPT(name, stacksize);
	MARK_SCRIPT_AS_NO_LONGER_NEEDED(name);
	return script;
}

void FadeIn(uint Time)
{
	if (!IS_SCREEN_FADED_IN())
	{
		DO_SCREEN_FADE_IN(Time);

		while (IS_SCREEN_FADING()) WAIT(0);
	}
}

void FadeOut(uint Time)
{
	if (!IS_SCREEN_FADED_OUT())
	{
		DO_SCREEN_FADE_OUT(Time);

		while (IS_SCREEN_FADING()) WAIT(0);
	}
}
