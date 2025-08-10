#pragma once

#include <windows.h>
#include <winnt.h>

#include <shlobj.h>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <gl/GL.h>

//#include <iostream>

namespace Main {
	//FUN_00427b50
	int FF4_main(int argc, char* argv[]);
	//FUN_00426d00
	void SETranslator(unsigned int code, EXCEPTION_POINTERS* info);
	//FUN_00423580
	std::string* __stdcall GetAppDataPath(std::string* path);
	//FUN_0042b080
	void LoadFF4ini();
	//FUN_0042b670
	void ParseMenuTxt();
	//FUN_00429920
	void CalculateViewportDimensions();
	//FUN_0042a140
	void RenderPauseScreen();
	//FUN_0042ac40
	SDL_Surface* FF4_TTF_RenderText(const char* text, int x, int y, int* size);

	void inline InitSDLJoystick();

	static std::string g_savedata_path;

	//DAT_005df410
	static int CurrentWindowWidth;
	//DAT_005df414
	static int CurrentWindowHeight;

	//DAT_005df418
	static int WindowWidth2;
	//DAT_005df41c
	static int WindowHeight2;

	//DAT_005df414
	static bool Windowed;
	//DAT_005f9a17
	static bool Borderless;

	//DAT_005df4a8
	static bool PauseInBG;

	//DAT_005df290
	static int* Keyboard_Keybinds[10];
	//DAT_005df4a0
	static int Keyboard_Chat;

	//DAT_005df2f8
	static int* Joystick_Keybinds[10];
	//DAT_005df4a4
	static int Joystick_Chat;

	//DAT_005df368
	static std::string Menu_Resume;
	//DAT_005df380
	static std::string Menu_Quit;
	//DAT_005df398
	static std::string Menu_Yes;
	//DAT_005df3b0
	static std::string Menu_No;
	//DAT_005df3c8
	static std::string Menu_SkipScene;
	//DAT_005df3e0
	static std::string Menu_QuitGame;
	//DAT_005df3f8
	static std::string Menu_EnterName;

	//DAT_005f99e8
	static SDL_GameController* GameController;
	//DAT_005f99ec
	static SDL_Joystick* Joystick;

	//DAT_005e99d2
	static bool HasGameControllerEvents;
	//DAT_005e99d3
	static bool HasJoystickEvents;

	//DAT_005f99f0
	static int JoystickNumAxes;

	static void* DAT_005f99f4; //Maybe float?

	//DAT_005f9a68
	static SDL_Window* Window;
	//DAT_005f9a4c
	static SDL_GLContext ActiveContext;
	//DAT_005f9a50
	static SDL_GLContext BackgroundContext;
	//DAT_005f9a6c
	static SDL_Renderer* Renderer;
	//DAT_005f9a54
	static SDL_DisplayMode DisplayMode;

	//DAT_005f9a58
	static int ScreenWidth;
	//DAT_005f9a5c
	static int ScreenHeight;

	//DAT_005e99dc
	static int ViewportWidth;
	//DAT_005e99e0
	static int ViewportHeight;
	//DAT_005df288
	static int RenderWidth;
	//DAT_005df28c
	static int RenderHeight;
	//DAT_005e99d4
	static int ViewportX;
	//DAT_005e99d8
	static int ViewportY;

	//DAT_005f9a07
	static bool IsPausePressed;

	//DAT_005f9a15
	static bool DAT_005f9a15;
	//DAT_005f9a74
	static SDL_Texture* DAT_005f9a74;
	//DAT_005f9a16
	static bool DAT_005f9a16;
	//DAT_005f9a70
	static SDL_Texture* DAT_005f9a70;

	//DAT_005f9a80
	static DWORD Button1Width;
	//DAT_005f9a84
	static DWORD Button1Height;
	//DAT_005f9a90
	static DWORD Button2Width;
	//DAT_005f9a94
	static DWORD Button2Height;
	//DAT_005f9a2c
	static DWORD _DAT_005f9a2c;
	//DAT_005f9a30
	static long iRam005f9a30;
	//DAT_005f9a40
	static long iRam005f9a40;
	//DAT_005f9a34
	static unsigned long uRam005f9a34;
	//DAT_005f9a38
	static unsigned long uRam005f9a38;
	//DAT_005f9a44
	static unsigned long uRam005f9a44;
	//DAT_005f9a48
	static unsigned long uRam005f9a48;
	//DAT_005f9a3c
	static long _DAT_005f9a3c;
	//DAT_005f9a78
	static SDL_Rect Button1Rect;
	//DAT_005f9a88
	static SDL_Rect Button2Rect;

	//DAT_005df368
	static std::string DAT_005df368;

	//DAT_005e99bc;
	static int HoveredButtonIndex;

	//DAT_005f9a70
	static SDL_Texture* OverlayTexture;

	//DAT_005e99c8
	static void* DOTEMU_ASSERT_VAR;

	//DAT_005f9a22
	static bool DAT_005f9a22;
	//DAT_005f9a23
	static bool DAT_005f9a23;
	//DAT_005f9a26
	static bool DAT_005f9a26;
	//DAT_005e99d0
	static bool DAT_005e99d0;
	//DAT_005e99d1
	static bool DAT_005e99d1;
	//DAT_005f9a27
	static bool DAT_005f9a27;
	//DAT_005f9ab8
	static int DAT_005f9ab8;
}