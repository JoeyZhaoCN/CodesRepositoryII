#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>

typedef struct {
	int x;
	int y;
}cursor;
/******************��ʼ������**********************/
void initGame(cursor*,int*,int*,int*);	

/******************��Ϸ��ʼ����********************/
void gameBegin(cursor*,int*,int*);	

/******************��Ϸ���й���********************/
void gameProcess(cursor*,cursor*,int*,int*,int*);	
void drawCursor(cursor*, COLORREF);						//�����
void drawTime(int);										//��ʱ��
void drawScore(int);									//������
void getSameColorBalls(cursor*,cursor*,COLORREF,int*);	//�������λ����ɫ��ͬ��С�򣬽���x��yֵ��������ballsArr��
int isValid(cursor*, cursor*, COLORREF, int*);			//�ݹ麯��getSamColorBalls�Ľ�������
void ballsFall(cursor*, int*);							//����С����Ϸ���С������

/******************��Ϸ�������ͷ���Դ***************/
int gameEnd(int*);		
void closeGame();

COLORREF colorArr[6] = { RGB(200,0,0),RGB(0,200,0),RGB(0,0,200),
							RGB(200,200,0),RGB(200,0,200),RGB(0,200,200) };
cursor *cur = (cursor *)malloc(sizeof(cursor)); 			//��ǰ����λ��
cursor *ballsArr = (cursor *)malloc(180 * sizeof(cursor));	//ͬɫС������
int sec, score,ball_num;
int main() {
	while (1) {
		initGame(cur,&sec,&score,&ball_num);
		gameBegin(cur,&sec,&score);
		gameProcess(cur,ballsArr,&sec,&score,&ball_num);
		if (!gameEnd(&score))
			break;
	}
	closeGame();
	return 0;
}

/************************************************************************/
/*initiate game                                                                     */
/************************************************************************/
void initGame(cursor *cur,int *sec,int *score,int *ball_num) {
	initgraph(1000, 700);
	cur->x = 480;
	cur->y = 350;
	*sec = 30;
	*score = 0;
	*ball_num = 0;
}

/************************************************************************/
/* game begin                                                                     */
/************************************************************************/
void gameBegin(cursor *cur,int *sec,int *score) {
	//���Ʊ߿�
	setlinecolor(RGB(50, 50, 50));
	setlinestyle(PS_SOLID, 10);
	rectangle(255, 45, 745, 655);
	//����С��	
	setlinestyle(PS_SOLID, 1);
	srand((unsigned)time(NULL));
	for (int x = 280; x < 740; x += 40) {
		for (int y = 70; y < 650; y += 40) {
			COLORREF cl;
			cl = colorArr[rand() % 6];
			setlinecolor(cl);
			setfillcolor(cl);
			fillcircle(x, y, 19);
		}
	}
	//���ƹ��
	drawCursor(cur, RGB(255, 255, 255));
	//����ʱ��
	drawTime(*sec);
	//���Ʒ���
	drawScore(*score);
}

