#ifndef __STU_IFO_H__
#define __STU_IFO_H__

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct STU{

    unsigned int _id;
    char _name[20];
    char _sex;   // m(man)/w(woman)
    int _mGrade; // math grade
    int _eGrade; // englih grade
    struct STU * _next;
    struct STU * _pre;

}STU, * PSTU;

typedef struct{

    PSTU _head;
    PSTU _tail;
    int _stucnt;

}STUIFO, * PSTUIFO; // 使用链表管理学生

PSTUIFO
init_stuifo();

void
free_stuifo(PSTUIFO);

void
add_stu_to_stuifo(PSTUIFO);

void
modify_stu_grades(PSTUIFO);

#ifdef __cplusplus
}
#endif

#endif // __STU_IFO_H__ //
