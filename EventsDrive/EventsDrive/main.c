#include "main.h"
#include "main.h"

// Global
HINSTANCE     g_hinstance;
HWND          g_hwnd;
WPARAM        g_wparam;
LPARAM        g_lparam;

HWND     hStartButton;
HWND     hExitButton;
HWND     hRegistButton;
HWND     hWnd1;
HWND     hWnd2;
HWND     hWnd3;
HWND     hWnd4;

// Program entry
int WINAPI 
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	// 全局变量 g_hinstance赋值
	g_hinstance = hInstance;

	static char szWndClassName[] = TEXT("BankWin");

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
		TEXT("Bank System"),
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
	g_hwnd   = hwnd;

	static PSYS pSys;

	switch (message) {

	case WM_CREATE: {

		InitButton();

		pSys = NULL;

	} break;

	case WM_PAINT: {



	} break;

	case WM_COMMAND: {

		int wmID, wmEV;

		wmID = LOWORD(wparam);
		wmEV = HIWORD(wparam);

		switch (wmID) {

		case IDC_STARTBUTTON: {

			if (pSys == NULL) {

				pSys = InitSystem();
				MessageBox(hwnd, TEXT("成功启动系统~"), TEXT("通知"), MB_OK);

			}
			else {

				MessageBox(hwnd, TEXT("系统运行中，请勿重复操作~"), TEXT("错误"), MB_OK);

			}

		} break;

		case IDC_EXITBUTTON: {

			CloseSystem(pSys);
			pSys = NULL;

			MessageBox(hwnd, TEXT("成功关闭系统~"), TEXT("通知"), MB_OK);

		} break;

		case IDC_REGISTBUTTON: {



		} break;

		}

	} break;

	case WM_DESTROY: {

		PostQuitMessage(0);

	} break;

	}

	return DefWindowProc(hwnd, message, wparam, lparam);

}


void
InitButton() {

	hStartButton = CreateWindow(
		TEXT("button"),
		TEXT("开始营业"),
		WS_CHILD | WS_VISIBLE,
		20, 20, 100, 40,
		g_hwnd,
		IDC_STARTBUTTON,
		g_hinstance,
		NULL
	);

	hExitButton = CreateWindow(
		TEXT("button"),
		TEXT("结束营业"),
		WS_CHILD | WS_VISIBLE,
		20, 80, 100, 40,
		g_hwnd,
		IDC_EXITBUTTON,
		g_hinstance,
		NULL
	);

	hRegistButton = CreateWindow(
		TEXT("button"),
		TEXT("顾客挂号"),
		WS_CHILD | WS_VISIBLE,
		300, 20, 100, 40,
		g_hwnd,
		IDC_REGISTBUTTON,
		g_hinstance,
		NULL
	);

	hWnd1 = CreateWindow(
		TEXT("button"),
		TEXT("一号窗口完成业务"),
		WS_CHILD | WS_VISIBLE,
		20, 200, 160, 40,
		g_hwnd,
		IDC_WND_1,
		g_hinstance,
		NULL
	);

	hWnd2 = CreateWindow(
		TEXT("button"),
		TEXT("二号窗口完成业务"),
		WS_CHILD | WS_VISIBLE,
		20, 270, 160, 40,
		g_hwnd,
		IDC_WND_2,
		g_hinstance,
		NULL
	);

	hWnd3 = CreateWindow(
		TEXT("button"),
		TEXT("三号窗口完成业务"),
		WS_CHILD | WS_VISIBLE,
		20, 340, 160, 40,
		g_hwnd,
		IDC_WND_3,
		g_hinstance,
		NULL
	);

	hWnd4 = CreateWindow(
		TEXT("button"),
		TEXT("四号窗口完成业务"),
		WS_CHILD | WS_VISIBLE,
		20, 410, 160, 40,
		g_hwnd,
		IDC_WND_4,
		g_hinstance,
		NULL
	);

}


PSYS
InitSystem() {

	PSYS pSys = (PSYS)malloc(sizeof(SYSTEM));
	if (!pSys)
		exit(OVERFLOW);

	pSys->m_cnt      = 0;
	pSys->m_evQuene  = InitQuene();
	pSys->m_runState = TRUE;

	return pSys;

}


void
CloseSystem(PSYS pSys) {

	assert(pSys != NULL);

	DestroyQuene(pSys->m_evQuene);

	free(pSys);
	pSys = NULL;

}


PEVENT
NewEvent(EVENT_TYPE eventType, PSYS pSys) {

	assert(pSys != NULL);

	PEVENT pEvent = (PEVENT)malloc(sizeof(EVENT));
	if (!pEvent)
		exit(OVERFLOW);

	pEvent->m_eventType = eventType;

	pSys->m_cnt++;
	pEvent->m_idReg = pSys->m_cnt;

	return pEvent;

}