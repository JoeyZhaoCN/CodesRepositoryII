#include\
"F:\workspace\gits\CodesRepository\ManagerSys\INFO\stuifo.h"

static PSTU
add_stu();

static PSTU
add_stu(){

    unsigned int id;
    char name[20];
    char sex;
    int mGrade;
    int eGrade;


    PSTU pstu = (PSTU)malloc(sizeof(STU));
    if (!pstu)
        exit(-2);

    printf("please input the id:");
    scanf("%u", &id);

    printf("please input student's name:");
    scanf("%s", name);

    while (1) {

        fflush(stdin);

        printf("please input student's sex:");
        scanf("%c", &sex);

        if(sex == 'm' || sex == 'w')
            break;

    }

    printf("please input the math grade:");
    scanf("%d", &mGrade);

    printf("please input the englih grade:");
    scanf("%d", &eGrade);

    pstu->_id = id;
    strcpy(pstu->_name, name);
    pstu->_sex = sex;
    pstu->_mGrade = mGrade;
    pstu->_eGrade = eGrade;
    pstu->_next = NULL;
    pstu->_pre = NULL;

    return pstu;

}


PSTUIFO
init_stuifo(){

    PSTUIFO pifo = (PSTUIFO)malloc(sizeof(STUIFO));
    if(!pifo)
        exit(-2);

    pifo->_head = NULL;
    pifo->_tail = NULL;
    pifo->_stucnt = 0;

    return pifo;

}


void
free_stuifo(PSTUIFO pifo){

    assert(pifo != NULL);

    if (pifo->_stucnt != 0) {

        PSTU pre = NULL;
        PSTU cur = pifo->_head;

        while (cur != NULL) {

            pre = cur->_next;
            free(cur);
            cur = pre;

        }

    }

    free(pifo);
    pifo = NULL;

}


void
add_stu_to_stuifo(PSTUIFO pifo){

    PSTU newstu = add_stu();

    if (pifo->_stucnt == 0) {

        pifo->_head = newstu;
        pifo->_tail = newstu;

    } else {

        pifo->_tail->_next = newstu;
        newstu->_pre = pifo->_tail;
        pifo->_tail = newstu;

    }

    pifo->_stucnt++;

}
