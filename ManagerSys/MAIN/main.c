#include\
"F:\workspace\gits\CodesRepository\ManagerSys\MAIN\main.h"

int main(int argc, char *argv[]){

    PSYS psys = init_sys();

    for (;;) {

        show_sysui();

        while(1){

            int flag = items_chose(psys);

            if(flag)
                break;    

        }

    }

    return 0;
}

PSYS
init_sys(){

    PSYS psys = (PSYS)malloc(sizeof(SYS));

    psys->items_chose = 0;

    return psys;

}
