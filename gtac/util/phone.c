
#include "types.h"
#include "constants.h"
#include "intrinsics.h"
#include "natives.h"
#include "common.h"
#include "gtac.h"
#include "util.h"
#include "phone.h"

void GiveContact(int Contact, bool bSilent)
{
	if (!g_PhoneContacts[Contact].m_Entry.m_bExists)
	{
		g_PhoneContacts[Contact].m_Entry.m_bExists = true;

		if (!bSilent)
		{
			char szBuffer[16];
			strcpy(szBuffer, "CONT_", 16);
			stradd(szBuffer, g_PhoneContacts[Contact].m_Entry.m_szID, 16);
			SET_PHONE_HUD_ITEM(2, szBuffer, -1);
		}
	}
}

bool IsPlayerCallingContact(int Contact, bool b)
{
	if (IS_SCRIPTED_CONVERSATION_ONGOING())
	{
		DebugPrint("\n IS_PLAYER_CALLING_CONTACT - Scripted Conversation ongoing");
		return false;
	}
	switch (g_SpeechControlStatus)
	{
		case 4:
		case 1:
		case 2:
			DebugPrint("\n IS_PLAYER_CALLING_CONTACT - speech control is streaming");
			return false;
			break;
	}
	if (g_Cellphone.m_State == 1005 && g_Cellphone.m_Contact == Contact)
	{
		if (b)
		{
			if (g_Cellphone.m_Unknown508 >= 4 && !g_Cellphone.m_bMissionAnsweredPhone)
			{
				return true;
			}
		}
		else if (!g_Cellphone.m_Unknown368)
		{
			return true;
		}
	}
	return false;
}

bool IsPhoneReadyToAnswerContact(int Contact)
{
	if (Contact == 57)
		return false;
	return g_PhoneCall.m_Contact != Contact;
}

void DebugPrint(const char* psz)
{
}

void DebugPrintParam(const char* psz, const char* pszParam)
{
}

void CopyContactName(int i, char* pszBuffer)
{
	switch (i)
	{
		case 0:
			strcpy(pszBuffer, "ROMAN", 32);
			break;
		case 1:
			strcpy(pszBuffer, "VLAD", 32);
			break;
		case 2:
			strcpy(pszBuffer, "MICHELLE", 32);
			break;
		case 3:
			strcpy(pszBuffer, "JACOB", 32);
			break;
		case 4:
			strcpy(pszBuffer, "FAUSTIN", 32);
			break;
		case 5:
			strcpy(pszBuffer, "MANNY", 32);
			break;
		case 6:
			strcpy(pszBuffer, "ELIZABETA", 32);
			break;
		case 7:
			strcpy(pszBuffer, "DWAYNE", 32);
			break;
		case 8:
			strcpy(pszBuffer, "BRUCIE", 32);
			break;
		case 9:
			strcpy(pszBuffer, "PLAYBOY", 32);
			break;
		case 10:
			strcpy(pszBuffer, "KATE_MCREARY", 32);
			break;
		case 11:
			strcpy(pszBuffer, "FRANCIS_MCREARY", 32);
			break;
		case 12:
			strcpy(pszBuffer, "CIA_CHARACTER", 32);
			break;
		case 13:
			strcpy(pszBuffer, "PACKIE_MCREARY", 32);
			break;
		case 14:
			strcpy(pszBuffer, "RAY_BOCCINO", 32);
			break;
		case 15:
			strcpy(pszBuffer, "GERRY_MCREARY", 32);
			break;
		case 16:
			strcpy(pszBuffer, "DERRICK_MCREARY", 32);
			break;
		case 18:
			strcpy(pszBuffer, "BERNIE", 32);
			break;
		case 19:
			strcpy(pszBuffer, "BELL", 32);
			break;
		case 22:
			strcpy(pszBuffer, "JIMMY_PEGORINO", 32);
			break;
		case 20:
			strcpy(pszBuffer, "GRAVELLI", 32);
			break;
		case 25:
			strcpy(pszBuffer, "DIMITRI", 32);
			break;
		case 26:
			strcpy(pszBuffer, "MALLORIE", 32);
			break;
		case 27:
		case 42:
			strcpy(pszBuffer, "GRACIE", 32);
			break;
		case 28:
			strcpy(pszBuffer, "ALEX", 32);
			break;
		case 29:
			strcpy(pszBuffer, "KIKI", 32);
			break;
		case 30:
			strcpy(pszBuffer, "CARMEN", 32);
			break;
		case 35:
			strcpy(pszBuffer, "RECEPTIONIST_F", 32);
			break;
		case 36:
			strcpy(pszBuffer, "BLACKMAILER_M", 32);
			break;
		case 37:
			strcpy(pszBuffer, "TOM", 32);
			break;
		case 38:
			strcpy(pszBuffer, "REAL_BADMAN", 32);
			break;
		case 39:
			strcpy(pszBuffer, "BRIAN", 32);
			break;
		case 40:
			strcpy(pszBuffer, "PI_CHERISE", 32);
			break;
		case 41:
			strcpy(pszBuffer, "PI_ED_LOW", 32);
			break;
		case 43:
			strcpy(pszBuffer, "HOSSAN", 32);
			break;
		case 44:
			strcpy(pszBuffer, "PI_ILYENA", 32);
			break;
		case 45:
			strcpy(pszBuffer, "IVAN", 32);
			break;
		case 46:
			strcpy(pszBuffer, "PI_JEFF", 32);
			break;
		case 47:
			strcpy(pszBuffer, "PI_MARLENE", 32);
			break;
		case 48:
			strcpy(pszBuffer, "CLARENCE", 32);
			break;
		case 49:
			strcpy(pszBuffer, "PI_MEL", 32);
			break;
		case 50:
			strcpy(pszBuffer, "PATHOS", 32);
			break;
		case 51:
			strcpy(pszBuffer, "SARA", 32);
			break;
		case 52:
			strcpy(pszBuffer, "GORDON", 32);
			break;
		case 53:
			strcpy(pszBuffer, "DARKO_BREVIC", 32);
			break;
		case 21:
			strcpy(pszBuffer, "LAZLOW", 32);
			break;
		case 17:
			strcpy(pszBuffer, "FIXER", 32);
			break;
		default:
			strcpy(pszBuffer, "", 32);
			if (i != 56)
			{
			}
			break;
	}
}

