#include "ff4_win32.h"

#include "Steam.h"

#include "Language.cpp"
#include "Renderer.cpp"

static const char g_period = '.';
static const char g_backslash = '\\';

//this is just to prevent inlining. Will not be needed eventually.
void ignore_this() {
	std::string str = std::string("appdata_path").append("appdata_path");
	std::string str2 = std::string("appdata2_path").append("1appdata_path");
	size_t a = str.rfind(".");
	size_t a2 = str.rfind(".");
	size_t a3 = str.rfind(g_period);
	size_t a4 = str.rfind(g_backslash);

	std::ifstream file;
	file.open("hi");
	file.close();

	std::ifstream filea;
	filea.open("hi");
	filea.close();

	Main::LoadFF4ini();
	Renderer::FUN_00441cc0(nullptr, nullptr, nullptr, nullptr);
	Renderer::FUN_00441ca0(0, 0);
	Renderer::FUN_00441cc0(nullptr, nullptr, nullptr, nullptr);
	Renderer::FUN_00441ca0(0, 0);
	Main::CalculateViewportDimensions();
	Main::CalculateViewportDimensions();
	Main::RenderPauseScreen();
	Main::RenderPauseScreen();
	SDL_FreeSurface(Main::FF4_TTF_RenderText(Main::Menu_Resume.c_str(), 40, 30, {}));
	SDL_FreeSurface(Main::FF4_TTF_RenderText(Main::Menu_Quit.c_str(), 20, 130, {}));
}

//FUN_00423560
void EnsureDirectory(LPCSTR param_1) {
	SHCreateDirectoryExA(NULL, param_1, NULL);
}

void inline Main::InitSDLJoystick() {
	SDL_GameControllerAddMappingsFromRW(SDL_RWFromFile("files/gamecontroller.db", "rb"), 1);
	printf("%i joysticks were found.\n\n", SDL_NumJoysticks());
	int num_joysticks = SDL_NumJoysticks();
	if (num_joysticks > 0) {
		GameController = SDL_GameControllerOpen(0);
		if (GameController == nullptr) {
			Joystick = SDL_JoystickOpen(0);
		}
		else {
			Joystick = SDL_GameControllerGetJoystick(GameController);
			HasGameControllerEvents = true;
			SDL_GameControllerEventState(1);
		}
		HasJoystickEvents = true;
		SDL_JoystickEventState(1);
		JoystickNumAxes = SDL_JoystickNumAxes(Joystick);
		if (JoystickNumAxes > 0) {
			DAT_005f99f4 = malloc(JoystickNumAxes << 2);
			memset(DAT_005f99f4, 0, JoystickNumAxes << 2);
			return;
		}
	}
	DAT_005f99f4 = nullptr;
}

