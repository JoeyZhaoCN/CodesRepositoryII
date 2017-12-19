/**********************************************
               Editor:Joezeo			                       
          E-mail:joezeo@outlook.com                  
            Date:2017/12/19/20/53     
**********************************************/
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define STACKINITSIZE	100	// 储存空间初始分配量
#define STACKINCREMENT	100 // 储存空间分配增量

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define OVERFLOW -2

typedef int ElemType;
typedef int Status;

typedef struct {

	ElemType *base;	// 栈底指针
	ElemType *top;	// 栈顶指针
	int	stacksize;	// 栈的容量
	int cnt;		// 栈当前元素个数

}SqStack;


/*
**			函数前向声明
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
**			主函数，程序入口
*/
int main()
{
	SqStack *sqs = InitStack();
	ElemType e;

	for (int i = 0; i < 110; i++) {

		Push(sqs, i);

	}

	printf("目前栈长度：%d\n", StackLength(sqs));
	printf("遍历栈：\n");
	StackTraverse(sqs);

	Pop(sqs, &e);
	printf("栈顶元素出栈：%d\n", e);
	printf("目前栈长度：%d\n", StackLength(sqs));

	DestroyStack(sqs);
	
	system("pause");
	return 0;
}

/*
**			函数定义
*/
SqStack *
InitStack() {

	/*
		构造一个空栈
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
		销毁栈，释放资源
	*/

	assert(sqs != NULL);

	free(sqs->base);
	sqs->base = NULL;
	sqs->top = NULL;

	free(sqs);
	sqs = NULL;

	printf("栈已成功销毁\n");

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
		若栈为空栈，返回TRUE，否则返回FALSE
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
		返回栈元素的个数，即栈的长度
	*/

	assert(sqs != NULL);

	return sqs->cnt;

}

Status
GetTop(SqStack *sqs, ElemType *e) {

	/*
		若栈不空，用e返回栈顶元素，并返回OK；否则返回ERROR
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
		增加栈的容量
	*/

	assert(sqs != NULL);

	ElemType *add = (ElemType *)realloc(sqs->base,
		(sqs->stacksize + STACKINCREMENT) * sizeof(ElemType));

	if (!add) exit(OVERFLOW);

	sqs->base = add;
	sqs->stacksize += STACKINCREMENT;

	printf("栈容量自动扩充\n");

	return OK;

}

Status
Push(SqStack *sqs, ElemType e) {

	/*
		插入元素e为新的栈顶元素
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
		若栈不空，则删除栈顶元素，用e返回其值
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
		从栈底到栈顶依次遍历栈
	*/

	assert(sqs != NULL);

	ElemType *tmp = sqs->base;

	for (; tmp != (sqs->top); tmp++) {

		printf("%d\t", *tmp);

	}

	return OK;

}