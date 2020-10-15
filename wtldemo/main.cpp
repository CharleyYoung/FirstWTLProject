#include "stdafx.h"
#include <atlwin.h> // ATL ������
#include <atlframe.h> // WTL ����ܴ�����
#include <atlmisc.h> // WTL ʵ�ù����࣬���磺CString
#include <atlcrack.h> // WTL ��ǿ����Ϣ��
#include "resource.h"
#include "MyWindow.h"

CAppModule _Module;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	_Module.Init(NULL, hInstance);

	CMyWindow wndMain;
	MSG msg;

	// Create the main window
	if (NULL == wndMain.CreateEx())
		return 1; // Window creation failed

				  // Show the window
	wndMain.ShowWindow(nCmdShow);
	wndMain.UpdateWindow();

	// Standard Win32 message loop
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	_Module.Term();
	return msg.wParam;
}