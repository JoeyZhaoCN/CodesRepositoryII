#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include\
"F:\workspace\gits\CodesRepository\ManagerSys\UI\sysui.h"
#include\
"F:\workspace\gits\CodesRepository\ManagerSys\INFO\stuifo.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct{

    int _chose;

}SYS, * PSYS;

void
items_chose(PSYS);

PSYS
init_sys();

void
page_control(PSYS, PSTUIFO);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__ //
