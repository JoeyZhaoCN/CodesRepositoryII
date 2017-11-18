/**********************************************
               Editor:Joezeo			                       
          E-mail:joezeo@outlook.com                  
            Date:2017/11/18/10/42     
**********************************************/
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>

typedef struct snakenode{
	int x, y;						//�������x��y����
	int direction;					//��ͷ�����˶�����
	struct snakenode *next,*pre;	//ָ���������ǰ������̽��
	COLORREF snaCL;
}snakenode;

typedef struct {
	int x, y;						//ʳ���x��y����
	int flag;						//�ж�ʳ���Ƿ񱻳Ե�,����Ϊ1��û����Ϊ0
}food;

/*
	��ʼ����Ϸ���������ڣ���ʼ������
*/
void initgame(snakenode*,snakenode*,food *fd,int*);
void drawelcome();			//���Ƴ���ӭ����
void specification();		//��Ϸ˵��
void drawranklist(int*);	//�������а�
void gameUI();				//��Ϸ����

/*
	��Ϸ���й���
*/
void gameproc(snakenode*,snakenode*,food*,int*);
void drawsnake(snakenode*,snakenode*);				//����
void drawfood(snakenode*, food*);					//��ʳ��
void controlsnake(snakenode*);						//������
void movesnake(snakenode*,snakenode*,snakenode*);	//�ƶ���
void createnode(snakenode**,snakenode*);			//�ٵ�ʳ�������һ���µ�������
int judegame(snakenode*);							//�ж��Ƿ�ײǽ����ײ���Լ�����
void drawscore(int*);								//���Ʒ���

/* 
	��Ϸ�������棺�ͷ���Դ������ѭ��(���¿�ʼ��ر���Ϸ)                        
*/
int gameover(int*,int*);
void updaterank(int*,int*);	//�������а�

int main()
{
	snakenode node_H, node_T;
	snakenode *head = &node_H, *tail = &node_T;
	food fd;
	int ranklist[5] = { 0,0,0,0,0 }, score = 0;
	while (1) {
		initgame(head, tail, &fd,ranklist);
		gameproc(head, tail, &fd,&score);
		if (gameover(ranklist,&score))
			break;
	}
	return 0;
}