//FUN_00427b50
int Main::FF4_main(int argc, char* argv[]) {
	try {
		int appId = 312750;
		if (Steam::Get()->Initialize(appId)) {
			std::string* appdata_path_ptr;
			appdata_path_ptr = GetAppDataPath(nullptr);
			if (appdata_path_ptr != &g_savedata_path) {
				memcpy(&g_savedata_path, appdata_path_ptr, sizeof(std::string));
				appdata_path_ptr = nullptr;
			}

			std::ostringstream id;
			id << Steam::Get()->steamID;
			g_savedata_path += id.str();

			EnsureDirectory(g_savedata_path.c_str());

			g_savedata_path = g_savedata_path + g_backslash + "SAVE.BIN";

			LoadFF4ini();

			SDL_Init(SDL_INIT_EVERYTHING);
			InitSDLJoystick();
			//Maybe this is a class contructor?
			//_DAT_005f9a00 = 0;
			//_DAT_005f99f8 = 0;
			//DAT_005f9a04 = 0;
			//_DAT_005f9a08 = 0;
			//_DAT_005f9a10 = 0;
			//DAT_005f9a14 = 0;
			//_DAT_005f9a18 = 0;
			//_DAT_005f9a20 = 0;
			//DAT_005f9a24 = 0;
			if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
				printf("IMG_Init: Failed to init required png support!\n");
				printf("IMG_Init: %s\n", SDL_GetError());
			}
			if (TTF_Init() == -1) {
				printf("TTF_Init: Failed to init required TTF support!\n");
				printf("TTF_Init: %s\n", SDL_GetError());
			}
			SDL_DisableScreenSaver();
			if (Window != nullptr) {
				SDL_GL_DeleteContext(ActiveContext);
				SDL_GL_DeleteContext(BackgroundContext);
				if (Renderer != nullptr) {
					SDL_DestroyRenderer(Renderer);
				}
				SDL_DestroyWindow(Window);
				Window = nullptr;
			}
			if (!Windowed) {
				SDL_GetCurrentDisplayMode(0, &DisplayMode);
				Window = SDL_CreateWindow("Final Fantasy IV", 0, 0, ScreenWidth, ScreenHeight, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_FULLSCREEN_DESKTOP);
			}
			else {
				Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_FOCUS;
				if (Borderless)
					flags = SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_INPUT_FOCUS;
				SDL_CreateWindow("Final Fantasy IV", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CurrentWindowWidth, CurrentWindowHeight, flags);
			}
			SDL_SetHint("SDL_RENDER_DRIVER", "opengl");
			Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
			ActiveContext = SDL_GL_GetCurrentContext();
			BackgroundContext = SDL_GL_CreateContext(Window);
			SDL_GL_MakeCurrent(Window, ActiveContext);
			SDL_GL_SetSwapInterval(1);
			if (!Windowed) {
				CurrentWindowWidth = ScreenWidth;
				CurrentWindowHeight = ScreenHeight;
			}
			SDL_Surface* icon = IMG_Load("icon.png");
			SDL_SetWindowIcon(Window, icon);
			SDL_FreeSurface(icon);
			Renderer::FUN_00441cc0(Window, Renderer, &ActiveContext, &BackgroundContext);
			Renderer::FUN_00441ca0(CurrentWindowWidth, CurrentWindowHeight);
			Main::CalculateViewportDimensions();
			SDL_GL_MakeCurrent(Window, BackgroundContext);
			glViewport(ViewportX, ViewportY, ViewportWidth, ViewportHeight);
			SDL_GL_MakeCurrent(Window, ActiveContext);
			if (IsPausePressed) {
				RenderPauseScreen();
			}
			SDL_ShowCursor(1);

		}
	}
	//FUN_00426bb0
	catch(int err) {
		printf("test");
	}


	ignore_this();
	ignore_this();
	return -1;
}

//FUN_00426d00
void Main::SETranslator(unsigned int code, EXCEPTION_POINTERS* info) {}

//FUN_00423580
std::string* __stdcall Main::GetAppDataPath(std::string* out) {
	char exe_path[MAX_PATH + 1];
	GetModuleFileNameA(NULL, exe_path, MAX_PATH + 1);
	const char* exe_name = strrchr(exe_path, '\\');
	if (exe_name) {
		char appdata_path[MAX_PATH];
		HRESULT hr = SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, appdata_path);
		if (SUCCEEDED(hr)) {
			std::string path = appdata_path;
			path += exe_name;
			path = path.substr(0, path.rfind(g_period));
			path.append(g_backslash, 1);

			hr = SHCreateDirectoryExA(NULL, path.c_str(), NULL);
			if (SUCCEEDED(hr)) {
				memcpy(out, &path, sizeof(std::string));
				return out;
			}
		}
	}
	exe_name = exe_path;
	std::string path = exe_name;
	path = path.substr(0, path.rfind(g_backslash) + 1);
	memcpy(out, &path, sizeof(std::string));
	return out;
}

//FUN_0042b080
void Main::LoadFF4ini() {
	std::ifstream file;

	std::string filepath;
	GetAppDataPath(&filepath);
	filepath += "FF4.ini";

	printf(filepath.c_str());

	file.open(filepath, std::ios_base::in, 64);

	std::string line;
	char* value;
	if (file.is_open()) {
		while (line != "[Video]")
			std::getline(file, line);

		std::getline(file, line);
		value = strtok(&line[0], " =");
		value = strtok(nullptr, " =");
		CurrentWindowWidth = atoi(value);
		WindowWidth2 = CurrentWindowWidth;

		std::getline(file, line);
		value = strtok(&line[0], " =");
		value = strtok(nullptr, " =");
		CurrentWindowHeight = atoi(value);
		WindowHeight2 = CurrentWindowHeight;

		std::getline(file, line);
		value = strtok(&line[0], " =");
		value = strtok(nullptr, " =");
		Windowed = atoi(value) != 1;
		Borderless = atoi(value) != 2;

		std::getline(file, line);
		value = strtok(&line[0], " =");
		value = strtok(nullptr, " =");
		PauseInBG = atoi(value) > 0;

		while (line != "[Keyboard]")
			std::getline(file, line);

		for (int* keybind : Keyboard_Keybinds) {
			std::getline(file, line);
			value = strtok(&line[0], " =");
			value = strtok(nullptr, " =");
			if (value != nullptr) {
				*keybind = atoi(value);
			}
		}

		value = strtok(&line[0], " =");
		value = strtok(nullptr, " =");
		Keyboard_Chat = atoi(value);

		while (line != "[Joystick]")
			std::getline(file, line);

		for (int* keybind : Joystick_Keybinds) {
			std::getline(file, line);
			value = strtok(&line[0], " =");
			value = strtok(nullptr, " =");
			if (value != nullptr) {
				*keybind = atoi(value);
			}
		}

		value = strtok(&line[0], " =");
		value = strtok(nullptr, " =");
		Joystick_Chat = atoi(value);

		while (line != "[Language]" && std::getline(file, line));

		int language;
		if (std::getline(file, line))
			language = atoi(&line[0]);
		else
			language = 0;

		Language::SetLanguage(language);

		file.close();

		ParseMenuTxt();
	}
}

