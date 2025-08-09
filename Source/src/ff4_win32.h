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
	void FUN_0042a140();

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
	static bool DAT_005f9a07;

	//DAT_005f9a15
	static bool DAT_005f9a15;
	//DAT_005f9a74
	static SDL_Texture* DAT_005f9a74;
	//DAT_005f9a16
	static bool DAT_005f9a16;
	//DAT_005f9a70
	static SDL_Texture* DAT_005f9a70;

}