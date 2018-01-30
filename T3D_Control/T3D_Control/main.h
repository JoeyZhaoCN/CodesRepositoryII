#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif


/* 
+
-			包含头文件
+
*/
#include <windows.h>


/*
+
-			函数前向声明
+
*/
LRESULT CALLBACK 
WndProc(HWND, UINT, WPARAM, LPARAM);

int
GameMain();



#ifdef __cplusplus
}
#endif

#endif // XX //
