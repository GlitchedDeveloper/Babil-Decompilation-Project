#pragma once

#include <SDL.h>

namespace Renderer {
	//DAT_0060bfc4
	static SDL_Window* Window;
	//DAT_0060bfc8
	static SDL_Renderer* Renderer;
	//DAT_0060bfcc
	static SDL_GLContext* CurrentContext;
	//DAT_0060bfd0
	static SDL_GLContext* NextContext;

	void FUN_00441cc0(SDL_Window* window, SDL_Renderer* renderer, SDL_GLContext* current_context, SDL_GLContext* next_context) {
		Window = window;
		Renderer = renderer;
		CurrentContext = current_context;
		NextContext = next_context;
	}

	//DAT_0060bfbc
	static int WindowWidth;
	//DAT_0060bfc0
	static int WindowHeight;

	void FUN_00441ca0(int width, int height) {
		WindowWidth = width;
		WindowHeight = height;
	}
}