#include "Steam.h"

#include <Windows.h>

//FUN_00441f90
static void SteamWarningMessageHook(int severity, const char* message) {
	OutputDebugStringA(message);
}

//FUN_00441ea0
bool __thiscall Steam::Initialize(uint32 AppID) {
	bool res;
	res = SteamAPI_RestartAppIfNecessary(AppID);
	if (!res) {
		res = SteamAPI_Init();
		if (res) {
			SteamClient()->SetWarningMessageHook(&SteamWarningMessageHook);
			SteamUtils()->SetOverlayNotificationPosition(k_EPositionTopRight);
			storage = SteamRemoteStorage();
			hasStorage = true;
			name = SteamFriends()->GetPersonaName();
			steamID = SteamUser()->GetSteamID().ConvertToUint64();
			return steamID;
		}
	}
	return res;
}