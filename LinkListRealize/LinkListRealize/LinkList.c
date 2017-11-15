/**********************************************
               Editor:Joezeo			                       
          E-mail:joezeo@outlook.com                  
            Date:2017/11/15/19/34     
**********************************************/
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int ElemType;
typedef int Status;

typedef struct {//结点类型
	ElemType data;		//数据域
	struct Node *next;	//指向后继结点
	struct Node *pre;	//指向前驱结点
}Node,*node;

typedef struct {//链表类型
	node head;			//头指针
	node tail;			//尾指针
	int len;			//链表中数据元素的个数
}LkList,*lkList;

Status MakeNode(node, ElemType);//分配由p指向e的结点，并返回OK；分配失败则返回ERROR
void FreeNode(node);//释放p所指结点
Status InitList(lkList);//构造一个空的链表L
Status InsertHead(lkList, node);//空表插入头结点
Status ClearList(lkList);//将线性表L重置为空表，并释放原链表的结点空间
Status InsFirst(lkList, node);//将s所指结点插入头结点之前
Status InsAfter(lkList, node);//将s所指结点插入头结点之后
Status DelFirst(lkList);//删除头结点，如果此时链表L中的数据元素个数不为0，则头指针后移
Status Append(lkList, lkList);//将第二个链表链接到第一个结点的尾结点之后
Status DelTail(lkList);//删除尾结点，如果此时链表L中的数据元素个数不为0，则尾指针前移
Status SetElem(lkList, int, ElemType);//改变链表中第i个元素的数据域
ElemType GetElem(lkList, int);//返回链表中第i个元素的数据域
Status EmptyList(lkList);//判断链表L是否是空表，是则返回TRUE，否则返回FALSE
int ListLength(lkList);//返回链表L的数据元素个数
node GetPrior(lkList, int);//返回第i个元素的前驱地址
node GetNext(lkList, int);//返回第i个元素的后继地址
Status iInsertBefore(lkList, int, node);//将s结点插入第i个元素之前
Status iInsertAfter(lkList, int, node);//将s结点插入第i个元素之后
Status TraverseList(lkList);//遍历链表

int main()
{
	LkList L;
	Node node_head;
	Node nodes[10];
	for (int i = 0; i < 10; i++) {
		MakeNode(&nodes[i],i + 1);
	}
	MakeNode(&node_head, 0);//创建头结点
	InitList(&L);
	InsertHead(&L, &node_head);
	printf("插入头结点:\n");
	TraverseList(&L);
	InsFirst(&L, &nodes[0]);
	printf("\n头结点之前插入结点：\n");
	TraverseList(&L);
	DelFirst(&L);
	printf("\n删除头结点：\n");
	TraverseList(&L);
	for (int i = 0; i < 10; i++) {
		InsAfter(&L, &nodes[i]);
	}
	printf("\n在头结点后连续插入结点：\n");
	TraverseList(&L);
	SetElem(&L, 2, 100);
	printf("\n改变第二个结点的数据域为100：\n");
	TraverseList(&L);
	printf("\n当前链表长度为：\n%d\n", ListLength(&L));	
	ClearList(&L);
	printf("\n清空链表！\n");
	printf("\n当前链表长度为：\n%d\n", ListLength(&L));
	printf("\n当前链表是否为空？ %d", EmptyList(&L));
	getch();
	return 0;
}

Status MakeNode(node p, ElemType e) {//分配由p指向e的结点，并返回OK
	p->data = e;
	p->next = NULL;
	p->pre = NULL;
	return OK;
}

void FreeNode(node p) {//释放p所指结点
	p->data = 0;
	p->next = NULL;
	p->pre = NULL;
	free(p);
}

Status InitList(lkList L) {//构造一个空的链表L
	L->head = NULL;
	L->tail = NULL;
	L->len = 0;
	return OK;
}

Status InsertHead(lkList L, node node_head) {//空表插入头结点
	L->head = node_head;
	L->tail = node_head;
	L->len++;
	return OK;
}

Status ClearList(lkList L) {//将线性表L重置为空表，并释放原链表的结点空间
	L->head = NULL;
	L->tail = NULL;
	L->len = 0;
	return OK;
}

Status InsFirst(lkList L, node s) {//将s所指结点插入头结点之前
	s->next = L->head;
	s->pre = NULL;
	(L->head)->pre = s;
	L->head = s;
	L->len++;
	return OK;
}

Status InsAfter(lkList L, node s) {//将s所指结点插入头结点之后
	L->len++;
	s->pre = L->head;
	s->next = (L->head)->next;
	(L->head)->next = s;
	if (s->next == NULL) {
		L->tail = s;
		return OK;
	}
	return OK;
}

