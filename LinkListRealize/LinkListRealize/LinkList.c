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

typedef struct {//�������
	ElemType data;		//������
	struct Node *next;	//ָ���̽��
	struct Node *pre;	//ָ��ǰ�����
}Node,*node;

typedef struct {//��������
	node head;			//ͷָ��
	node tail;			//βָ��
	int len;			//����������Ԫ�صĸ���
}LkList,*lkList;

Status MakeNode(node, ElemType);//������pָ��e�Ľ�㣬������OK������ʧ���򷵻�ERROR
void FreeNode(node);//�ͷ�p��ָ���
Status InitList(lkList);//����һ���յ�����L
Status InsertHead(lkList, node);//�ձ����ͷ���
Status ClearList(lkList);//�����Ա�L����Ϊ�ձ����ͷ�ԭ����Ľ��ռ�
Status InsFirst(lkList, node);//��s��ָ������ͷ���֮ǰ
Status InsAfter(lkList, node);//��s��ָ������ͷ���֮��
Status DelFirst(lkList);//ɾ��ͷ��㣬�����ʱ����L�е�����Ԫ�ظ�����Ϊ0����ͷָ�����
Status Append(lkList, lkList);//���ڶ����������ӵ���һ������β���֮��
Status DelTail(lkList);//ɾ��β��㣬�����ʱ����L�е�����Ԫ�ظ�����Ϊ0����βָ��ǰ��
Status SetElem(lkList, int, ElemType);//�ı������е�i��Ԫ�ص�������
ElemType GetElem(lkList, int);//���������е�i��Ԫ�ص�������
Status EmptyList(lkList);//�ж�����L�Ƿ��ǿձ����򷵻�TRUE�����򷵻�FALSE
int ListLength(lkList);//��������L������Ԫ�ظ���
node GetPrior(lkList, int);//���ص�i��Ԫ�ص�ǰ����ַ
node GetNext(lkList, int);//���ص�i��Ԫ�صĺ�̵�ַ
Status iInsertBefore(lkList, int, node);//��s�������i��Ԫ��֮ǰ
Status iInsertAfter(lkList, int, node);//��s�������i��Ԫ��֮��
Status TraverseList(lkList);//��������

int main()
{
	LkList L;
	Node node_head;
	Node nodes[10];
	for (int i = 0; i < 10; i++) {
		MakeNode(&nodes[i],i + 1);
	}
	MakeNode(&node_head, 0);//����ͷ���
	InitList(&L);
	InsertHead(&L, &node_head);
	printf("����ͷ���:\n");
	TraverseList(&L);
	InsFirst(&L, &nodes[0]);
	printf("\nͷ���֮ǰ�����㣺\n");
	TraverseList(&L);
	DelFirst(&L);
	printf("\nɾ��ͷ��㣺\n");
	TraverseList(&L);
	for (int i = 0; i < 10; i++) {
		InsAfter(&L, &nodes[i]);
	}
	printf("\n��ͷ�������������㣺\n");
	TraverseList(&L);
	SetElem(&L, 2, 100);
	printf("\n�ı�ڶ�������������Ϊ100��\n");
	TraverseList(&L);
	printf("\n��ǰ������Ϊ��\n%d\n", ListLength(&L));	
	ClearList(&L);
	printf("\n�������\n");
	printf("\n��ǰ������Ϊ��\n%d\n", ListLength(&L));
	printf("\n��ǰ�����Ƿ�Ϊ�գ� %d", EmptyList(&L));
	getch();
	return 0;
}

Status MakeNode(node p, ElemType e) {//������pָ��e�Ľ�㣬������OK
	p->data = e;
	p->next = NULL;
	p->pre = NULL;
	return OK;
}

void FreeNode(node p) {//�ͷ�p��ָ���
	p->data = 0;
	p->next = NULL;
	p->pre = NULL;
	free(p);
}

Status InitList(lkList L) {//����һ���յ�����L
	L->head = NULL;
	L->tail = NULL;
	L->len = 0;
	return OK;
}

Status InsertHead(lkList L, node node_head) {//�ձ����ͷ���
	L->head = node_head;
	L->tail = node_head;
	L->len++;
	return OK;
}

Status ClearList(lkList L) {//�����Ա�L����Ϊ�ձ����ͷ�ԭ����Ľ��ռ�
	L->head = NULL;
	L->tail = NULL;
	L->len = 0;
	return OK;
}