void CopyPlayerName(char* pszBuffer)
{
	strcpy(pszBuffer, "NIKO", 16);
}

bool SetupAudioPhoneCall(uint Contact, uint Labels1Count, PhoneLabel* rgpLabels1, const char* pszDialog,
	uint uParam3, uint Labels2Count, PhoneLabel* rgpLabels2, uint Labels3Count, PhoneLabel* rgpLabels3,
	const char* uParam6, uint uParam7, bool bMissionCall, uint uParam9, uint uParam10,
	bool bOverrideCellphoneChecks, uint uParam12, uint uParam13)
{
	int I;

	if (g_Cellphone.m_Unknown540)
		return false;

	DebugPrint("\n SETUP_AUDIO_PHONE_CALL has been called");
	if (IS_SCRIPTED_CONVERSATION_ONGOING())
	{
		if (g_SpeechPriority >= 6)
		{
			DebugPrint("\n scripted conversation is ongoing and priority is high");
			return false;
		}
	}
	if (!IS_PLAYER_PLAYING(GetPlayer()))
	{
		DebugPrint("\n player is not playing");
		return false;
	}
	if (IS_CHAR_IN_ANY_CAR(GetPlayerChar()) && !IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerChar()))
	{
		DebugPrint("\n player is in middle of getting in/out of a car");
		return false;
	}
	switch (g_SpeechControlStatus)
	{
		case 4:
		case 1:
		case 2:
			DebugPrint("\n speechControlStatus = SPEECH_CONTROL_STREAMING_MOBILE OR speechControlStatus = SPEECH_CONTROL_STREAMING_CONVERSATION");
			return false;
			break;
	}
	switch (uParam9)
	{
		case 0:
			if (!CanRingCellphone() && !bOverrideCellphoneChecks)
				return false;
			g_Cellphone.m_Contact = Contact;
			g_Cellphone.m_Unknown48 = 1;
			g_PhoneContacts[g_Cellphone.m_Contact].m_Entry.m_Unknown24 = 0;
			break;
		case 1:
			if (g_Cellphone.m_Unknown368)
			{
				if (g_Cellphone.m_bMissionAnsweredPhone || !bMissionCall)
				{
					DebugPrint("\n cellphone3Dstructure.missionAnsweredPhone OR (NOT missionCall)");
					return false;
				}
			}
			if (g_Cellphone.m_Contact != -1)
			{
				if (g_PhoneContacts[g_Cellphone.m_Contact].m_Entry.m_Unknown24 != 5 && g_PhoneContacts[g_Cellphone.m_Contact].m_Entry.m_Unknown24 != 4)
				{
					g_PhoneContacts[g_Cellphone.m_Contact].m_Entry.m_Unknown24 = 0;
				}
			}
			g_Cellphone.m_Unknown368 = 1;
			g_Cellphone.m_bMissionAnsweredPhone = bMissionCall;
			Contact = g_Cellphone.m_Contact;
			break;
		case 2:
			if (!CanRingCellphone() && !bOverrideCellphoneChecks)
				return 0;
			g_Cellphone.m_Contact = Contact;
			g_Cellphone.m_Unknown52 = 1;
			g_Cellphone.m_Unknown56 = 1;
			g_Cellphone.m_bMissionAnsweredPhone = 1;
			g_Cellphone.m_Unknown368 = 1;
			g_PhoneContacts[g_Cellphone.m_Contact].m_Entry.m_Unknown24 = 0;
			break;
	}

	if (IS_SCRIPTED_CONVERSATION_ONGOING())
		ABORT_SCRIPTED_CONVERSATION(0);

	CopyContactName(Contact, g_Cellphone.m_szCaller);
	CopyPlayerName(g_Cellphone.m_szAnswerer);
	g_Cellphone.m_Unknown380 = uParam10;
	g_Cellphone.m_bOverrideCellphoneChecks = bOverrideCellphoneChecks;
	g_Cellphone.m_Unknown420 = uParam12;
	g_Cellphone.m_Unknown424 = -1;
	g_Cellphone.m_Unknown364 = uParam3;
	strcpy(g_Cellphone.m_szDialog, pszDialog, 16);

	for (I = 0; I < g_PhoneLabels.m_Count; I++)
		strcpy(g_PhoneLabels.m_Labels[I].m_szName, "END", 16);

	for (I = 0; I < Labels1Count; I++)
	{
		strcpy(g_PhoneLabels.m_Labels[I].m_szName, rgpLabels1[I].m_szName, 16);
		DebugPrintParam("\n Telling phone we want to play these labels ", rgpLabels1[I].m_szName);
	}

	for (I = 0; I < g_Cellphone.m_Labels1Count; I++)
	{
		if (I < Labels2Count)
		{
			strcpy(g_Cellphone.m_Labels1[I].m_szName, rgpLabels2[I].m_szName, 16);
		}
		else
		{
			strcpy(g_Cellphone.m_Labels1[I].m_szName, "", 16);
		}
	}

	for (I = 0; I < g_Cellphone.m_Labels2Count; I++)
	{
		if (I < Labels3Count)
		{
			strcpy(g_Cellphone.m_Labels2[I].m_szName, rgpLabels3[I].m_szName, 16);
		}
		else
		{
			strcpy(g_Cellphone.m_Labels2[I].m_szName, "", 16);
		}
	}

	strcpy(g_Cellphone.m_szUnknown208, uParam6, 16);
	g_Cellphone.m_Unknown80 = uParam7;
	g_Cellphone.m_Unknown384 = 0;
	g_Cellphone.m_Unknown532 = uParam13;
	g_SpeechControlStatus = 4;
	return true;
}

