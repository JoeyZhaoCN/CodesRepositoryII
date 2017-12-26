#include "main.h"

int main(int argc, char *argv[]){

    int arg;
    int sys;

    while (1) {

        system("cls");
        printf("please input a number:");
        scanf("%d", &arg);
        printf("please input conversion number system:");
        scanf("%d", &sys);
        NumSysConverse(arg, sys);

        printf("\nexit program?\ne/E to exit.\npush other key to continue.");

        arg = getch();
        if (arg == 'e' || arg == 'E')
            break;

    }


    return 0;

}

void
NumSysConverse(const int _arg, const int _numsys){

    int tmp = _arg;
    int les = 0;
    PSTACK psta = InitStack();

    while (tmp != 0) {

        les = tmp % _numsys;
        Push(psta, &les, sizeof(int));
        tmp /= _numsys;

    }

    while (!StackEmpty(psta)) {

        Pop(psta, &tmp, sizeof(int));
        printf("%d", tmp);

    }

    printf("\n");

    DestroyStack(psta);

}
