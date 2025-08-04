#pragma once

#include <steam/steam_api.h>
#include "typedef.h"

class Steam {
private:
	static CCallbackManual<Steam, UserAchievementStored_t, false> m_UserAchievementStoredCallback;
	void OnUserAchievementStored(UserAchievementStored_t* pCallback);
public:
	char unknown[0x14];
	ISteamRemoteStorage* storage; //0x14
	char unknown2[0x8];
	bool hasStorage; //0x20
	char unknown3[0x3];
	const char* name; //0x24
	uint64 steamID; //0x28 0x2c
	//FUN_00441ea0
	bool __thiscall Initialize(uint32 AppID);
	void Test();
	void __fastcall RegisterAchievementCallback(CCallbackManual<Steam, UserAchievementStored_t, false>* pCallback);
	//void OnUserAchievementStored(UserAchievementStored_t* pCallback);
};