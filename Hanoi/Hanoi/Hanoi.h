#ifndef __HANOI_H__
#define __HANOI_H__

#ifdef __cplusplus
extern "C" {
#endif


/* 
+
-			����ͷ�ļ�
+
*/
#include "dtastc.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


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
Status
Hanoi(int, PSTACK, PSTACK, PSTACK);

Status
MoveBlock(int, PSTACK, PSTACK);

Status
DrawStack(PSTACK);

#ifdef __cplusplus
}
#endif

#endif // __HANOI_H__ //
