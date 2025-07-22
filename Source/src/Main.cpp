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
	str = str.substr(str.rfind("a"));
	str = str.substr(str.rfind('.'));
	str = str.substr(str.rfind('.'));
}

//FUN_00427b50
int Main::FF4_main(int argc, char* argv[]) {
	try {
		Steam steam;
		if (steam.Initialize(312750)) {
			LPCSTR* savepath;
			GetSavePath(savepath);
			ignore_this();
			ignore_this();
		}
	}
	catch(int err) {}
	return -1;
}

//FUN_00426d00
void Main::SETranslator(unsigned int code, EXCEPTION_POINTERS* info) {}

//FUN_00423580
void Main::GetSavePath(LPCSTR* savepath) {
	try {
		char exe_path[MAX_PATH];
		GetModuleFileNameA(NULL, exe_path, MAX_PATH);
		char* exe_name = strrchr(exe_path, '\\');
		if (exe_name != NULL) {
			char appdata_path[MAX_PATH];
			HRESULT hr = SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, appdata_path);
			if (SUCCEEDED(hr)) {
				std::string str = appdata_path;
				str += exe_name;
				str = str.substr(str.rfind(g_period));
				str = str.append(g_backslash, 1);
				hr = SHCreateDirectoryExA(NULL, str.c_str(), NULL);
				if (SUCCEEDED(hr)) {
					*savepath = str.c_str();
					return;
				}
			}
		}
		std::string str(exe_path);
		str = str.substr(str.rfind(g_backslash));
		*savepath = str.c_str();
		return;
	}
	catch (int errorCode) {}
}