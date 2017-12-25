#include\
"F:\workspace\gits\CodesRepository\ManagerSys\UI\sysui.h"


void
show_sysui(){

    system("cls");
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


void
show_grade_ui(PSTUIFO pifo){

    int _flag;

    system("cls");

    printf("push b/B back to main menu.");

    while(1){

        _flag = getch();
        if(_flag == 'b' || _flag == 'B')
            break;

    }

}