/************************************************************************/
/* ��ʼ����Ϸ���������ڣ���ʼ������                                          */
/************************************************************************/
void initgame(snakenode *head,snakenode *tail,food *fd,int *ranklist) {
	initgraph(1200, 800);
	head->direction = 0x4d;
	head->x = 610;
	head->y = 360;
	head->next = tail;
	head->pre = NULL;
	head->snaCL = 0x0055AA;
	tail->direction = 0;
	tail->x = 590;
	tail->y = 360;
	tail->next = NULL;
	tail->pre = head;
	tail->snaCL = 0x00AA00;
	fd->flag = 0;
	srand((unsigned)time(NULL));
	int X = 0, Y = 0;
	while (1) {
		int flag = 1;
		snakenode *p = head;
		X = 310 + rand() % 30 * 20;
		Y = 60 + rand() % 30 * 20;
		while (p != NULL) {
			if (X == p->x && Y == p->y) flag = 0;
			p = p->next;
		}
		if (flag && X % 10 == 0 && Y % 10 == 0) break;
	}
	fd->x = X;
	fd->y = Y;
	drawelcome();
	while (1) {
		int ch = _getch();
		if (ch == 'e' || ch == 'E') {
			specification();	
		}
		if (ch == 's' || ch == 'S') {
			gameUI();
			break;
		}
		if (ch == 'p' || ch == 'P') {
			drawranklist(ranklist);
		}
	}
}
void drawelcome() {//���Ƴ���ӭ����
	setlinecolor(RGB(250, 250, 250)); 
	setlinestyle(PS_SOLID,5);
	rectangle(450, 235, 795, 295);
	rectangle(520, 395, 725, 435);
	rectangle(520, 470, 725, 510);
	rectangle(520, 545, 725, 585);
	settextstyle(30, 0, _T("����"));
	settextcolor(RGB(200, 75, 75));
	outtextxy(465, 250, "��� ~ ��ӭ����̰����");
	outtextxy(525, 400, "  ��ʼ    S  ");
	outtextxy(525, 475, "  ˵��    E  ");
	outtextxy(525, 550, " ���а�   P  ");
	settextstyle(20, 0, _T("����"));
	outtextxy(700, 310, "���ߣ�Joezeo");
	settextcolor(RGB(250, 250, 250));
	settextstyle(18, 0, _T("����"));
	outtextxy(500, 750, "������ʾ�����л����������뷨");
}
void specification() {//��Ϸ˵��
	cleardevice();
	settextstyle(50, 0, _T("����"));
	settextcolor(RGB(255, 255, 255));
	outtextxy(560, 100, "˵����");
	settextstyle(25, 0, _T("����"));
	outtextxy(280, 300, "�������ҿ������ƶ�����Ҫײ���Լ�����ǽ�ڣ�����Ե�ʳ���~");
	rectangle(515, 395, 720, 435);
	settextstyle(30, 0, _T("����"));
	settextcolor(RGB(200, 75, 75));
	outtextxy(520, 400, "  ����    B  ");
	while (1) {
		int ch = _getch();
		if (ch == 'b' || ch == 'B') {
			cleardevice();
			drawelcome();
			break;
		}
	}
}
void gameUI() {//��Ϸ����
	cleardevice();
	setlinecolor(RGB(150, 150, 150));
	setlinestyle(PS_SOLID, 10);
	rectangle(295, 45, 905, 655);
}
void drawranklist(int *ranklist) {//���Ƴ����а�
	int x = 530, y = 140;
	char str[25];
	cleardevice();
	settextcolor(RGB(255, 255, 255));
	settextstyle(50, 0, _T("����"));
	outtextxy(540, 100, "���а�");
	rectangle(515, 545, 720, 585);
	settextstyle(30, 0, _T("����"));
	settextcolor(RGB(200, 75, 75));
	outtextxy(520, 550, "  ����    B  ");
	settextstyle(25, 0, _T("����"));
	for (int i = 0; i < 5; i++) {
		y += 60;
		sprintf_s(str, "%d        %3d", i + 1, ranklist[i]);
		outtextxy(x, y, str);
	}
	while (1) {
		int ch = _getch();
		if (ch == 'b' || ch == 'B') {
			cleardevice();
			drawelcome();
			break;
		}
	}
}

