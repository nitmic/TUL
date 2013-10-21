#pragma once

#ifdef WIN32
#include <Windows.h>

void restoreFakeFullScreen(HWND hWnd);

void fakeFullScreen(HWND hWnd, int width, int height);
#endif