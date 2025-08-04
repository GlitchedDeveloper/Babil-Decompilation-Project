#pragma once

#include <windows.h>
#include <winnt.h>

#include <shlobj.h>
#include <string>
#include <sstream>

#include <iostream>

namespace Main {
	int FF4_main(int argc, char* argv[]);
	void SETranslator(unsigned int code, EXCEPTION_POINTERS* info);
	std::string* GetAppDataPath(std::string* path);

	static std::string g_appdata_path;
}