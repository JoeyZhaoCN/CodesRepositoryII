#ifndef __HANOI_H__
#define __HANOI_H__

#ifdef __cplusplus
extern "C" {
#endif


/* 
+
-			包含头文件
+
*/
#include "dtastc.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


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
