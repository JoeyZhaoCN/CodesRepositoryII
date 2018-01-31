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
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dtastc.h>
#include <windows.h>


/*
+
-			结构体定义
+
*/
typedef struct {

	POINT m_pos;

	BOOL m_pass;

	BOOL m_up;
	BOOL m_right;
	BOOL m_down;
	BOOL m_left;
	
	BOOL m_over;

}BLOCK, * PBLOCK;

typedef struct  {
	
	PBLOCK *m_blocks;

}MAZE, * PMAZE;


/*
+
-			函数前向声明
+
*/

PMAZE
Initmaze();

int
DrawMaze(PMAZE);

int
MazePath(PMAZE, POINT, POINT);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__ //
