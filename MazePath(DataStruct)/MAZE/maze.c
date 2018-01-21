//#include "F:/workspace/gits/CodesRepository/MazePath(DataStruct)/MAZE/maze.h"
#include "maze.h"

PMAZE
InitMaze() {

    PMAZE pmaze = (PMAZE)malloc(sizeof(MAZE));
    if (!pmaze)
        exit(OVERFLOW);

    pmaze->m_staPos.x = 1;
    pmaze->m_staPos.y = 1;
    pmaze->m_endPos.x = 8;
    pmaze->m_endPos.y = 8;

    pmaze->m_map = (int **)malloc(10 * sizeof(int *));
    if (!(pmaze->m_map))
        exit(OVERFLOW);

    for(int i = 0; i < 10; i++){

        *(pmaze->m_map + i) = (int *)malloc(10 * sizeof(int));
        if (!(pmaze->m_map + i))
            exit(OVERFLOW);

    }

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            *(*(pmaze->m_map + i) + j) = 1;
        }
    }

    for(int i = 0; i < 10; i++){

        *(*(pmaze->m_map + 0) + i) = 0;

        *(*(pmaze->m_map + 9) + i) = 0;

    }

    for(int i = 0; i < 10; i++){

        *(*(pmaze->m_map + i) + 0) = 0;
        *(*(pmaze->m_map + i) + 9) = 0;

    }

    *(*(pmaze->m_map + 1) + 3) = 0;
    *(*(pmaze->m_map + 1) + 7) = 0;
    *(*(pmaze->m_map + 2) + 3) = 0;
    *(*(pmaze->m_map + 2) + 7) = 0;
    *(*(pmaze->m_map + 3) + 5) = 0;
    *(*(pmaze->m_map + 3) + 6) = 0;
    *(*(pmaze->m_map + 4) + 2) = 0;
    *(*(pmaze->m_map + 4) + 3) = 0;
    *(*(pmaze->m_map + 4) + 4) = 0;
    *(*(pmaze->m_map + 5) + 4) = 0;
    *(*(pmaze->m_map + 6) + 2) = 0;
    *(*(pmaze->m_map + 6) + 6) = 0;
    *(*(pmaze->m_map + 7) + 2) = 0;
    *(*(pmaze->m_map + 7) + 3) = 0;
    *(*(pmaze->m_map + 7) + 4) = 0;
    *(*(pmaze->m_map + 7) + 6) = 0;
    *(*(pmaze->m_map + 7) + 7) = 0;
    *(*(pmaze->m_map + 8) + 1) = 0;

    return pmaze;

}
// 初始化迷宫

Status
FreeMaze(PMAZE _pmaze) {

    assert(_pmaze != NULL);

    for(int i = 0; i < 10; i++){

        free(*(_pmaze->m_map + i));

    }

    free(_pmaze->m_map);

    free(_pmaze);
    _pmaze = NULL;

    return SUCCESS;

}
// 释放迷宫内存资源
