#include "Hanoi.h"

int main(int argc, char *argv[]) {

	PSTACK A = InitStack(sizeof(int));
	PSTACK B = InitStack(sizeof(int));
	PSTACK C = InitStack(sizeof(int));

	int tmp;

	for (int i = 0; i < 10; i++) {

		tmp = i;

		Push(A, &tmp, sizeof(int));

	}

	Hanoi(10, A, B, C);

	DrawStack(C);

	system("pause");
	return 0;

}

Status
Hanoi(int n, PSTACK A, PSTACK B, PSTACK C) {
	// Hanooi 算法， 编号为1 - n的块从A移动到C，B作为辅助
	// 最底层的编号为n， 及栈底元素编号为n

	if (n == 1) {

		MoveBlock(1, A, C);

	}
	else {

		Hanoi(n - 1, A, C, B); // 将 1 - n-1 编号的块从A移至B， C作为辅助
		MoveBlock(n, A, C);    // 将栈底元素，及编号为n的块 从A移至C
		Hanoi(n - 1, B, A, C); // 将 1 ~ n-1 编号的块从B移至C， A作为辅助

	}

	return OK;

}

Status
MoveBlock(int n, PSTACK source, PSTACK target) {

	// 移动块编号为n的块，从 A 移动到 C

	int tmp = 0;

	Pop(source, &tmp, sizeof(int));

	Push(target, &tmp, sizeof(int));

	return OK;

}

Status
DrawStack(PSTACK pstack) {

	assert(pstack != NULL);

	int tmp;

	while (!StackEmpty(pstack)) {

		Pop(pstack, &tmp, sizeof(int));

		printf("%d\n", tmp);

	}

	return 0;

}