#include "main.h"
#include "main.h"

// Global
HINSTANCE     g_hinstance;
HWND          g_hwnd;
WPARAM        g_wparam;
LPARAM        g_lparam;

// Program entry
int WINAPI 
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	// 全局变量 g_hinstance赋值
	g_hinstance = hInstance;

	static char szWndClassName[] = TEXT("hellowin");

	HWND       hwnd;
	MSG        msg;
	WNDCLASSEX wndclass;

	wndclass.cbSize        = sizeof(WNDCLASSEX);
	wndclass.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS | CS_OWNDC;
	wndclass.lpfnWndProc   = WndProc;
	wndclass.cbClsExtra    = 0;
	wndclass.cbWndExtra    = 0;
	wndclass.hInstance     = hInstance;
	wndclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName  = NULL;
	wndclass.lpszClassName = szWndClassName;
	wndclass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wndclass)) {

		MessageBox(NULL, TEXT("注册失败"), TEXT("错误"), MB_ICONERROR);
		return 0;

	}

	RECT   rect;
	SetRect(&rect, 0, 0, CXCLIENT, CYCLIENT);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	hwnd = CreateWindowEx(
		NULL,
		szWndClassName,	
		TEXT("T3D"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	g_hwnd = hwnd;
	
	UpdateWindow(hwnd);

	ShowWindow(hwnd, nShowCmd);

	while (TRUE) {

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

			if (msg.message == WM_QUIT) {

				break;

			}

			TranslateMessage(&msg);

			DispatchMessage(&msg);

		}

	}

	return msg.wParam;

}


// Message deal
LRESULT CALLBACK 
WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {

	// 全局变量 g_wparam, g_lparam赋值
	g_wparam = wparam;
	g_lparam = lparam;

	switch (message) {

	case WM_CREATE: {



	} break;

	case WM_PAINT: {



	} break;

	case WM_DESTROY: {

		PostQuitMessage(0);

	} break;

	}

	return DefWindowProc(hwnd, message, wparam, lparam);

}
