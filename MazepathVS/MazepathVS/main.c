#include "main.h"

int main (int argc, char *argv[]) {

	PMAZE pmaze = Initmaze();

	DrawMaze(pmaze);

	system("pause");
	return 0;

}

PMAZE
Initmaze() {

	PMAZE pmaze = (PMAZE)malloc(sizeof(MAZE));
	if (!pmaze)
		exit(-2);

	pmaze->m_blocks = (PBLOCK *)malloc(10 * sizeof(PBLOCK));
	if (!pmaze->m_blocks)
		exit(-2);

	for (int i = 0; i < 10; i++) {

		*(pmaze->m_blocks + i) = (PBLOCK)malloc(10 * sizeof(BLOCK));
		if (!*(pmaze->m_blocks + i))
			exit(-2);

	}

	for(int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {

			(*(pmaze->m_blocks + i) + j)->m_pos.x = i;
			(*(pmaze->m_blocks + i) + j)->m_pos.y = j;
			(*(pmaze->m_blocks + i) + j)->m_pass = FALSE;
			(*(pmaze->m_blocks + i) + j)->m_up = FALSE;
			(*(pmaze->m_blocks + i) + j)->m_right = FALSE;
			(*(pmaze->m_blocks + i) + j)->m_down = FALSE;
			(*(pmaze->m_blocks + i) + j)->m_left = FALSE;
			(*(pmaze->m_blocks + i) + j)->m_over = FALSE;

		}

	(*(pmaze->m_blocks + 1) + 1)->m_pass = TRUE;
	(*(pmaze->m_blocks + 1) + 2)->m_pass = TRUE;
	(*(pmaze->m_blocks + 1) + 4)->m_pass = TRUE;
	(*(pmaze->m_blocks + 1) + 5)->m_pass = TRUE;
	(*(pmaze->m_blocks + 1) + 6)->m_pass = TRUE;
	(*(pmaze->m_blocks + 1) + 8)->m_pass = TRUE;
	(*(pmaze->m_blocks + 2) + 1)->m_pass = TRUE;
	(*(pmaze->m_blocks + 2) + 2)->m_pass = TRUE;
	(*(pmaze->m_blocks + 2) + 4)->m_pass = TRUE;
	(*(pmaze->m_blocks + 2) + 5)->m_pass = TRUE;
	(*(pmaze->m_blocks + 2) + 6)->m_pass = TRUE;
	(*(pmaze->m_blocks + 2) + 8)->m_pass = TRUE;
	(*(pmaze->m_blocks + 3) + 1)->m_pass = TRUE;
	(*(pmaze->m_blocks + 3) + 2)->m_pass = TRUE;
	(*(pmaze->m_blocks + 3) + 3)->m_pass = TRUE;
	(*(pmaze->m_blocks + 3) + 4)->m_pass = TRUE;
	(*(pmaze->m_blocks + 3) + 7)->m_pass = TRUE;
	(*(pmaze->m_blocks + 3) + 8)->m_pass = TRUE;
	(*(pmaze->m_blocks + 4) + 1)->m_pass = TRUE;
	(*(pmaze->m_blocks + 4) + 5)->m_pass = TRUE;
	(*(pmaze->m_blocks + 4) + 6)->m_pass = TRUE;
	(*(pmaze->m_blocks + 4) + 7)->m_pass = TRUE;
	(*(pmaze->m_blocks + 4) + 8)->m_pass = TRUE;
	(*(pmaze->m_blocks + 5) + 1)->m_pass = TRUE;
	(*(pmaze->m_blocks + 5) + 2)->m_pass = TRUE;
	(*(pmaze->m_blocks + 5) + 3)->m_pass = TRUE;
	(*(pmaze->m_blocks + 5) + 5)->m_pass = TRUE;
	(*(pmaze->m_blocks + 5) + 6)->m_pass = TRUE;
	(*(pmaze->m_blocks + 5) + 7)->m_pass = TRUE;
	(*(pmaze->m_blocks + 5) + 8)->m_pass = TRUE;
	(*(pmaze->m_blocks + 6) + 1)->m_pass = TRUE;
	(*(pmaze->m_blocks + 6) + 3)->m_pass = TRUE;
	(*(pmaze->m_blocks + 6) + 4)->m_pass = TRUE;
	(*(pmaze->m_blocks + 6) + 5)->m_pass = TRUE;
	(*(pmaze->m_blocks + 6) + 7)->m_pass = TRUE;
	(*(pmaze->m_blocks + 6) + 8)->m_pass = TRUE;
	(*(pmaze->m_blocks + 7) + 1)->m_pass = TRUE;
	(*(pmaze->m_blocks + 7) + 5)->m_pass = TRUE;
	(*(pmaze->m_blocks + 7) + 8)->m_pass = TRUE;
	(*(pmaze->m_blocks + 8) + 2)->m_pass = TRUE;
	(*(pmaze->m_blocks + 8) + 3)->m_pass = TRUE;
	(*(pmaze->m_blocks + 8) + 4)->m_pass = TRUE;
	(*(pmaze->m_blocks + 8) + 5)->m_pass = TRUE;
	(*(pmaze->m_blocks + 8) + 6)->m_pass = TRUE;
	(*(pmaze->m_blocks + 8) + 7)->m_pass = TRUE;
	(*(pmaze->m_blocks + 8) + 8)->m_pass = TRUE;

	return pmaze;

}

int
DrawMaze(PMAZE pmaze) {

	assert(pmaze != NULL);

	for (int i = 0; i < 10; i++) {

		for (int j = 0; j < 10; j++) {

			if ((*(pmaze->m_blocks + i) + j)->m_pass)
				printf(". ");
			else
				printf("* ");

		}

		printf("\n");

	}
		
	return 0;

}

int
MazePath(PMAZE pmaze, POINT start, POINT ending) {

	assert(pmaze != NULL);

	PBLOCK curpos = (*(pmaze->m_blocks + start.x) + start.y);

	PSTACK buffer = InitStack();

	do {

		if (curpos->m_pass) {

			Push(buffer, curpos, sizeof(BLOCK));

			//GetTop(buffer, curpos, sizeof(BLOCK));

			if (curpos->m_pos == ending)
				break;

		}

	} while (!StackEmpty(buffer));

}
