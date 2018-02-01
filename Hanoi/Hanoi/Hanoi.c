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
	// Hanooi �㷨�� ���Ϊ1 - n�Ŀ��A�ƶ���C��B��Ϊ����
	// ��ײ�ı��Ϊn�� ��ջ��Ԫ�ر��Ϊn

	if (n == 1) {

		MoveBlock(1, A, C);

	}
	else {

		Hanoi(n - 1, A, C, B); // �� 1 - n-1 ��ŵĿ��A����B�� C��Ϊ����
		MoveBlock(n, A, C);    // ��ջ��Ԫ�أ������Ϊn�Ŀ� ��A����C
		Hanoi(n - 1, B, A, C); // �� 1 ~ n-1 ��ŵĿ��B����C�� A��Ϊ����

	}

	return OK;

}

Status
MoveBlock(int n, PSTACK source, PSTACK target) {

	// �ƶ�����Ϊn�Ŀ飬�� A �ƶ��� C

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