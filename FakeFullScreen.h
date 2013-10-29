#pragma once

#ifdef WIN32
#include <Windows.h>
namespace TUL{
	void restoreFakeFullScreen(HWND hWnd);

	void fakeFullScreen(HWND hWnd, int width, int height);
};
#endif