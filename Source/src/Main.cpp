#include "Main.h"

#include "Steam.h"

static const char* g_period = ".";
static const char* g_backslash = "\\";

void ignore_this() {
	std::string str = std::string("appdata_path").append("appdata_path");
	std::string str2 = std::string("appdata2_path").append("1appdata_path");
	size_t a = str.rfind(".");
	size_t a2 = str.rfind(".");
	size_t a3 = str.rfind(g_period);
	size_t a4 = str.rfind(g_backslash);
}

//FUN_00427b50
int Main::FF4_main(int argc, char* argv[]) {
	try {
		int appId = 312750;
		Steam steam;
		if (steam.Initialize(appId)) {
			std::string* appdata_path = GetAppDataPath(&std::string());
			if (appdata_path != &g_appdata_path) {
				memcpy(&g_appdata_path, appdata_path, sizeof(std::string));
				appdata_path = nullptr;
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
std::string* Main::GetAppDataPath(std::string* out) {
	try {
		char exe_path[MAX_PATH];
		GetModuleFileNameA(NULL, exe_path, MAX_PATH);
		char* exe_name = strrchr(exe_path, '\\');
		if (exe_name != NULL) {
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
	catch (int a) {}
}