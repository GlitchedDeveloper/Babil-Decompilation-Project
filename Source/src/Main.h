#pragma once

#include <windows.h>
#include <winnt.h>

#include <shlobj.h>
#include <string>

namespace Main {
	int FF4_main(int argc, char* argv[]);
	void SETranslator(unsigned int code, EXCEPTION_POINTERS* info);
	void GetSavePath(LPCSTR* savepath);
}