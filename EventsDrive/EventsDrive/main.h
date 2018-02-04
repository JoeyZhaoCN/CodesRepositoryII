#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#define CXCLIENT 720
#define CYCLIENT 500

/* 
+
-			包含头文件
+
*/
#include <windows.h>
#include "dtastc.h"


/*
+
-			结构体定义
+
*/

/*
+
-			函数前向声明
+
*/

LRESULT CALLBACK
WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__ //
