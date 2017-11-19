#include <windows.h>
#define INITCAPACITY 10000  //RcPoint��ʼ����
#define ADDCAPACITY 10000	//RcPoint��������
typedef struct {
	int x;
	int y;
	int index;
}Point;
typedef struct {
	Point *base;	//����ַ
	int curnum;		//��ǰ����
	int maxnum;		//��ǰ������ɵ���
}RcPoint;//���滭�µĵ������

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AddRcPoint(RcPoint*);//����RcPoint����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
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
		MessageBox(NULL, "ע��ʧ��", "����", MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(
		szWndClassName,		//windows class name
		"Joezeo",			//windows caption	
		WS_OVERLAPPEDWINDOW,//windows style
		CW_USEDEFAULT,		//intial x position
		CW_USEDEFAULT,		//intial y position
		CW_USEDEFAULT,		//intial x size
		CW_USEDEFAULT,		//intial y size
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam,
							LPARAM lparam) {//wparam�Զ����Ƶķ�ʽ������ఴ����Ϣ
	HDC hdc;		//�豸��������			//lparam�Զ����Ƶķ�ʽ�������λ����Ϣ
	PAINTSTRUCT ps;
	RECT rect;

	static Point PrePoint;	//ǰһ����
	static int index = 0;
	static HPEN hpen[3];
	static RcPoint *rcPoint;
	static int ldown = -1;	//��¼���������´���
	
	switch (message) {
	case WM_CREATE:
		hpen[0] = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		hpen[1] = CreatePen(PS_SOLID, 10, RGB(0, 255, 0));
		hpen[2] = CreatePen(PS_SOLID, 15, RGB(0, 0, 255));
		rcPoint = (RcPoint *)malloc(100 * sizeof(RcPoint));
		for (int i = 0; i < 100; i++) {
			(rcPoint + i)->base = (Point *)malloc(INITCAPACITY * sizeof(Point));
			(rcPoint + i)->curnum = 0;
			(rcPoint + i)->maxnum = INITCAPACITY;
		}
		
		return 0;
	case WM_KEYDOWN://��ⰴ��
		if (VK_RETURN == wparam) {
			InvalidateRect(hwnd, NULL, TRUE);
			}
		return 0;
	case WM_MOUSEMOVE:
		if (MK_LBUTTON & wparam) {//����������������
			Point point;
			hdc = GetDC(hwnd);
			point.x = LOWORD(lparam);
			point.y = HIWORD(lparam);

			if ((rcPoint + ldown)->curnum == (rcPoint + ldown)->maxnum) {
				AddRcPoint(&rcPoint);
			}
			((rcPoint + ldown)->base + (rcPoint + ldown)->curnum)->x = point.x;
			((rcPoint + ldown)->base + (rcPoint + ldown)->curnum)->y = point.y;
			((rcPoint + ldown)->base + (rcPoint + ldown)->curnum)->index = index;
			(rcPoint + ldown)->curnum++;
			
			//SetPixel(hdc, point.x, point.y, RGB(255,0,0));
			SelectObject(hdc, hpen[index]);
			MoveToEx(hdc, PrePoint.x, PrePoint.y, NULL);
			LineTo(hdc, point.x, point.y);
			PrePoint = point;
			ReleaseDC(hwnd, hdc);
		}
		return 0;
	case WM_LBUTTONDOWN:
		int x = LOWORD(lparam);	//ȡ����λ
		int y = HIWORD(lparam);//ȡ����λ
		ldown++;
		PrePoint.x = x;
		PrePoint.y = y;
		if ((rcPoint + ldown)->curnum == (rcPoint + ldown)->maxnum) {
			AddRcPoint(&rcPoint);
		}
		((rcPoint + ldown)->base + (rcPoint + ldown)->curnum)->x = PrePoint.x;
		((rcPoint + ldown)->base + (rcPoint + ldown)->curnum)->y = PrePoint.y;
		((rcPoint + ldown)->base + (rcPoint + ldown)->curnum)->index = index;
		(rcPoint + ldown)->curnum++;
		return 0;
	case WM_RBUTTONDOWN:
		int tx = LOWORD(lparam);	//ȡ����λ
		int ty = HIWORD(lparam);	//ȡ����λ
		index++;
		if (index == 3) index = 0;
		if ((rcPoint + ldown)->curnum == (rcPoint + ldown)->maxnum) {
			AddRcPoint(&rcPoint);
		}
		((rcPoint + ldown)->base + (rcPoint + ldown)->curnum)->x = tx;
		((rcPoint + ldown)->base + (rcPoint + ldown)->curnum)->y = ty;
		((rcPoint + ldown)->base + (rcPoint + ldown)->curnum)->index = index;
		(rcPoint + ldown)->curnum++;
		return 0;
	case WM_PAINT://���ڱ�������ػ�ʱ,����Ч������л���
		hdc = BeginPaint(hwnd, &ps);//�����豸��������
		for (int j = 0; j < ldown + 1; j++) {
			for (int i = 0; i < (rcPoint + j)->curnum - 1; i++) {
				SelectObject(hdc, hpen[((rcPoint + j)->base + i)->index]);
				if ((((rcPoint + j)->base + i)->index != ((rcPoint + j)->base + i)->index) && i != 0)
					SelectObject(hdc, hpen[((rcPoint + j)->base + i + 1)->index]);
				MoveToEx(hdc, ((rcPoint + j)->base + i)->x, ((rcPoint + j)->base + i)->y, NULL);
				LineTo(hdc, ((rcPoint + j)->base + i + 1)->x, ((rcPoint + j)->base + i + 1)->y);
			}
		}
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		DeleteDC(hpen);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wparam, lparam);
}
void AddRcPoint(RcPoint *rcPoint) {
	Point *p = (Point *)realloc(rcPoint->base, (rcPoint->curnum + ADDCAPACITY) * sizeof(Point));
	if (!p) exit(-2);
	rcPoint->base = p;
	rcPoint->maxnum += ADDCAPACITY;
}