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
-			����ͷ�ļ�
+
*/
#include <windows.h>
#include "dtastc.h"


/*
+
-			�ṹ�嶨��
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

	int    m_cnt;     // ��ǰ�Һŵ�����
	PQUENE m_evQuene; // �¼�����
	BOOL   m_runState;// ϵͳ����״̬

} SYSTEM, * PSYS;

typedef struct {
	
	EVENT_TYPE m_eventType;

	int        m_idReg;

}EVENT, * PEVENT;


/*
+
-			����ǰ������
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

PEVENT
NewEvent(EVENT_TYPE, PSYS);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__ //
