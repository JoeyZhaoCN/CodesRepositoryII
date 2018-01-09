#ifndef __MAZE_H__
#define __MAZE_H__

#ifdef __cplusplus
extern "C"{
#endif

#include <stdlib.h>
#include <assert.h>

// 状态码定义 //
#define TRUE      1
#define FALSE     0
#define SUCCESS   1
#define ERROR    -1
#define OVERFLOW -2

typedef int Status;

typedef struct{

    int x;
    int y;

}POINT;

typedef struct{

    POINT m_staPos; // 迷宫起点
    POINT m_endPos; // 迷宫终点

    int ** m_map;   // 迷宫地图，用一个二维数组存储
                    // 0表示墙壁，1表示路径
}MAZE, * PMAZE;

PMAZE
InitMaze();
// 初始化迷宫

Status
FreeMaze(PMAZE);
// 释放迷宫内存资源

#ifdef __cplusplus
}
#endif

#endif // __MAZE_H__ //
