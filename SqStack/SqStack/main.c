/**********************************************
               Editor:Joezeo			                       
          E-mail:joezeo@outlook.com                  
            Date:2017/12/19/20/53     
**********************************************/
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define STACKINITSIZE	100	// ����ռ��ʼ������
#define STACKINCREMENT	100 // ����ռ��������

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define OVERFLOW -2

typedef int ElemType;
typedef int Status;

typedef struct {

	ElemType *base;	// ջ��ָ��
	ElemType *top;	// ջ��ָ��
	int	stacksize;	// ջ������
	int cnt;		// ջ��ǰԪ�ظ���

}SqStack;


/*
**			����ǰ������
*/
SqStack *
InitStack();

Status
DestroyStack(SqStack *);

Status
ClearStack(SqStack *);

Status
StackEmpty(SqStack *);

int
StackLength(SqStack *);

Status
GetTop(SqStack *, ElemType *);

Status
AddStackSize(SqStack *);

Status
Push(SqStack *, ElemType);

Status
Pop(SqStack *, ElemType *);

Status
StackTraverse(const SqStack *);


/*
**			���������������
*/
int main()
{
	SqStack *sqs = InitStack();
	ElemType e;

	for (int i = 0; i < 110; i++) {

		Push(sqs, i);

	}

	printf("Ŀǰջ���ȣ�%d\n", StackLength(sqs));
	printf("����ջ��\n");
	StackTraverse(sqs);

	Pop(sqs, &e);
	printf("ջ��Ԫ�س�ջ��%d\n", e);
	printf("Ŀǰջ���ȣ�%d\n", StackLength(sqs));

	DestroyStack(sqs);
	
	system("pause");
	return 0;
}

/*
**			��������
*/
SqStack *
InitStack() {

	/*
		����һ����ջ
	*/

	SqStack *sqs;

	sqs = (SqStack *)malloc(sizeof(SqStack));

	if (!sqs) exit(OVERFLOW);

	sqs->base = (ElemType *)malloc(STACKINITSIZE * sizeof(ElemType));

	if (!(sqs->base)) exit(OVERFLOW);

	sqs->top = sqs->base;

	sqs->stacksize = STACKINITSIZE;

	sqs->cnt = 0;

	return sqs;

}

Status
DestroyStack(SqStack *sqs) {

	/*
		����ջ���ͷ���Դ
	*/

	assert(sqs != NULL);

	free(sqs->base);
	sqs->base = NULL;
	sqs->top = NULL;

	free(sqs);
	sqs = NULL;

	printf("ջ�ѳɹ�����\n");

	return OK;

}

Status
ClearStack(SqStack *sqs) {

	assert(sqs != NULL);

	sqs->top = sqs->base;

	sqs->cnt = 0;

	return OK;

}

Status
StackEmpty(SqStack *sqs) {

	/*
		��ջΪ��ջ������TRUE�����򷵻�FALSE
	*/

	assert(sqs != NULL);

	if (sqs->cnt == 0)
		return TRUE;
	else
		return FALSE;

}

int
StackLength(SqStack *sqs) {

	/*
		����ջԪ�صĸ�������ջ�ĳ���
	*/

	assert(sqs != NULL);

	return sqs->cnt;

}

Status
GetTop(SqStack *sqs, ElemType *e) {

	/*
		��ջ���գ���e����ջ��Ԫ�أ�������OK�����򷵻�ERROR
	*/

	assert(sqs != NULL);

	assert(e != NULL);

	if (StackEmpty(sqs))
		return ERROR;

	*e = *(sqs->top - 1);

	return OK;

}

Status
AddStackSize(SqStack *sqs) {

	/*
		����ջ������
	*/

	assert(sqs != NULL);

	ElemType *add = (ElemType *)realloc(sqs->base,
		(sqs->stacksize + STACKINCREMENT) * sizeof(ElemType));

	if (!add) exit(OVERFLOW);

	sqs->base = add;
	sqs->stacksize += STACKINCREMENT;

	printf("ջ�����Զ�����\n");

	return OK;

}

Status
Push(SqStack *sqs, ElemType e) {

	/*
		����Ԫ��eΪ�µ�ջ��Ԫ��
	*/

	assert(sqs != NULL);

	if (sqs->cnt == sqs->stacksize)
		AddStackSize(sqs);

	*(sqs->top) = e;

	(sqs->top)++;

	(sqs->cnt)++;

	return OK;

}

Status
Pop(SqStack *sqs, ElemType *e) {

	/*
		��ջ���գ���ɾ��ջ��Ԫ�أ���e������ֵ
	*/

	assert(sqs != NULL);

	if (StackEmpty(sqs))
		return ERROR;

	(sqs->top)--;

	(sqs->cnt)--;

	*e = *(sqs->top);

	return OK;

}

Status
StackTraverse(const SqStack *sqs) {

	/*
		��ջ�׵�ջ�����α���ջ
	*/

	assert(sqs != NULL);

	ElemType *tmp = sqs->base;

	for (; tmp != (sqs->top); tmp++) {

		printf("%d\t", *tmp);

	}

	return OK;

}