bool SetupSimpleConversation(const char* pszLabels, const char* pszDialog, bool bPhoneCall)
{
	PhoneLabel Labels[2];
	strcpy(Labels[0].m_szName, pszLabels, 16);
	strcpy(Labels[1].m_szName, "END", 16);
	if (!COMPARE_STRING(pszLabels, "PLACEHOLDER"))
	{
		if (bPhoneCall)
		{
			return SetupAudioPhoneCall(g_Cellphone.m_Contact, 2, Labels, pszDialog, 0, 0, NULL, 0, NULL, "", 0, bPhoneCall, 1, 1, 0, 0, 0);
		}
		if (!g_Cellphone.m_Unknown368)
		{
			strcpy(g_Cellphone.m_Labels0[0].m_szName, pszDialog, 16);
			strcpy(g_Cellphone.m_Labels0[1].m_szName, pszLabels, 16);
			CopyContactName(g_Cellphone.m_Contact, g_Cellphone.m_szCaller);
			g_Cellphone.m_Unknown368 = 1;
			return true;
		}
	}
	return false;
}

bool SetupSimplePhoneCall(uint Contact, const char* pszLabels, const char* pszDialog, int uParam3, int uParam4)
{
	PhoneLabel Labels[2];
	strcpy(Labels[0].m_szName, pszLabels, 16);
	strcpy(Labels[1].m_szName, "END", 16);
	return SetupAudioPhoneCall(Contact, 2, Labels, pszDialog, 0, 0, NULL, 0, NULL, "", uParam3, 1, 0, 1, 0, 0, uParam4);
}

