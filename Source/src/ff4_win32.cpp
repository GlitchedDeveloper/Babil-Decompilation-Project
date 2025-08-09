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
	Main::FUN_0042a140();
	Main::FUN_0042a140();
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
			if (DAT_005f9a07) {
				FUN_0042a140();
			}
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
void Main::FUN_0042a140() {
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
	//DAT_005f9a80 = 0xf0;
	//DAT_005f9a84 = 0x48;
	//DAT_005f9a90 = 0xf0;
	//DAT_005f9a94 = 0x48;
	//_DAT_005f9a2c = CurrentWindowWidth / 2 + -0x78;
	//iRam005f9a30 = CurrentWindowHeight / 2 + -0x6c;
	//iRam005f9a40 = CurrentWindowHeight / 2 + 0x24;
	//uRam005f9a34 = 0xf0;
	//uRam005f9a38 = 0x48;
	//uRam005f9a44 = 0xf0;
	//uRam005f9a48 = 0x48;
	//_DAT_005f9a3c = _DAT_005f9a2c;
	//DAT_005f9a78 = _DAT_005f9a2c;
	//_DAT_005f9a7c = iRam005f9a30;
	//DAT_005f9a88 = _DAT_005f9a2c;
	//_DAT_005f9a8c = iRam005f9a40;
	SDL_Surface* btn1 = IMG_Load("button_off.png");
	SDL_Surface* btn2 = IMG_Load("button_off.png");
	void* local_18 = 0;
	//...
}