//#include "F:/workspace/gits/CodesRepository/MazePath(DataStruct)/MAIN/main.h"
#include "main.h"

int main(int argc, char *argv[]) {

    PMAZE pmaze = InitMaze();

    FreeMaze(pmaze);

    system("pause");

    return 0;

}
