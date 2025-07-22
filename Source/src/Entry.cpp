#include <SDL.h>
#include <Windows.h>
#include <exception>

#include "Main.h"

//FUN_0042c8d0
int SDL_main(int argc, char* argv[]) {
	_set_se_translator(Main::SETranslator);
	return Main::FF4_main(argc, argv);
}