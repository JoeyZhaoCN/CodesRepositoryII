/*
+
-             ���ߣ�Joezeo < joezeo@outlook.com >
+
-             ����ʱ�䣺2018.1.26 / 18��40
+
-             �޸�ʱ�䣺2018.1.26 / 18��40
+
-             �ļ����ƣ�main.h
+
-             ģ�飺Graphicsͼ�������ϰ
+
-             ���ܣ�ͷ�ļ�������ͷ�ļ��������궨�壬�ṹ�嶨�壬����ǰ��������
+
*/
#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif


/* 
+
-			����ͷ�ļ�
+
*/
#include <windows.h>
#pragma comment(lib,"msimg32.lib")
#pragma comment(lib,"winmm.lib")

/*
+
-			�궨�嶨��
+
*/
#define WND_WIDTH  1080
#define WND_HEIGHT 720

/*
+
-			����ǰ������
+
*/

LRESULT CALLBACK 
WndProc(HWND, UINT, WPARAM, LPARAM);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__ //