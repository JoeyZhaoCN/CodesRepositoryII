#include "main.h"

// Global
HINSTANCE  g_hinstance;
HWND       g_hwnd;
WPARAM     g_wparam;
LPARAM     g_lparam;

// Program entry
int WINAPI 
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	static char szWndClassName[] = TEXT("hellowin");

	HWND     hwnd;
	MSG      msg;
	WNDCLASS wndclass;

	wndclass.style         = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc   = WndProc;
	wndclass.cbClsExtra    = 0;
	wndclass.cbWndExtra    = 0;
	wndclass.hInstance     = hInstance;
	wndclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName  = NULL;
	wndclass.lpszClassName = szWndClassName;

	if (!RegisterClass(&wndclass)) {

		MessageBox(NULL, TEXT("×¢²áÊ§°Ü"), TEXT("´íÎó"), MB_ICONERROR);
		return 0;

	}

	hwnd = CreateWindow(
		szWndClassName,	
		TEXT("T3D"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, nShowCmd);

	UpdateWindow(hwnd);

	while (TRUE) {

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

			if (msg.message == WM_QUIT) {

				break;

			}

			TranslateMessage(&msg);

			DispatchMessage(&msg);

		}

		GameMain();

	}

	return msg.wParam;

}

// Message deal
LRESULT CALLBACK 
WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {

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

int
GameMain() {



	return 0;

}