Status DelFirst(lkList L) {//删除头结点，如果此时链表L中的数据元素个数不为0，则头指针后移
	if (--(L->len) > 0) {
		L->head = (L->head)->next;
		(L->head)->pre = NULL;
		return OK;
	}
	L->head = NULL;
	L->tail = NULL;
	return OK;
}

Status Append(lkList L1, lkList L2) {//将第二个链表链接到第一个结点的尾结点之后
	(L1->tail)->next = L2->head;
	(L2->head)->pre = L1->tail;
	L1->tail = L2->tail;
	L1->len += L2->len;
	return OK;
}

Status DelTail(lkList L) {//删除尾结点，如果此时链表L中的数据元素个数不为0，则尾指针前移
	if (--(L->len) > 0) {
		L->tail = (L->tail)->pre;
		(L->tail)->next = NULL;
		return OK;
	}
	L->head = NULL;
	L->tail = NULL;
	L->len = 0;
	return OK;
}

Status SetElem(lkList L, int i, ElemType e) {//改变链表中第i个元素的数据域
	if (i < 1) {
		printf("请输入正确的元素位数!");
		return ERROR;
	}
	if (i > L->len + 1) {
		printf("链表中最大的元素位数为：%d", L->len);
		return ERROR;
	}
	node p = L->head;
	for (int k = 0; k < i - 1; k++) {
		p = p->next;
	}
	p->data = e;
	return OK;
}

ElemType GetElem(lkList L, int i) {//获得链表中第i个元素的数据域
	if (i < 1) {
		printf("请输入正确的元素位数!");
		return ERROR;
	}
	if (i > L->len + 1) {
		printf("链表中最大的元素位数为：%d", L->len);
		return ERROR;
	}
	node p = L->head;
	for (int k = 0; k < i - 1; k++) {
		p = p->next;
	}
	return p->data;
}

Status EmptyList(lkList L) {//判断链表L是否是空表，是则返回TRUE，否则返回FALSE
	if (L->len == 0) return TRUE;
	return FALSE;
}

int ListLength(lkList L) {//返回链表L的数据元素个数
	return L->len;
}

node GetPrior(lkList L, int i) {//返回第i个元素的前驱结点
	if (i < 1) {
		printf("请输入正确的元素位数!");
		return NULL;
	}
	if (i > L->len + 1) {
		printf("链表中最大的元素位数为：%d", L->len);
		return NULL;
	}
	node p = L->head;
	for (int k = 0; k < i - 1; k++) {
		p = p->next;
	}
	return p->pre;
}

node GetNext(lkList L, int i) {//返回第i个元素的后继结点
	if (i < 1) {
		printf("请输入正确的元素位数!");
		return NULL;
	}
	if (i > L->len + 1) {
		printf("链表中最大的元素位数为：%d", L->len);
		return NULL;
	}
	node p = L->head;
	for (int k = 0; k < i - 1; k++) {
		p = p->next;
	}
	if (p->next == NULL) {
		printf("此结点已是尾结点！没有后继结点");
		return NULL;
	}
	return p->next;
}

Status iInsertBefore(lkList L, int i, node s) {//将s结点插入第i个元素之前
	if (i < 1) {
		printf("请输入正确的元素位数!");
		return ERROR;
	}
	if (i > L->len + 1) {
		printf("链表中最大的元素位数为：%d", L->len);
		return ERROR;
	}
	node p = L->head;
	for (int k = 0; k < i - 1; k++) {
		p = p->next;
	}
	node tmp = p->pre;
	if (i != 1) {
		tmp->next = s;
		s->pre = p->pre;
		s->next = p;
		p->pre = s;
		return OK;
	}
	s->pre = NULL;
	s->next = p;
	p->pre = s;
	L->head = s;
	L->len++;
	return OK;
}

Status iInsertAfter(lkList L, int i, node s) {//将s结点插入第i个元素之后
	if (i < 1) {
		printf("请输入正确的元素位数!");
		return ERROR;
	}
	if (i > L->len + 1) {
		printf("链表中最大的元素位数为：%d", L->len);
		return ERROR;
	}
	node p = L->head;
	for (int k = 0; k < i - 1; k++) {
		p = p->next;
	}
	if (p == L->tail) {
		p->next = s;
		s->pre = p;
		s->next = NULL;
		L->tail = s;
		return OK;
	}
	node tmp = p->next;
	s->next = p->next;
	s->pre = p;
	p->next = s;
	tmp->pre = s;
	L->len++;
	return OK;
}

Status TraverseList(lkList L) {//遍历链表
	node p = L->head;
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	return OK;
}