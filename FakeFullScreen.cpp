#include "FakeFullScreen.h"

#ifdef WIN32

int defaultDisplayWidth;
int defaultDisplayHeight;
int defaultWindowLeft;
int defaultWindowTop;
int defaultWindowRight;
int defaultWindowBottom;
bool isFullscreen = false;

void restoreFakeFullScreen(HWND hWnd){
	if(!isFullscreen) return;
	isFullscreen = false;
	
	SetWindowLong(hWnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);
	
	DEVMODE    devMode;
	devMode.dmSize       = sizeof(DEVMODE);
	devMode.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT;
	devMode.dmPelsWidth  = defaultDisplayWidth;
	devMode.dmPelsHeight = defaultDisplayHeight;
	ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);

	MoveWindow(
		hWnd, 
		defaultWindowLeft,
		defaultWindowTop,
		defaultWindowRight,
		defaultWindowBottom, TRUE
	);
}

void fakeFullScreen(HWND hWnd, int width, int height){
	if(isFullscreen) return;
	{
		isFullscreen = true;
		defaultDisplayWidth = GetSystemMetrics(SM_CXSCREEN);
		defaultDisplayHeight = GetSystemMetrics(SM_CYSCREEN);
		tagRECT rect;
		GetWindowRect(hWnd, &rect);
		defaultWindowLeft = rect.left;
		defaultWindowTop = rect.top;
		defaultWindowRight = rect.right;
		defaultWindowBottom = rect.bottom;
	}
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