//FUN_0042b670
void Main::ParseMenuTxt() {
	std::ifstream file("menu.txt", std::ios_base::in, 64);
	std::string line;
	if (file.is_open()) {
		if (Language::GetLanguage() > 0)
			for (int i = 0; i < Language::GetLanguage(); i++)
				for (int j = 0; j < 7; j++)
					std::getline(file, line);
		std::getline(file, line);
		Menu_Resume = line;
		std::getline(file, line);
		Menu_Quit = line;
		std::getline(file, line);
		Menu_Yes = line;
		std::getline(file, line);
		Menu_No = line;
		std::getline(file, line);
		Menu_SkipScene = line;
		std::getline(file, line);
		Menu_QuitGame = line;
		std::getline(file, line);
		Menu_EnterName = line;
		file.close();
	}
}

//FUN_00429920
void Main::CalculateViewportDimensions()
{
	ViewportWidth = CurrentWindowWidth;
	ViewportHeight = CurrentWindowHeight;
	if (CurrentWindowHeight * 3 < CurrentWindowWidth * 2) {
		int new_width = (CurrentWindowHeight * 21) / 9;
		if (new_width < CurrentWindowWidth) {
			ViewportWidth = new_width;
		}
		RenderWidth = (ViewportWidth * 320) / CurrentWindowHeight;
		RenderHeight = 320;
	}
	else {
		int new_height = (CurrentWindowWidth * 3) / 4;
		if (new_height < CurrentWindowHeight) {
			ViewportHeight = new_height;
		}
		RenderHeight = (ViewportHeight * 480) / CurrentWindowWidth;
		RenderWidth = 480;
	}
	ViewportX = (CurrentWindowWidth - ViewportWidth) / 2;
	ViewportY = (CurrentWindowHeight - ViewportHeight) / 2;
	return;
}

