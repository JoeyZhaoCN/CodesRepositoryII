#include\
"F:\workspace\gits\CodesRepository\ManagerSys\UI\sysui.h"

static void
show_title();

static void
show_title(){

    system("cls");
    printf("----------------------------------------------------\n");
    printf("|            students infomation system            |\n");
    printf("|                                                  |\n");
    printf("|            editor:         JOEZEO                |\n");
    printf("|            VERSION:        0.1.0                 |\n");
    printf("----------------------------------------------------\n");

}

void
show_sysui(){

    show_title();

    printf("\nchose the operation:\n");
    printf("0.exit manage system.\n");
    printf("1.view students grades.\n");
    printf("2.add students information.\n");
    printf("3.modify students grades.\n");

}


void
show_grade_ui(PSTUIFO pifo){

    assert(pifo != NULL);

    int _flag;

    show_title();

    printf("\npresent students counts: %d\n", pifo->_stucnt);

    if (pifo->_stucnt != 0) {

        PSTU cur = pifo->_head;

        printf("id\tname\tsex\tmath\teng\n");

        while (cur != NULL) {

            printf("%u\t%s\t%c\t%d\t%d\n", cur->_id, cur->_name,
                    cur->_sex, cur->_mGrade, cur->_eGrade);
            cur = cur->_next;

        }

    }

    printf("\npush b/B back to main menu.");

    while (1) {

        _flag = getch();
        if (_flag == 'b' || _flag == 'B')
            break;

    }

}


void
add_stuifo_ui(PSTUIFO pifo){

    assert(pifo != NULL);

    int _flag;

    while(1){

        show_title();

        add_stu_to_stuifo(pifo);

        printf("\npush b/B back to main menu.\n");
        printf("push r/R to continue add students.\n");

        while (1) {

            _flag = getch();
            if (_flag == 'b' || _flag == 'B')
                return;
            if (_flag == 'r' || _flag == 'R')
                break;

        }

    }

}