bool CanRingCellphone()
{
	if (g_Cellphone.m_Unknown48 || g_Cellphone.m_Unknown52)
	{
		return false;
	}
	if (g_Cellphone.m_Unknown40 == 0)
	{
		return false;
	}
	if (!PhoneCheck())
	{
		return false;
	}
	if (g_Unknown555 == 1)
	{
		return false;
	}
	return true;
}

bool PhoneCheck()
{
	bool b = false;
	if (!IS_PLAYER_PLAYING(GetPlayer()))
	{
		DebugPrint("\n PHONE SCREEN CHECK - player is not playing.");
		return false;
	}
	if (NETWORK_HAVE_SUMMONS())
	{
		DebugPrint("\n PHONE SCREEN CHECK - player has been summoned into another session.");
		return false;
	}
	if (g_Cellphone.m_bOverrideCellphoneChecks)
	{
		DebugPrint("\n PHONE CHECK - .cellphone3Dstructure.overrideCellphoneChecks is returning TRUE");
		return true;
	}
	if (g_Cellphone.m_bHideCellphone || g_Cellphone.m_bDisableCellphone)
	{
		DebugPrint("\n PHONE CHECK - .hideCellphone OR .disableCellphone are returning TRUE.");
		return false;
	}
	if (!IS_PLAYER_FREE_FOR_AMBIENT_TASK(GetPlayer()))
	{
		if (!IS_CHAR_IN_ANY_CAR(GetPlayerChar()))
		{
			int Status;
			GET_SCRIPT_TASK_STATUS(GetPlayerChar(), 53, &Status);
			switch (Status)
			{
				case 7:
				case 2:
					DebugPrint("\n PHONE CHECK - player is not free for an ambient task and is not in a car)");
					return false;
					break;
				default:
					if (!IS_CHAR_IN_WATER(GetPlayerChar()))
					{
						b = true;
					}
					else
					{
						DebugPrint("\n PHONE CHECK - player is in water");
						return false;
					}
					break;
			}
		}
	}
	if (CODE_WANTS_MOBILE_PHONE_REMOVED() && !b)
	{
		DebugPrint("\n PHONE CHECK - CODE_WANTS_MOBILE_PHONE_REMOVED() is returning TRUE.");
		return false;
	}
	if (!IS_PLAYER_SCRIPT_CONTROL_ON(GetPlayer()))
	{
		DebugPrint("\n PHONE CHECK - IS_PLAYER_SCRIPT_CONTROL_ON is returning FALSE.");
		return false;
	}
	return true;
}

int GetLastContactUnknown24()
{
	if (g_Cellphone.m_Contact != -1)
	{
		return g_PhoneContacts[g_Cellphone.m_Contact].m_Entry.m_Unknown24;
	}
	return 6;
}