Status InsFirst(lkList L, node s) {//��s��ָ������ͷ���֮ǰ
	s->next = L->head;
	s->pre = NULL;
	(L->head)->pre = s;
	L->head = s;
	L->len++;
	return OK;
}

Status InsAfter(lkList L, node s) {//��s��ָ������ͷ���֮��
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

Status DelFirst(lkList L) {//ɾ��ͷ��㣬�����ʱ����L�е�����Ԫ�ظ�����Ϊ0����ͷָ�����
	if (--(L->len) > 0) {
		L->head = (L->head)->next;
		(L->head)->pre = NULL;
		return OK;
	}
	L->head = NULL;
	L->tail = NULL;
	return OK;
}

Status Append(lkList L1, lkList L2) {//���ڶ����������ӵ���һ������β���֮��
	(L1->tail)->next = L2->head;
	(L2->head)->pre = L1->tail;
	L1->tail = L2->tail;
	L1->len += L2->len;
	return OK;
}

Status DelTail(lkList L) {//ɾ��β��㣬�����ʱ����L�е�����Ԫ�ظ�����Ϊ0����βָ��ǰ��
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

Status SetElem(lkList L, int i, ElemType e) {//�ı������е�i��Ԫ�ص�������
	if (i < 1) {
		printf("��������ȷ��Ԫ��λ��!");
		return ERROR;
	}
	if (i > L->len + 1) {
		printf("����������Ԫ��λ��Ϊ��%d", L->len);
		return ERROR;
	}
	node p = L->head;
	for (int k = 0; k < i - 1; k++) {
		p = p->next;
	}
	p->data = e;
	return OK;
}

ElemType GetElem(lkList L, int i) {//��������е�i��Ԫ�ص�������
	if (i < 1) {
		printf("��������ȷ��Ԫ��λ��!");
		return ERROR;
	}
	if (i > L->len + 1) {
		printf("����������Ԫ��λ��Ϊ��%d", L->len);
		return ERROR;
	}
	node p = L->head;
	for (int k = 0; k < i - 1; k++) {
		p = p->next;
	}
	return p->data;
}

Status EmptyList(lkList L) {//�ж�����L�Ƿ��ǿձ����򷵻�TRUE�����򷵻�FALSE
	if (L->len == 0) return TRUE;
	return FALSE;
}

int ListLength(lkList L) {//��������L������Ԫ�ظ���
	return L->len;
}

node GetPrior(lkList L, int i) {//���ص�i��Ԫ�ص�ǰ�����
	if (i < 1) {
		printf("��������ȷ��Ԫ��λ��!");
		return NULL;
	}
	if (i > L->len + 1) {
		printf("����������Ԫ��λ��Ϊ��%d", L->len);
		return NULL;
	}
	node p = L->head;
	for (int k = 0; k < i - 1; k++) {
		p = p->next;
	}
	return p->pre;
}

node GetNext(lkList L, int i) {//���ص�i��Ԫ�صĺ�̽��
	if (i < 1) {
		printf("��������ȷ��Ԫ��λ��!");
		return NULL;
	}
	if (i > L->len + 1) {
		printf("����������Ԫ��λ��Ϊ��%d", L->len);
		return NULL;
	}
	node p = L->head;
	for (int k = 0; k < i - 1; k++) {
		p = p->next;
	}
	if (p->next == NULL) {
		printf("�˽������β��㣡û�к�̽��");
		return NULL;
	}
	return p->next;
}

Status iInsertBefore(lkList L, int i, node s) {//��s�������i��Ԫ��֮ǰ
	if (i < 1) {
		printf("��������ȷ��Ԫ��λ��!");
		return ERROR;
	}
	if (i > L->len + 1) {
		printf("����������Ԫ��λ��Ϊ��%d", L->len);
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

Status iInsertAfter(lkList L, int i, node s) {//��s�������i��Ԫ��֮��
	if (i < 1) {
		printf("��������ȷ��Ԫ��λ��!");
		return ERROR;
	}
	if (i > L->len + 1) {
		printf("����������Ԫ��λ��Ϊ��%d", L->len);
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

Status TraverseList(lkList L) {//��������
	node p = L->head;
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	return OK;
}