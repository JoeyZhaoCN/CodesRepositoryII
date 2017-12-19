/**********************************************
               Editor:Joezeo			                       
          E-mail:joezeo@outlook.com                  
            Date:2017/12/19/19/22     
**********************************************/
#pragma warning(disable:4996)
#pragma warning(disable:4133)
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <assert.h>

typedef struct {

	float	coef;	// ϵ��
	int		expn;	// ָ��

}term, ElemType;

typedef struct {

	ElemType data;
	struct node *next;

}node;

typedef struct {

	node *head;

	int cnt;

}LinkList;

typedef LinkList polynomial;	// polynomial - ����ʽ

/*
**
**		����ǰ������
**
*/

polynomial * 
CreatePloyn(int);

void
DestroyPolyn(polynomial *);

void
PrintPolyn(const polynomial *);

int
PolynLength(const polynomial *);

void
AddPolyn(polynomial *, polynomial *);


/*
**
**		����������������
**
*/
int main()
{
	polynomial *p1, *p2;

	p1 = CreatePloyn(3);
	p2 = CreatePloyn(5);

	AddPolyn(p1, p2);

	PrintPolyn(p1);

	DestroyPolyn(p1);
	
	system("pause");
	return 0;
}


/*
**
**		��������
**
*/
polynomial *
CreatePloyn(int m) {

	/*
		����m���ϵ����ָ����������ʾһԪ����ʽ����������p
	*/

	if (m <= 0) {

		return NULL;

	}

	polynomial *ployn = (polynomial *)malloc(sizeof(polynomial));
	node *prenode = NULL;
	node *curnode = NULL;

	ployn->cnt = m;

	for (int i = 0; i < m; i++) {

		node *newnode = (node*)malloc(sizeof(node));

		printf("�������%d���ϵ����ָ����", i + 1);
		scanf("%f,%d", &((newnode->data).coef), 
			&((newnode->data).expn));
		newnode->next = NULL;

		if (i == 0) {

			ployn->head = newnode;

			curnode = (ployn->head);

			continue;

		}

		(curnode->next) = newnode;
		prenode = curnode;
		curnode = (curnode->next);

	}

	return ployn;

}


void
DestroyPolyn(polynomial *P) {

	/*
		����һԪ����ʽP
	*/

	assert(P != NULL);

	node *tmpnode = NULL;
	node *curnode = P->head;

	while (curnode != NULL) {

		tmpnode = curnode->next;
		free(curnode);
		curnode = tmpnode;

	}
	
	free(P);
	P = NULL;

}


void
PrintPolyn(const polynomial *P) {

	assert(P != NULL);

	node *tmp = P->head;

	printf("f(x) = ");

	while (tmp != NULL) {
		
		printf("%.2fx^%d", (tmp->data).coef, (tmp->data).expn);

		tmp = tmp->next;

		if (tmp != NULL) {

			printf(" + ");

		}

		if (tmp == NULL) {

			printf("\n");

		}
	
	}

}

int
PolynLength(const polynomial *P) {

	/*
		����һԪ����ʽ�е�����
	*/

	return P->cnt;

}

void
AddPolyn(polynomial *Pa, polynomial *Pb) {

	/*
		��ɶ���ʽ��������㣬����Pa = Pa + Pb��������Pb
	*/

	assert(Pa != NULL);
	assert(Pb != NULL);

	node *prenode = NULL;
	node *n1 = Pa->head;
	node *n2 = Pb->head;
	node *tmp = NULL;

	while (n1 && n2) {

		if ((n1->data).expn == (n2->data).expn) {

			(n1->data).coef += (n2->data).coef;

			tmp = n2;
			prenode = n1;
			n1 = n1->next;
			n2 = n2->next;
			Pb->head = n2;
			free(tmp);
			tmp = NULL;

		}
		else if ((n1->data).expn > (n2->data).expn) {

			if (prenode == NULL) {

				Pa->head = n2;

			}
			else {

				prenode->next = n2;

			}

			Pb->head = n2->next;
			n2->next = n1;
			n2 = Pb->head;

		}
		else {

			prenode = n1;
			n1 = n1->next;

		}
	}

	if (n2) {

		prenode->next = n2;

	}

	free(Pb);
	Pb = NULL;

}