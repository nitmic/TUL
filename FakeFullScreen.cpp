#include "FakeFullScreen.h"
#include <assert.h>

#ifdef WIN32
namespace TUL{
	namespace {
		int defaultDisplayWidth = 0;
		int defaultDisplayHeight = 0;
		bool isFullscreen = false;
		LONG windowLong;
	};

	void restoreFakeFullScreen(HWND hWnd){
		if(!isFullscreen) return;

		// 解像度を元に戻す
		DEVMODE    devMode;
		devMode.dmSize       = sizeof(DEVMODE);
		devMode.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT;
		devMode.dmPelsWidth  = defaultDisplayWidth;
		devMode.dmPelsHeight = defaultDisplayHeight;
		assert(ChangeDisplaySettings(&devMode, CDS_FULLSCREEN)==DISP_CHANGE_SUCCESSFUL);
		
		// ウィンドウが最小化されていたら元に戻す（いらないかも）
		while(IsIconic(hWnd)) ShowWindow(hWnd, SW_RESTORE);
		// ウィンドウのスタイルを戻す
		SetWindowLong(hWnd, GWL_STYLE, windowLong);
		// ウィンドウを移動。最前面解除
		assert(SetWindowPos( hWnd, HWND_TOP, 0, 0, defaultDisplayWidth, defaultDisplayHeight, SWP_FRAMECHANGED));

		{
			isFullscreen = false;
		}
	}

	void fakeFullScreen(HWND hWnd, int width, int height){
		if(isFullscreen) return;
		
		// ウィンドウが最小化されていたら元に戻す
		while(IsIconic(hWnd)) ShowWindow(hWnd, SW_RESTORE);
		{
			isFullscreen = true;
			
			if(defaultDisplayHeight==0){
				defaultDisplayWidth = GetSystemMetrics(SM_CXSCREEN);
				defaultDisplayHeight = GetSystemMetrics(SM_CYSCREEN);
				windowLong = GetWindowLong(hWnd, GWL_STYLE);
				// ウィンドウのサイズ・スタイルの情報を保存
			}
		}
		//枠無しに
		SetWindowLong(hWnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);
		// ウィンドウを移動させ最前面にしておく
		assert(SetWindowPos( hWnd, HWND_TOPMOST, 0, 0, width, height, (SWP_SHOWWINDOW|SWP_FRAMECHANGED)));
		
		//プライマリモニタの解像度を変更
		DEVMODE    devMode;
		devMode.dmSize       = sizeof(DEVMODE);
		devMode.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT;
		devMode.dmPelsWidth  = width;
		devMode.dmPelsHeight = height;
		assert(ChangeDisplaySettings(&devMode, CDS_FULLSCREEN)==DISP_CHANGE_SUCCESSFUL);
	}
};
#endif