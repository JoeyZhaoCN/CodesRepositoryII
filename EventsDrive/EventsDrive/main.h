#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#define CXCLIENT 720
#define CYCLIENT 500

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

/*
+
-			����ǰ������
+
*/

LRESULT CALLBACK
WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__ //
