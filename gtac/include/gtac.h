
#pragma once

#include "types.h"
#include "constants.h"

//Fix for intellisense nonsense
#ifndef _MSC_VER
#define _native __attribute((native))
#define _native32(hash) __attribute((native(hash)))
#define l ;
#else
#define _native
#define _native32(hash)
#define l {};
#endif

extern _native32(0xE4E5A304) bool NETWORK_HOST_GAME_GTAC(void)l
extern _native32(0x4B18792D) bool NETWORK_IS_GAME_GTAC(void)l
extern _native32(0x84833DDB) bool GTAC_IS_NETWORK_SESSION(void)l
extern _native32(0x320B41D4) bool GTAC_IS_MULTIPLAYER_GAME(void)l
extern _native32(0x1EFE3826) void GTAC_JOIN(void)l
extern _native32(0xC3DA6B16) bool GTAC_IS_JOINED(void)l
extern _native32(0x75BC7E97) uint GTAC_START_NEW_SCRIPT(char* name)l
//extern _native32(0x0A2E0469) void GTAC_TRIGGER_INGAME(void)l
//extern _native32(0x2849DCA3) void GTAC_START_INGAME(bool bRestarted)l
//extern _native32(0xCB920024) void GTAC_FIND_GAME(int Gamemode, bool bRanked, int Episode, int MaxTeams)l
extern _native32(0xEC894190) bool GTAC_GET_CVAR_BOOLEAN(char* name, bool bDefaultValue)l
extern _native32(0xEA034C83) void GTAC_SET_CHAT_WINDOW_ENABLED(bool bEnabled)l
extern _native32(0xD4874676) bool GTAC_IS_CHAT_WINDOW_ENABLED(void)l
extern _native32(0xA7954E0C) bool GTAC_ARE_TRAINERS_DISALLOWED(void)l
extern _native32(0x79023CFC) bool GTAC_LOG(const char* psz)l
extern _native32(0xABCB0B59) uint GTAC_GET_MAX_PLAYERS(void)l
extern _native32(0x390C97BE) void GTAC_REGISTER_HOST_BROADCAST_VARIABLES(void* pMemory, int Count, int ID)l
extern _native32(0xC59C5372) void FORCE_NEXT_STATION_LAZLOW(bool bForced)l
extern _native32(0x89315432) void SET_LOADING_TEXT(char* pszText)l
extern _native32(0xFA43CB89) void SET_GTAC_LOADING_TEXT(void)l

#undef _native
#undef _native32
#undef l