/************************************************************************/
/* ��Ϸ���й���                                                            */
/************************************************************************/
void gameproc(snakenode *head,snakenode *tail,food *fd,int *score) {
	snakenode *oritail = (snakenode *)malloc(sizeof(snakenode));

	while (1) {
		if (judegame(head))
			break;
		drawscore(score);
		drawsnake(head,oritail);
		drawfood(head,fd);	
		controlsnake(head);
		movesnake(head, tail, oritail);	
		if (head->x == fd->x && head->y == fd->y) {
			fd->flag = 1;
			snakenode *newnode = (snakenode *)malloc(sizeof(snakenode));
			createnode(&head, newnode);
			*score += 10;
		}	
		Sleep(500);
	}
	free(oritail);
}
void drawsnake(snakenode *head,snakenode *oritail) {
	snakenode *p = head;
	setfillcolor(oritail->snaCL);
	setlinecolor(oritail->snaCL);
	fillrectangle(oritail->x - 5, oritail->y - 5, oritail->x + 5, oritail->y + 5);
	while (p != NULL) {
		setlinecolor(p->snaCL);
		setfillcolor(p->snaCL);
		fillrectangle(p->x - 5, p->y - 5, p->x + 5, p->y + 5);
		p = p->next;
	}
}
void drawfood(snakenode *head, food *fd) {
	if (fd->flag) {
		srand((unsigned)time(NULL));
		int X = 0, Y = 0;
		while (1) {
			int flag = 1;
			snakenode *p = head;
			X = 310 + rand() % 30 * 20;
			Y = 60 + rand() % 30 * 20;
			while (p != NULL) {
				if (X == p->x && Y == p->y) flag = 0;
				p = p->next;
			}
			if (flag && X % 10 == 0 && Y % 10 == 0) break;
		}
		fd->x = X;
		fd->y = Y;
	}
	setlinecolor(0x0000AA);
	setfillcolor(0x0000AA);
	fillcircle(fd->x, fd->y, 5);
	fd->flag = 0;
}
void controlsnake(snakenode *head) {//������
	int dirc;
	if (_kbhit()) {
		dirc = _getch();	
		head->direction = dirc;	
	}
}
void movesnake(snakenode *head, snakenode *tail,snakenode *oritail) {
	snakenode *p = tail;
	oritail->direction = 0;
	oritail->next = NULL;
	oritail->pre = NULL;
	oritail->snaCL = RGB(0,0,0);
	oritail->x = tail->x;
	oritail->y = tail->y;
	while (p != head) {
		p->x = (p->pre)->x;
		p->y = (p->pre)->y;
		p = p->pre;
	}
	switch (head->direction) {
	case 0x48:
		head->y -= 20;
		break;
	case 0x50:
		head->y += 20;
		break;
	case 0x4b:
		head->x -= 20;
		break;
	case 0x4d:
		head->x += 20;
		break;
		}
}
void createnode(snakenode **head,snakenode *newnode) {//�ٵ�ʳ�������һ���µ�������
	newnode->direction = (*head)->direction;
	newnode->next = *head;
	newnode->pre = NULL;
	newnode->snaCL = (*head)->snaCL;
	switch ((*head)->direction)
	{
	case 0x48:
		newnode->y = (*head)->y - 20;
		newnode->x = (*head)->x;
		break;
	case 0x50:
		newnode->y = (*head)->y + 20;
		newnode->x = (*head)->x;
		break;
	case 0x4b:
		newnode->x = (*head)->x - 20;
		newnode->y = (*head)->y;
		break;
	case 0x4d:
		newnode->x = (*head)->x + 20;
		newnode->y = (*head)->y;
		break;
	}
	(*head)->snaCL = 0x00AA00;
	(*head)->pre = newnode;
	*head = newnode;
}
int judegame(snakenode *head) {
	snakenode *p = head->next;
	snakenode *tmp_H = head;
	if (head->x < 310 || head->x >890 || head->y < 60 || head->y > 640)
		return 1;
	
	return 0;
}
void drawscore(int *score) {
	char str[25];
	settextcolor(RGB(255, 255, 255));
	settextstyle(25, 0, _T("����"));
	sprintf_s(str, "������%3d", *score);
	outtextxy(60, 60, str);
}

/************************************************************************/
/* ��Ϸ�������棺�ͷ���Դ������ѭ��(���¿�ʼ��ر���Ϸ)                        */
/************************************************************************/
int gameover(int *ranklist,int *score) {
	settextcolor(RGB(255, 255, 255));
	settextstyle(25, 0, _T("����"));
	outtextxy(550,280,"��Ϸ����~");
	outtextxy(450, 440, "���¿�ʼ/R    �˳���Ϸ/E");
	updaterank(ranklist, score);
	while (1) {
		int ch = _getch();
		if (ch == 'r' || ch == 'R')
			return 0;
		if (ch == 'e' || ch == 'E')
			return 1;
	}
}
void updaterank(int *ranklist, int *score) {
	if (*(ranklist + 4) < *score)
		*(ranklist + 4) = *score;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5 - i - 1; j++) {
			if (*(ranklist + j) < *(ranklist + j + 1)) {
				int tmp;
				tmp = *(ranklist + j);
				*(ranklist + j) = *(ranklist + j + 1);
				*(ranklist + j + 1) = tmp;
			}
		}
	}
	*score = 0;
}
