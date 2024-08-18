#pragma once

#define _pad(x,y) uchar x[y]

#ifndef _MSC_VER
#define PACKED __attribute__((packed))
#else
#define PACKED
#endif

typedef struct PACKED
{
	char m_szName[16];//0-16
} PhoneLabel;

typedef struct PACKED
{
	uint m_Count;//0-4
	PhoneLabel m_Labels[1];
} PhoneLabels;

typedef struct PACKED
{
	int m_Unknown0;//0-4
	bool m_bExists;//4-8
	int m_Unknown8;//8-12
	char m_szID[8];//12-20
	int m_Unknown20;//20-24
	int m_Unknown24;//24-28
} ContactEntry;

typedef struct PACKED
{
	int m_Unknown0;//0-4
	int m_Unknown4;//4-8
	_pad(__pad0, 32 - 8);//8-32
	bool m_bHasJob;//32-36
	bool m_bHasBoating;//36-40
	bool m_bHasBowling;//40-44
	bool m_bHasDarts;//44-48
	bool m_bHasDrinking;//48-52
	bool m_bHasEating;//52-56
	bool m_bHasHeliRide;//56-60
	bool m_bHasLifts;//60-64
	bool m_bHasPool;//64-68
	bool m_bHasShow;//68-72
	bool m_bHasStripClub;//72-76
	_pad(__pad1, 132 - 76);//76-132
	ContactEntry m_Entry;//132-160
	_pad(__pad2, 444 - 160);//160-444
} CellphoneContact;

typedef struct PACKED
{
	uint m_State;//0-4
	_pad(__pad0, 40 - 4);//4-40
	int m_Unknown40;//40-48
	int m_RenderId;//44-48
	int m_Unknown48;//48-52
	int m_Unknown52;//52-56
	int m_Unknown56;//56-60
	int m_Contact;//60-64
	_pad(__pad1, 80 - 64);//64-80
	int m_Unknown80;//80-84
	_pad(__pad2, 100 - 84);//84-100
	bool m_bHideCellphone;//100-104
	bool m_bDisableCellphone;//104-108
	int m_Unknown108;//108-112
	int m_Unknown112;//112-116
	_pad(__pad3, 128 - 116);//116-128
	char m_szDialedNumber[16];//128-144
	char m_szDialog[16];//144-160
	char m_szAnswerer[16];//160-176
	char m_szCaller[16];//176-192
	char m_szUnknown192[16];//192-208
	char m_szUnknown208[16];//208-224
	uint m_Labels0Count;//224-228
	PhoneLabel m_Labels0[2];//228-260
	uint m_Labels1Count;//260-264
	PhoneLabel m_Labels1[3];//264-312
	uint m_Labels2Count;//312-316;
	PhoneLabel m_Labels2[3];//316-364
	int m_Unknown364;//364-368
	bool m_Unknown368;//368-372
	uint m_bMissionAnsweredPhone;//372-376
	bool m_bOverrideCellphoneChecks;//376-380
	int m_Unknown380;//380-384
	int m_Unknown384;//384-388
	_pad(__pad7, 396 - 388);//388-396
	int m_Unknown396;//396-400
	_pad(__pad8, 420 - 400);//400-420
	int m_Unknown420;//420-424
	int m_Unknown424;//424-428
	_pad(__pad9, 500 - 428);//428-500
	bool m_bIsHiDef;//500-504
	int m_Unknown504;//500-504
	int m_Unknown508;//508-512
	_pad(__pad10, 524 - 512);//512-524
	int m_Unknown524;//524-528
	int m_Unknown528;//528-532
	int m_Unknown532;//532-536
	_pad(__pad11, 540 - 536);//536-540
	bool m_Unknown540;//540-544
	_pad(__pad12, 656 - 544);//544-656
	int m_Unknown656;//656-660
	_pad(__pad13, 1488 - 660);//660-1488
	bool m_bZit;//1488-1492
} cellphone3Dstructure;

typedef struct
{
	uint m_Contact;//0-4
} PhoneCall;

typedef struct
{
	uint m_StrandID;//0-4
	int m_Unknown4;//4-8
	int m_Unknown8;//8-12
	int m_Unknown12;//12-16
	int m_Unknown16;//16-20
	char m_szName[16];//20-36
	char m_szScript[32];//36-68
	_pad(__pad0, 100 - 68);//68-100
	int m_Unknown100;//100-104
	int m_Unknown104;//104-108
	int m_Unknown108;//108-112
} Trigger;

typedef struct
{
	int m_Count;//0-4
	int m_Unknown4[3];//4-16
	_pad(__pad0, 40 - 16);//16-40
} Email;

#ifndef SUBTARGET
global(91) cellphone3Dstructure g_Cellphone;
#elif SUBTARGET==SUBTARGET_TLAD
global(94) cellphone3Dstructure g_Cellphone;
#elif SUBTARGET==SUBTARGET_TBOGT
global(942) cellphone3Dstructure g_Cellphone;
#endif
global(555) uint g_Unknown555;
global(8392) uint g_SpeechPriority;
global(8394) uint g_SpeechControlStatus;
global(8499) PhoneLabels g_PhoneLabels; // 25
global(15946) CellphoneContact g_PhoneContacts[1];
global(64542) PhoneCall g_PhoneCall;

global(32639) uint g_TriggerCount;
global(26758) Trigger g_Triggers[210];

global(968) uint g_EmailCount;
global(969) Email g_Emails[40];

extern void GiveContact(int Contact, bool bSilent);
extern bool IsPlayerCallingContact(int Contact, bool b);
extern bool IsPhoneReadyToAnswerContact(int Contact);
extern void DebugPrint(const char* psz);
extern void DebugPrintParam(const char* psz, const char* pszParam);
extern void CopyContactName(int i, char* pszBuffer);
extern void CopyPlayerName(char* pszBuffer);
extern bool SetupAudioPhoneCall(uint Contact, uint Labels1Count, PhoneLabel* rgpLabels1, const char* pszDialog, uint uParam3, uint Labels2Count, PhoneLabel* rgpLabels2, uint Labels3Count, PhoneLabel* rgpLabels3, const char* uParam6, uint uParam7, bool bMissionCall, uint uParam9, uint uParam10, bool bOverrideCellphoneChecks, uint uParam12, uint uParam13);
extern bool SetupSimpleConversation(const char* pszLabels, const char* pszDialog, bool bPhoneCall);
extern bool SetupSimplePhoneCall(uint Contact, const char* pszLabels, const char* pszDialog, int uParam3, int uParam4);
extern bool CanRingCellphone();
extern bool PhoneCheck();
extern int GetLastContactUnknown24();
extern void RestorePhoneScriptValues();

extern void DeleteEmail(uint Index);
extern void InitialLogic();