/************************************************************************/
/* game process                                                                     */
/************************************************************************/
void gameProcess(cursor *cur,cursor *ballsArr,int *sec,int *score,int *ball_num) {
	int time;
	for (time = 0; time < 1260000; time++) {
		int ch;
		if (_kbhit()) {
			ch = _getch();
			if (ch == 0x48 && cur->y - 40 >= 70) {
				drawCursor(cur, RGB(0, 0, 0));
				cur->y -= 40;
				drawCursor(cur, RGB(255, 255, 255));
			}
			if (ch == 0x50 && cur->y + 40 <= 650) {
				drawCursor(cur, RGB(0, 0, 0));
				cur->y += 40;
				drawCursor(cur, RGB(255, 255, 255));
			}
			if (ch == 0x4b && cur->x - 40 >= 280) {
				drawCursor(cur, RGB(0, 0, 0));
				cur->x -= 40;
				drawCursor(cur, RGB(255, 255, 255));
			}
			if (ch == 0x4d && cur->x + 40 <= 740) {
				drawCursor(cur, RGB(0, 0, 0));
				cur->x += 40;
				drawCursor(cur, RGB(255, 255, 255));
			}
			if (ch == 0x0d) {
				getSameColorBalls(cur, ballsArr, getpixel(cur->x, cur->y), ball_num);
				if (*ball_num > 2) {
					for (int i = 0; i < *ball_num; i++) {
						setlinecolor(RGB(0, 0, 0));
						setfillcolor(RGB(0, 0, 0));
						fillcircle((ballsArr + i)->x, (ballsArr + i)->y, 19);
					}
					Sleep(10);
					ballsFall(ballsArr, ball_num);
					*score += *ball_num;
					drawScore(*score);
					time -= 42000;
					*sec += 1;
					drawTime(*sec);
				}
				*ball_num = 0;
			}
		}
		if (time % 42000 == 0) {
			(*sec)--;
			drawTime(*sec);
		}		
	}	
}
void drawCursor(cursor *cur, COLORREF color){
	setlinecolor(color);
	rectangle(cur->x - 20, cur->y - 20, cur->x + 20, cur->y + 20);
}
void drawTime(int sec) {
	char str[30];
	settextcolor(RGB(255, 255, 0));
	settextstyle(25, 0, _T("����"));
	sprintf_s(str, "ʣ��ʱ�䣺 %d s", sec);
	outtextxy(30, 50, str);
}
void drawScore(int score) {
	char str[30];
	settextcolor(RGB(255, 0, 0));
	settextstyle(25, 0, _T("����"));
	sprintf_s(str, "������%d", score);
	outtextxy(30, 600, str);
}
void getSameColorBalls(cursor *cur,cursor *ballsArr,COLORREF col,int *ball_num) {
	(ballsArr + *ball_num)->x = cur->x;
	(ballsArr + *ball_num)->y = cur->y;
	(*ball_num)++;

	cursor tmp;
	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0:
			tmp.x = cur->x; tmp.y = cur->y - 40;
			break;
		case 1:
			tmp.x = cur->x; tmp.y = cur->y + 40;
			break;
		case 2:
			tmp.x = cur->x - 40; tmp.y = cur->y;
			break;
		case 3:
			tmp.x = cur->x + 40; tmp.y = cur->y;
			break;
		}
		if (isValid(&tmp,ballsArr,col,ball_num)) {
			getSameColorBalls(&tmp, ballsArr,col, ball_num);
		}
	}
}
int isValid(cursor *cur, cursor *ballsArr, COLORREF col, int *ball_num) {
	if (getpixel(cur->x, cur->y) != col)
		return 0;
	else
	{
		for (int i = 0; i < *ball_num; i++) {
			if (cur->x == (ballsArr + i)->x && cur->y == (ballsArr + i)->y)
				return 0;
		}
		return 1;
	}
}
void ballsFall(cursor *ballsArr, int *ball_num) {
	int tmp_y;
	srand((unsigned)time(NULL));
	for (int i = 0; i < *ball_num; i++) {	
		tmp_y = (ballsArr + i)->y;
		if (getpixel((ballsArr + i)->x, (ballsArr + i)->y) == RGB(0, 0, 0)) {
			while (tmp_y > 70) {
				setlinecolor(getpixel((ballsArr + i)->x, tmp_y - 40));
				setfillcolor(getpixel((ballsArr + i)->x, tmp_y - 40));
				fillcircle((ballsArr + i)->x, tmp_y, 19);
				tmp_y -= 40;
			}
			COLORREF cl = colorArr[rand() % 6];
			setlinecolor(cl);
			setfillcolor(cl);
			fillcircle((ballsArr + i)->x, 70, 19);
		}
		if (getpixel((ballsArr + i)->x, (ballsArr + i)->y) == RGB(0, 0, 0)) {
			i--;
		}
	}
}

/************************************************************************/
/* game end                                                                     */
/************************************************************************/
int gameEnd(int *score) {
	char str[50];
	int ch;
	sprintf_s(str,"��Ϸ��������ķ�����%3d",*score);
	cleardevice();
	settextstyle(30, 0, _T("����"));
	settextcolor(0x5555FF);
	outtextxy(325, 300, str);
	sprintf_s(str, "R/START         Q/QUIET");
	outtextxy(325, 350, str);
	while (ch = _getch()) {
		if (ch == 'r' || ch == 'R')
			return 1;
		if (ch == 'q' || ch == 'Q')
			return 0;
	}
}
void closeGame() {
	free(cur);
	free(ballsArr);
	closegraph();
}