//FUN_0042a140
void Main::RenderPauseScreen() {
	DAT_005f9a15 = false;
	if (DAT_005f9a74 == nullptr && !DAT_005f9a16) {
		SDL_GL_MakeCurrent(Window, BackgroundContext);
		void* pixels = malloc(CurrentWindowHeight * CurrentWindowWidth * 4);
		glReadPixels(0, 0, CurrentWindowWidth, CurrentWindowHeight, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		SDL_GL_MakeCurrent(Window, ActiveContext);
		SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, CurrentWindowWidth, CurrentWindowHeight, 32, CurrentWindowWidth * 4, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
		if (surface == nullptr) {
			fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
			return;
		}
		DAT_005f9a74 = SDL_CreateTextureFromSurface(Renderer, surface);
		if (DAT_005f9a74 == nullptr) {
			fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
			return;
		}
		SDL_FreeSurface(surface);
		free(pixels);
	}
	else {
		SDL_GL_MakeCurrent(Window, ActiveContext);
	}
	if (DAT_005f9a70 != nullptr) {
		SDL_DestroyTexture(DAT_005f9a70);
		DAT_005f9a70 = nullptr;
	}
	SDL_RenderClear(Renderer);
	SDL_Surface* surface = SDL_CreateRGBSurface(0, CurrentWindowWidth, CurrentWindowHeight, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
	SDL_FillRect(surface, 0, SDL_MapRGBA(surface->format, 0, 0, 0, 127));
	Button1Width = 240;
	Button1Height = 72;
	Button2Width = 240;
	Button2Height = 72;
	_DAT_005f9a2c = CurrentWindowWidth / 2 + -0x78;
	iRam005f9a30 = CurrentWindowHeight / 2 + -0x6c;
	iRam005f9a40 = CurrentWindowHeight / 2 + 0x24;
	uRam005f9a34 = 240;
	uRam005f9a38 = 72;
	uRam005f9a44 = 240;
	uRam005f9a48 = 72;
	_DAT_005f9a3c = _DAT_005f9a2c;
	Button1Rect.x = _DAT_005f9a2c;
	Button1Rect.y = iRam005f9a30;
	Button2Rect.x = _DAT_005f9a2c;
	Button2Rect.y = iRam005f9a40;
	SDL_Surface* btn1 = IMG_Load("button_off.png");
	SDL_Surface* btn2 = IMG_Load("button_off.png");
	SDL_Surface* resume_text = FF4_TTF_RenderText(Menu_Resume.c_str(), 40, 30, {});
	SDL_Surface* quit_text = FF4_TTF_RenderText(Menu_Quit.c_str(), 40, 30, {});
	SDL_Rect rect;
	{
		rect.x = (Button1Width - resume_text->w) / 2;
		rect.y = (Button1Height - resume_text->h) / 2;
		rect.w = resume_text->w;
		rect.h = resume_text->h;
		SDL_UpperBlit(resume_text, nullptr, btn1, &rect);
	}
	{
		rect.x = (Button2Width - quit_text->w) / 2;
		rect.y = (Button2Height - quit_text->h) / 2;
		rect.w = quit_text->w;
		rect.h = quit_text->h;
		SDL_UpperBlit(quit_text, nullptr, btn2, &rect);
	}
	SDL_Surface* point = IMG_Load("point.png");
	SDL_UpperBlit(btn1, nullptr, surface, &Button1Rect);
	SDL_UpperBlit(btn2, nullptr, surface, &Button2Rect);
	{
		float x;
		if (HoveredButtonIndex == 0) {
			x = (float)(Button1Rect.x - point->w + Button1Width) / 5.8;
			rect.y = (Button1Height / 2 - point->h / 4) + Button1Rect.y;
		}
		else {
			x = (float)(Button2Rect.x - point->w + Button2Width) / 5.8;
			rect.y = (Button2Height / 2 - point->h / 4) + Button2Rect.y;
		}
		rect.x = x;
		SDL_UpperBlit(point, nullptr, surface, &rect);
	}
	OverlayTexture = SDL_CreateTextureFromSurface(Renderer, surface);
	if (OverlayTexture == nullptr) {
		fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return;
	}
	SDL_FreeSurface(point);
	SDL_FreeSurface(resume_text);
	SDL_FreeSurface(quit_text);
	SDL_FreeSurface(btn1);
	SDL_FreeSurface(btn2);
	SDL_FreeSurface(surface);
	if (DOTEMU_ASSERT_VAR == NULL) {
		surface = IMG_Load("point.png");
		if (surface == nullptr) {
			printf("DOTEMU_ASSERT(tmp != NULL) failed at %s, line: %d\n", "c:\\slave_jenkins\\workspace\\stx_time_steam_content\\src\\ff4_win32.cpp", 1930);
			MessageBoxA(NULL, "The program has encountered an undefined behavior, see the logs for more details", "Assert Failed", MB_ICONERROR);
			exit(1);
		}
		SDL_Surface* new_surface = surface;
		if (surface->format->format != SDL_PIXELFORMAT_ARGB8888) {
			new_surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB8888, 0);
			SDL_FreeSurface(surface);
		}
		SDL_Rect test_rect;
		test_rect.x = 0;
		test_rect.y = 0;
		test_rect.w = new_surface->w;
		test_rect.h = new_surface->h;
		DOTEMU_ASSERT_VAR = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_ARGB8888, 0, new_surface->w, new_surface->h);
		if (DOTEMU_ASSERT_VAR == NULL) {
			printf("DOTEMU_ASSERT(testImg != NULL) failed at %s, line: %d\n", "c:\\slave_jenkins\\workspace\\stx_time_steam_content\\src\\ff4_win32.cpp", 1948);
			MessageBoxA(NULL, "The program has encountered an undefined behavior, see the logs for more details", "Assert Failed", MB_ICONERROR);
			exit(1);
		}
		SDL_UpdateTexture((SDL_Texture*)DOTEMU_ASSERT_VAR, &test_rect, new_surface->pixels, new_surface->pitch);
		SDL_FreeSurface(new_surface);
		if (DOTEMU_ASSERT_VAR == NULL) {
			printf("DOTEMU_ASSERT(testImg != NULL) failed at %s, line: %d\n", "c:\\slave_jenkins\\workspace\\stx_time_steam_content\\src\\ff4_win32.cpp", 1952);
			MessageBoxA(NULL, "The program has encountered an undefined behavior, see the logs for more details", "Assert Failed", MB_ICONERROR);
			exit(1);
		}
	}
}

