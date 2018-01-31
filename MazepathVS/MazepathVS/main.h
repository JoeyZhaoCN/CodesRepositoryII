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
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "dtastc.h"


/*
+
-			�ṹ�嶨��
+
*/
typedef struct {

	POINT m_pos;

	BOOL m_pass; // �Ƿ���·
	BOOL m_flag; // �Ƿ�����

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
-			����ǰ������
+
*/

PMAZE
Initmaze();

int
DrawMaze(PMAZE);

int
MazePath(PMAZE, POINT, POINT);

int
NextPos(PBLOCK *, PMAZE);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__ //
