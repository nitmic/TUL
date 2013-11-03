#include "FakeFullScreen.h"
#include <assert.h>

#ifdef WIN32
namespace TUL{
	namespace {
		int defaultDisplayWidth = 0;
		int defaultDisplayHeight = 0;
		int defaultWindowLeft;
		int defaultWindowTop;
		int defaultWindowRight;
		int defaultWindowBottom;
		bool isFullscreen = false;
	};

	void restoreFakeFullScreen(HWND hWnd){
		if(!isFullscreen) return;
		

		DEVMODE    devMode;
		devMode.dmSize       = sizeof(DEVMODE);
		devMode.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT;
		devMode.dmPelsWidth  = defaultDisplayWidth;
		devMode.dmPelsHeight = defaultDisplayHeight;
		assert(ChangeDisplaySettings(&devMode, CDS_FULLSCREEN)==DISP_CHANGE_SUCCESSFUL);

		assert(MoveWindow(
			hWnd, 
			0,
			0,
			800,
			600, FALSE
		)==true);

		
		{
			isFullscreen = false;
			defaultDisplayHeight = 0;
			defaultDisplayHeight = 0;
		}
	}

	void fakeFullScreen(HWND hWnd, int width, int height){
		if(isFullscreen) return;
	
		{
			isFullscreen = true;
			
			if(defaultDisplayHeight==0){
				defaultDisplayWidth = GetSystemMetrics(SM_CXSCREEN);
				defaultDisplayHeight = GetSystemMetrics(SM_CYSCREEN);
				tagRECT rect;
				GetWindowRect(hWnd, &rect);
				defaultWindowLeft = rect.left;
				defaultWindowTop = rect.top;
				defaultWindowRight = rect.right;
				defaultWindowBottom = rect.bottom;
			}
		}

		SetWindowLong(hWnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);
	
		DEVMODE    devMode;
		devMode.dmSize       = sizeof(DEVMODE);
		devMode.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT;
		devMode.dmPelsWidth  = width;
		devMode.dmPelsHeight = height;
		assert(ChangeDisplaySettings(&devMode, CDS_FULLSCREEN)==DISP_CHANGE_SUCCESSFUL);

		//int x = GetSystemMetrics(SM_XVIRTUALSCREEN);
		//int y = GetSystemMetrics(SM_YVIRTUALSCREEN);
		//int w = GetSystemMetrics(SM_CXVIRTUALSCREEN);
		//int h = GetSystemMetrics(SM_CYVIRTUALSCREEN);
		assert(MoveWindow(
			hWnd, 
			0,
			0,
			width,
			height, FALSE
		)==true);
	}
};
#endif