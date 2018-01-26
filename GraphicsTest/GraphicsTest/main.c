/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2018.1.26 / 18：40
+
-             修改时间：2018.1.26 / 18：40
+
-             文件名称：main.c
+
-             模块：Graphics图形相关练习
+
-             功能：源文件，包括函数定义，及静态函数的声明和定义
+
*/

#include "main.h"


int WINAPI 
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	static char szWndClassName[] = "hellowin";
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szWndClassName;

	if (!RegisterClass(&wndclass)) {
		MessageBox(NULL, "注册失败", "错误", MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(
		szWndClassName,		//windows class name
		"Joezeo",			//windows caption	
		WS_OVERLAPPEDWINDOW,//windows style
		CW_USEDEFAULT,		//intial x position
		CW_USEDEFAULT,		//intial y position
		WND_WIDTH,		    //intial x size
		WND_HEIGHT,		    //intial y size
		NULL,				//parent wnidow handle
		NULL,				//window menu handle
		hInstance,			//program instance handle
		NULL);				//creation paramenter

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;

}

LRESULT CALLBACK 
WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {

	static int cxClient, cyClient, cxSource, cySource;

	HDC         hdcClient, hdcWindow;

	PAINTSTRUCT ps;

	switch (message) {

	case WM_CREATE:

		cxSource = GetSystemMetrics(SM_CXSIZEFRAME) + GetSystemMetrics(SM_CXSIZE);
		cySource = GetSystemMetrics(SM_CYSIZEFRAME) + GetSystemMetrics(SM_CYSIZE);

		break;

	case WM_SIZE:

		cxClient = LOWORD(lparam);
		cyClient = HIWORD(lparam);

		break;

	case WM_PAINT:

		hdcClient = BeginPaint(hwnd, &ps);
		hdcWindow = GetWindowDC(hwnd);

		for (int y = 0; y < cyClient; y += cySource) {

			for (int x = 0; x < cxClient; x++) {

				BitBlt(hdcClient,
					x, y,
					cxSource, cySource,
					hdcWindow,
					0, 0,
					SRCCOPY);

			}

		}

		EndPaint(hwnd, &ps);
		ReleaseDC(hwnd, hdcWindow);

		break;

	case WM_DESTROY:

		PostQuitMessage(0);

		break;

	}

	return DefWindowProc(hwnd, message, wparam, lparam);

}