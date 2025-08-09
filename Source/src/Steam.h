#pragma once

#include <steam/steam_api.h>
#include "typedef.h"

class Steam {
private:
	CCallback<Steam, UserAchievementStored_t, false> m_UserAchievementStoredCallback;
public:
	ISteamRemoteStorage* storage; //0x14
	char unknown2[0x8];
	bool hasStorage; //0x20
	char unknown3[0x3];
	const char* name; //0x24
	uint64 steamID; //0x28 0x2c

	void OnUserAchievementStored(UserAchievementStored_t* pCallback);
	Steam() : m_UserAchievementStoredCallback(this, &Steam::OnUserAchievementStored) {};

	//FUN_00441ea0
	bool __thiscall Initialize(uint32 AppID);
	
	static Steam* Get();
};