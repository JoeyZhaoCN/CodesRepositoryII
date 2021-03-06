#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#define CXCLIENT 720
#define CYCLIENT 500

#define IDC_STARTBUTTON  130
#define IDC_EXITBUTTON   131
#define IDC_REGISTBUTTON 132
#define IDC_WND_1        133
#define IDC_WND_2        134
#define IDC_WND_3        135
#define IDC_WND_4        136

#define ID_TIMER         1

/* 
+
-			包含头文件
+
*/
#include <windows.h>
#include "dtastc.h"
#include <stdio.h>


/*
+
-			结构体定义
+
*/
typedef enum {

	regist = 0,
	depart_1,
	depart_2,
	depart_3,
	depart_4,

}EVENT_TYPE;

typedef struct {

// private:
	int    m_cnt;     // 当前挂号的总数
	PQUENE m_evQuene; // 事件队列

} SYSTEM, * PSYS;

typedef struct {
	
	EVENT_TYPE m_eventType;
	int        m_idReg;

}EVENT, * PEVENT;

typedef struct {
	
	BOOL    m_workState;
	PEVENT  m_curEv;

}BWINDOW, * PBWINDOW;



/*
+
-			函数前向声明
+
*/

LRESULT CALLBACK
WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

void
InitButton();

PSYS
InitSystem();

void
CloseSystem(PSYS);

BOOL
isSystemRun(PSYS);

void
TextScreen(PSYS, HWND);

PEVENT
NewEvent(EVENT_TYPE, PSYS);

void
FreeEvent(PEVENT);

PBWINDOW
InitBwindow();

void
FreeBwindow(PBWINDOW);

void
NextClient(PBWINDOW *, PSYS);

BOOL
isWindowFree(PBWINDOW);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__ //
