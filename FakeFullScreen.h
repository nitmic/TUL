#pragma once

#ifdef WIN32
#include <Windows.h>

void fakeFullScreen(HWND hWnd, int width, int height){
	SetWindowLong(hWnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);
	
	//int x = GetSystemMetrics(SM_XVIRTUALSCREEN);
	//int y = GetSystemMetrics(SM_YVIRTUALSCREEN);
	//int w = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	//int h = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	MoveWindow(
		hWnd, 
		0,
		0,
		800,
		640, TRUE
	);
	
	DEVMODE    devMode;
	devMode.dmSize       = sizeof(DEVMODE);
	devMode.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT;
	devMode.dmPelsWidth  = width;
	devMode.dmPelsHeight = height;
	ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
}
#endif