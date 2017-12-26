#include\
"F:\workspace\gits\CodesRepository\ManagerSys\MAIN\main.h"

int main(int argc, char *argv[]){

    PSYS psys = init_sys();
    PSTUIFO pifo = init_stuifo();

    for (;;) {

        show_sysui();

        items_chose(psys);

        if (psys->_chose == '0')
            break;

        page_control(psys, pifo);

    }

    free_sys(psys);
    free_stuifo(pifo);

    return 0;
}


PSYS
init_sys(){

    PSYS psys = (PSYS)malloc(sizeof(SYS));
    if (!psys)
        exit(-2);

    psys->_chose = 0;

    return psys;

}


void
free_sys(PSYS psys){

    assert(psys != NULL);

    free(psys);
    psys = NULL;

}


void
items_chose(PSYS sys){

    assert(sys != NULL);

    while (1) {

        sys->_chose = getch();
        if (sys->_chose >= '0' && sys->_chose <= '3')
            break;

    }

}


void
page_control(PSYS psys, PSTUIFO pifo){

    assert(psys != NULL);
    assert(pifo != NULL);

    switch (psys->_chose) {

    case '1':
        show_grade_ui(pifo);
        break;

    case '2':
        add_stuifo_ui(pifo);
        break;

    case '3':
        modify_grade_ui(pifo);
        break;

    }

}
