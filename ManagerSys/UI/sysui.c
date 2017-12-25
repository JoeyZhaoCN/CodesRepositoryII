#include\
"F:\workspace\gits\CodesRepository\ManagerSys\UI\sysui.h"


void
show_sysui(){

    printf("----------------------------------------------------\n");
    printf("|            students infomation system            |\n");
    printf("|                                                  |\n");
    printf("|            editor:         JOEZEO                |\n");
    printf("|            VERSION:        0.1.0                 |\n");
    printf("----------------------------------------------------\n");
    printf("\nchose the operation:\n");
    printf("1.view students grades.\n");
    printf("2.add students information.\n");
    printf("3.modify students grades.\n");

}

int
items_chose(PSYS sys){

    sys->items_chose = (int)getch();

    if(sys->items_chose < 1 || sys->items_chose > 3)
        return 0;

    return 1;

}
