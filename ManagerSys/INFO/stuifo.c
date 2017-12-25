#include\
"F:\workspace\gits\CodesRepository\ManagerSys\INFO\stuifo.h"

PSTUIFO
init_stuifo(){

    PSTUIFO psifo = (PSTUIFO)malloc(sizeof(STUIFO));
    if(!psifo)
        exit(-2);

    psifo->_head = NULL;
    psifo->_tail = NULL;
    psifo->_stucnt = 0;

    return psifo;

}
