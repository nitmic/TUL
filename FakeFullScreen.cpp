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

		// �𑜓x�����ɖ߂�
		DEVMODE    devMode;
		devMode.dmSize       = sizeof(DEVMODE);
		devMode.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT;
		devMode.dmPelsWidth  = defaultDisplayWidth;
		devMode.dmPelsHeight = defaultDisplayHeight;
		assert(ChangeDisplaySettings(&devMode, CDS_FULLSCREEN)==DISP_CHANGE_SUCCESSFUL);
		
		// �E�B���h�E���ŏ�������Ă����猳�ɖ߂��i����Ȃ������j
		while(IsIconic(hWnd)) ShowWindow(hWnd, SW_RESTORE);
		// �E�B���h�E�̃X�^�C����߂�
		SetWindowLong(hWnd, GWL_STYLE, windowLong);
		// �E�B���h�E���ړ��B�őO�ʉ���
		assert(SetWindowPos( hWnd, HWND_TOP, 0, 0, defaultDisplayWidth, defaultDisplayHeight, SWP_FRAMECHANGED));

		{
			isFullscreen = false;
		}
	}

	void fakeFullScreen(HWND hWnd, int width, int height){
		if(isFullscreen) return;
		
		// �E�B���h�E���ŏ�������Ă����猳�ɖ߂�
		while(IsIconic(hWnd)) ShowWindow(hWnd, SW_RESTORE);
		{
			isFullscreen = true;
			
			if(defaultDisplayHeight==0){
				defaultDisplayWidth = GetSystemMetrics(SM_CXSCREEN);
				defaultDisplayHeight = GetSystemMetrics(SM_CYSCREEN);
				windowLong = GetWindowLong(hWnd, GWL_STYLE);
				// �E�B���h�E�̃T�C�Y�E�X�^�C���̏���ۑ�
			}
		}
		//�g������
		SetWindowLong(hWnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);
		// �E�B���h�E���ړ������őO�ʂɂ��Ă���
		assert(SetWindowPos( hWnd, HWND_TOPMOST, 0, 0, width, height, (SWP_SHOWWINDOW|SWP_FRAMECHANGED)));
		
		//�v���C�}�����j�^�̉𑜓x��ύX
		DEVMODE    devMode;
		devMode.dmSize       = sizeof(DEVMODE);
		devMode.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT;
		devMode.dmPelsWidth  = width;
		devMode.dmPelsHeight = height;
		assert(ChangeDisplaySettings(&devMode, CDS_FULLSCREEN)==DISP_CHANGE_SUCCESSFUL);
	}
};
#endif