//FUN_0042ac40
SDL_Surface* Main::FF4_TTF_RenderText(const char* text, int draw_area_size, int font_size, int* actual_size) {
	LOGFONTA lf;
	GetObjectA(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONTA), &lf);
	lf.lfHeight = font_size * -16;
	if (Language::GetLanguage() == 6) {
		strcpy_s(lf.lfFaceName, LF_FACESIZE, "arial");
	}
	HFONT font = CreateFontIndirectA(&lf);

	HDC hdc = CreateCompatibleDC(nullptr);
	SelectObject(hdc, font);
	SetTextColor(hdc, 0xffffff);
	SetBkColor(hdc, 0);
	WCHAR wide_text[256];
	MultiByteToWideChar(CP_UTF8, 0, text, -1, wide_text, 256);

	SIZE psizl;
	int wide_text_len = wcslen(wide_text);
	GetTextExtentPoint32W(hdc, wide_text, wide_text_len, &psizl);
	long render_width = (int)(psizl.cx + (psizl.cx >> 0x1f & 0xfU)) >> 4;
	if (actual_size != nullptr) {
		*actual_size = render_width;
		render_width = draw_area_size;
	}
	long bitmap_width = render_width * 16;
	HBITMAP bitmap = CreateCompatibleBitmap(hdc, bitmap_width, draw_area_size * 16);
	SelectObject(hdc, bitmap);

	BITMAPINFO bi;
	memset(&bi, 0, sizeof(bi));
	bi.bmiHeader.biHeight = draw_area_size * -16;
	bi.bmiHeader.biXPelsPerMeter = 0;
	bi.bmiHeader.biYPelsPerMeter = 0;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;
	bi.bmiHeader.biSize = 40;
	unsigned int pixels_len = render_width * draw_area_size * 16 * 16 * 4;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biSizeImage = pixels_len;
	bi.bmiHeader.biWidth = bitmap_width;

	void* pixels = malloc(pixels_len);
	RECT rect;
	rect.right = bi.bmiHeader.biWidth;
	rect.bottom = -bi.bmiHeader.biHeight;
	rect.left = 0;
	rect.top = 0;

	HBRUSH hbr = (HBRUSH)GetStockObject(BLACK_BRUSH);
	FillRect(hdc, &rect, hbr);
	DrawTextW(hdc, wide_text, wide_text_len, &rect, DT_NOCLIP | DT_SINGLELINE | DT_VCENTER);
	GetDIBits(hdc, bitmap, 0, -bi.bmiHeader.biHeight, pixels, &bi, DIB_RGB_COLORS);

	SDL_Surface* surface = SDL_CreateRGBSurface(0, render_width, draw_area_size, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
	SDL_LockSurface(surface);

	uint8_t* srcPixels = static_cast<uint8_t*>(pixels);
	int srcPitch = bitmap_width * 4;
	uint8_t* dstPixels = static_cast<uint8_t*>(surface->pixels);
	int dstPitch = surface->pitch;

	for (int blockY = 0; blockY < draw_area_size - 1; ++blockY) {
		uint8_t* dstRow = dstPixels + blockY * dstPitch;
		for (int blockX = 0; blockX < render_width; ++blockX) {

			int sumR = 0, sumG = 0, sumB = 0, sumA = 0;
			for (int y = 0; y < 16; ++y) {
				const uint8_t* srcRow = srcPixels + (blockY * 16 + y) * srcPitch + blockX * 16 * 4;
				for (int x = 0; x < 16; ++x) {
					uint8_t b = srcRow[x * 4 + 0];
					uint8_t g = srcRow[x * 4 + 1];
					uint8_t r = srcRow[x * 4 + 2];
					uint8_t a = srcRow[x * 4 + 3];
					sumR += r;
					sumG += g;
					sumB += b;
					sumA += a;
				}
			}

			int totalPixels = 16 * 16;
			int avg = (sumR + sumG + sumB + sumA) / (4 * totalPixels);

			uint8_t* dstPixel = dstRow + blockX * 4;
			dstPixel[0] = 0xFF;
			dstPixel[1] = 0xFF;
			dstPixel[2] = 0xFF;
			dstPixel[3] = static_cast<uint8_t>(avg);
		}
	}

	uint8_t* lastRow = dstPixels + (draw_area_size - 1) * dstPitch;
	for (int blockX = 0; blockX < render_width; ++blockX) {
		uint8_t* dstPixel = lastRow + blockX * 4;
		dstPixel[0] = 0xFF;
		dstPixel[1] = 0xFF;
		dstPixel[2] = 0xFF;
		dstPixel[3] = 0;
	}

	SDL_UnlockSurface(surface);
	DeleteDC(hdc);
	DeleteObject(bitmap);
	DeleteObject(font);
	free(pixels);

	return surface;
}