void RestorePhoneScriptValues()
{
	GTAC_LOG("RestorePhoneScriptValues");
	CreateSizedArray(int, ScriptValues, 10, 0);
	if (RESTORE_SCRIPT_VALUES_FOR_NETWORK_GAME(&ScriptValues))
	{
		g_Cellphone.m_Unknown40 = ScriptValues.items[0];
		g_Cellphone.m_Unknown108 = ScriptValues.items[1];
		g_Cellphone.m_Unknown112 = ScriptValues.items[2];
		SET_MOBILE_RING_TYPE(g_Cellphone.m_Unknown112);
		g_Cellphone.m_Unknown396 = ScriptValues.items[3];
		uint Episode = GET_CURRENT_EPISODE();
		if (Episode == 0 && ScriptValues.items[3] == 13)
			g_Cellphone.m_Unknown396 = 0;
		else if (Episode == 1 && ScriptValues.items[3] < 13)
			g_Cellphone.m_Unknown396 = 13;
		g_Cellphone.m_bIsHiDef = ScriptValues.items[4] != 0;
		if (ScriptValues.items[5] == 1)
			g_Cellphone.m_Unknown524 = 1;
		else
			g_Cellphone.m_Unknown524 = 0;
		g_Cellphone.m_Unknown656 = ScriptValues.items[6];
		if (ScriptValues.items[7] == 0)
			g_Cellphone.m_bZit = 1;
		else
			g_Cellphone.m_bZit = 0;
	}
	else
	{
		g_Cellphone.m_Unknown40 = 2;
		g_Cellphone.m_Unknown108 = 0;
		g_Cellphone.m_Unknown112 = 0;
		g_Cellphone.m_Unknown396 = 0;
		g_Cellphone.m_Unknown524 = 1;
		g_Cellphone.m_bIsHiDef = GET_IS_HIDEF();
		g_Cellphone.m_Unknown656 = -1;
		g_Cellphone.m_bZit = 0;
	}
	SET_MOBILE_RING_TYPE(g_Cellphone.m_Unknown112);
}

void DeleteEmail(uint Index)
{
	g_Emails[Index].m_Unknown4[0] = -1;
	g_Emails[Index].m_Unknown4[1] = -1;
	g_Emails[Index].m_Unknown4[2] = -1;
}

global(1502) int g_Unknown1502Count;
global(1503) int g_Unknown1502[1];

void sub_31159(int iParam0, int iParam1)
{
	int i = iParam0 % 1000;
	SET_BITS_IN_RANGE(&g_Unknown1502[i / 16], (i % 16) * 2, ((i % 16) * 2) + 1, iParam1);
}

void sub_31107()
{
	for (size_t i = 0; i < g_Unknown1502Count; i++)
	{
		g_Unknown1502[i] = 0;
	}

	sub_31159(1015, 2);
	sub_31159(1023, 2);
	sub_31159(2034, 2);
	sub_31159(4, 1);
	sub_31159(9, 3);
	sub_31159(1021, 2);
	sub_31159(1024, 2);
	sub_31159(1025, 3);
	sub_31159(2029, 1);
	sub_31159(3038, 2);
	sub_31159(4049, 1);
}

global(955) int g_Unknown955Count;
global(956) int g_Unknown955[1];

void sub_31311()
{
	SET_BITS_IN_RANGE(getGlobalPtrAtIndex(953), 0, 2, 7);
	SET_BITS_IN_RANGE(getGlobalPtrAtIndex(953), 3, 5, 7);
	SET_BITS_IN_RANGE(getGlobalPtrAtIndex(953), 6, 8, 7);
	SET_BITS_IN_RANGE(getGlobalPtrAtIndex(953), 9, 11, 7);
	SET_BITS_IN_RANGE(getGlobalPtrAtIndex(953), 12, 14, 0);
	setGlobalAtIndex(954, 0);
	for (size_t i = 0; i < g_Unknown955Count; i++)
	{
		int* p = &g_Unknown955[i];
		SET_BITS_IN_RANGE(p, 0, 5, 63);
		SET_BITS_IN_RANGE(p, 6, 11, 63);
		SET_BITS_IN_RANGE(p, 12, 17, 63);
		SET_BITS_IN_RANGE(p, 18, 23, 63);
		SET_BITS_IN_RANGE(p, 24, 29, 63);
	}
	setGlobalAtIndex(963, 0);
	setGlobalAtIndex(964, 0);
}

global(1452) int g_Unknown1452Count;
global(1453) int g_Unknown1452[1];

void InitialLogic()
{
	for (size_t i = 0; i < 40; i++)
		DeleteEmail(i);

	setGlobalAtIndex(965, -1);
	setGlobalAtIndex(966, -1);
	setGlobalAtIndex(946, -1);

	setGlobalAtIndex(1434 + (64 / 4), -1);

	for (size_t i = 0; i < g_Unknown1452Count; i++)
	{
		g_Unknown1452[i] = 0;
	}

	SET_BIT(&g_Unknown1452[1], 21);
	SET_BITS_IN_RANGE(&g_Unknown1452[1], 0, 8, 0);
	SET_BITS_IN_RANGE(&g_Unknown1452[1], 22, 31, 1);

	g_Unknown1452[0] = 2;

	setGlobalAtIndex(1451, 1);

	//sub_31107();
	//sub_31311();
}
