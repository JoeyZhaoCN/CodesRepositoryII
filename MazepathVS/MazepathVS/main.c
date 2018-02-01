#include "main.h"

int main (int argc, char *argv[]) {

	PMAZE pmaze = Initmaze();

	POINT start;
	POINT ending;

	start.x = 1;
	start.y = 1;

	ending.x = 8;
	ending.y = 8;

	DrawMaze(pmaze);

	MazePath(pmaze, start, ending);

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
			(*(pmaze->m_blocks + i) + j)->m_flag = FALSE;

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

	BOOL bingo = FALSE;

	PBLOCK curpos = (*(pmaze->m_blocks + start.x) + start.y);

	PSTACK buffer = InitStack(sizeof(PBLOCK));

	do {

		if (curpos->m_pass && !curpos->m_over) {

			if (!curpos->m_flag) {

				curpos->m_flag = TRUE;

				Push(buffer, &curpos, sizeof(PBLOCK));

			}

			if (curpos->m_pos.x == ending.x && curpos->m_pos.y == ending.y) {

				bingo = TRUE;

				break;

			}

			NextPos(&curpos, pmaze);

		}
		else {

			if (!StackEmpty(buffer) && curpos->m_over) { // 若栈不空，且栈顶四周已探索完毕

				Pop(buffer, &curpos, sizeof(PBLOCK));

				GetTop(buffer, &curpos, sizeof(PBLOCK));

			}
			if(!curpos->m_pass){

				GetTop(buffer, &curpos, sizeof(PBLOCK));

			}

		}

	} while (!StackEmpty(buffer));

	if (bingo) {

		printf("成功到达终点~\n");
		DrawRoute(buffer);

	}
	else {

		printf("到达终点失败~\n");

	}

	return 0;

}

int
NextPos(PBLOCK * pblock, PMAZE pmaze) {

	assert(pblock != NULL);
	assert(pmaze != NULL);

	if (!(*pblock)->m_up) {

		(*pblock)->m_up = TRUE;

		if ((*pblock)->m_pos.x > 0) {

			if (!(*(pmaze->m_blocks + (*pblock)->m_pos.x - 1) + (*pblock)->m_pos.y)->m_flag) {

				(*pblock) = (*(pmaze->m_blocks + (*pblock)->m_pos.x - 1) + (*pblock)->m_pos.y);

				if(!(*pblock)->m_pass)
					(*pblock)->m_flag = TRUE;

			}
				

		}	

	}
	else if (!(*pblock)->m_right) {

		(*pblock)->m_right = TRUE;

		if ((*pblock)->m_pos.y < 9) {

			if (!(*(pmaze->m_blocks + (*pblock)->m_pos.x) + (*pblock)->m_pos.y + 1)->m_flag) {

				(*pblock) = (*(pmaze->m_blocks + (*pblock)->m_pos.x) + (*pblock)->m_pos.y + 1);

				if (!(*pblock)->m_pass)
					(*pblock)->m_flag = TRUE;


			}
				

		}

	}
	else if (!(*pblock)->m_down) {

		(*pblock)->m_down = TRUE;

		if ((*pblock)->m_pos.x < 9) {

			if (!(*(pmaze->m_blocks + (*pblock)->m_pos.x + 1) + (*pblock)->m_pos.y)->m_flag) {

				(*pblock) = (*(pmaze->m_blocks + (*pblock)->m_pos.x + 1) + (*pblock)->m_pos.y);

				if (!(*pblock)->m_pass)
					(*pblock)->m_flag = TRUE;

			}
				

		}

	}
	else if (!(*pblock)->m_left) {

		(*pblock)->m_left = TRUE;

		if ((*pblock)->m_pos.y > 0) {

			if (!(*(pmaze->m_blocks + (*pblock)->m_pos.x) + (*pblock)->m_pos.y - 1)->m_flag) {

				(*pblock) = (*(pmaze->m_blocks + (*pblock)->m_pos.x) + (*pblock)->m_pos.y - 1);

				if (!(*pblock)->m_pass)
					(*pblock)->m_flag = TRUE;

			}
				

		}

	}
	else {

		(*pblock)->m_over = TRUE;

	}

	return 0;

}

int
DrawRoute(PSTACK * pstack) {

	assert(pstack != NULL);

	PSTACK buffer = InitStack(sizeof(PBLOCK));

	PBLOCK tmp = NULL;

	while (!StackEmpty(pstack)) {

		Pop(pstack, &tmp, sizeof(PBLOCK));
		Push(buffer, &tmp, sizeof(PBLOCK));

	}

	while (!StackEmpty(buffer)) {

		Pop(buffer, &tmp, sizeof(PBLOCK));

		printf("( %d , %d )\t", tmp->m_pos.x, tmp->m_pos.y);

	}

	return 1;

}
