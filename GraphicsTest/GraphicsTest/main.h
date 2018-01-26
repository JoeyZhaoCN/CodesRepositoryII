/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2018.1.26 / 18：40
+
-             修改时间：2018.1.26 / 18：40
+
-             文件名称：main.h
+
-             模块：Graphics图形相关练习
+
-             功能：头文件，包括头文件包含，宏定义，结构体定义，函数前向声明等
+
*/
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
#pragma comment(lib,"msimg32.lib")
#pragma comment(lib,"winmm.lib")

/*
+
-			宏定义定义
+
*/
#define WND_WIDTH  1080
#define WND_HEIGHT 720

/*
+
-			函数前向声明
+
*/

LRESULT CALLBACK 
WndProc(HWND, UINT, WPARAM, LPARAM);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__ //