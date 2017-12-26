#include "main.h"

int main(int argc, char *argv[]){

    NumSysConverse(158, 2);
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
