#include\
"F:\workspace\gits\CodesRepository\ManagerSys\MAIN\main.h"

int main(int argc, char *argv[]){

    PSYS psys = init_sys();
    PSTUIFO pifo = init_stuifo();

    for (;;) {

        show_sysui();

        items_chose(psys);

        page_control(psys, pifo);

    }

    return 0;
}


PSYS
init_sys(){

    PSYS psys = (PSYS)malloc(sizeof(SYS));
    if(!psys)
        exit(-2);

    psys->_chose = 0;

    return psys;

}


void
items_chose(PSYS sys){

    while(1){

        sys->_chose = getch();
        if(sys->_chose >= '1' && sys->_chose <= '3')
            break;

    }

}


void
page_control(PSYS psys, PSTUIFO pifo){

    switch(psys->_chose){

    case '1':
        show_grade_ui(pifo);
        break;

    case '2':
        break;

    case '3':
        break;

    }

}
