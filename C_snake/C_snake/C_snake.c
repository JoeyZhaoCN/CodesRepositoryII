/*****************************
*Editor:Joezeo
*E-mail:joeyzhaocn@foxmail.com
*Date:2017/11/3/16/04
*****************************/
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

HANDLE hout;
typedef struct {
	char bodylook;		//蛇身样式
	int x;			//蛇身结点的x坐标
	int y;			//蛇身结点的yzuob
	int motionNum;		//蛇身结点的当前运动方向
	struct SnakeBody *next;	//指向下一蛇身结点
	struct SnakeBody *pre;	//指向前驱结点
}SnakeBody;

typedef struct {
	int x;	//食物的x坐标
	int y;	//食物的y坐标
}Food;

typedef struct {
	int score;
	char *name;
}RankList;

void initGame(SnakeBody* snake_H, SnakeBody* snake_T, SnakeBody** snakeHead);//初始化各个变量

/*
gameBegin()：包括准备界面prepareUI()函数，和设置光标不可见invisibleCursor()函数，设置游戏界面gameUI()函数，
			 初始化蛇intialSnake(snakeBody snakeHead)函数，初始化食物initialFood(snakeBody snakeHead)
*/
void gameBegin(SnakeBody* snakeHead,Food* food,int *score,RankList *rankList);	//父函数
void prepareUI();								//准备界面
void gameUI(int *score,RankList *rankList);					//游戏界面
void invisibleCursor();								//设置光标不可见
void initialSnake(SnakeBody* snakeHead);					//初始化蛇，在屏幕上显示
void initialFood(SnakeBody* snakeHead,Food* food);				//初始化食物，在屏幕上显示

/*
gameProcess()：
*/
int gameProcess(SnakeBody** snakeHead,Food* food,int *score,RankList *rankList);//父函数
void createSnakeBody(SnakeBody** snakeHead,SnakeBody* newBody);			//吃到食物时创建一个新的蛇身体
void createFood(SnakeBody* snakeHead,Food* food);				//吃到食物后创建一个新的食物
void moveSnake(SnakeBody* snakeHead);						//按每个身体结点的运动方向进行相应的移动
void showSnake(SnakeBody* bodyHead,Food* food,int *score,RankList *rankList);	//在屏幕上打印出蛇
int judgeGame(SnakeBody* snakeHead);						//判断蛇是否撞到墙或者撞到自身，如果是返回1，否返回0
void recordScore(int *score);							//记录分数

/*
gameEnd():
*/
void gameEnd(int *score,RankList *rankList);		//父函数
void updateRanking(RankList *rankList,int *score);	//游戏结束更新排行榜
void endUI(int *score);					//游戏结束界面

int main(void)
{
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	RankList *rankList = (RankList*)malloc(5 * sizeof(RankList));
	for (int i = 0; i < 5; i++) {
		(rankList + i)->score = 0;
		(rankList + i)->name = "XXX";
	}
	/*
		这个游戏包括两个循环：
		一个是控制游戏开始、进行、结束的大循环；
		另一个是控制游戏进行过程的循环。
	*/
	while (1) {		
		SnakeBody snake_H,snake_T;
		SnakeBody* snakeHead = (SnakeBody*)malloc(sizeof(SnakeBody));
		Food* food = (Food*)malloc(sizeof(Food));
		int score = 0;		
		initGame(&snake_H, &snake_T, &snakeHead);
		gameBegin(snakeHead,food,&score,rankList);
		while (1) {
			if (gameProcess(&snakeHead, food, &score,rankList)) {
				gameEnd(&score,rankList);
				break;
			}
			Sleep(500);
		}
	}
	return 0;
}
/*****************************Initiate************************************/
void initGame(SnakeBody* snake_H, SnakeBody* snake_T, SnakeBody** snakeHead) {//初始化各个变量
	snake_H->bodylook = '@';
	snake_H->motionNum = 0x4d;
	snake_H->x = 20;
	snake_H->y = 10;
	snake_H->next = snake_T;
	snake_H->pre = NULL;
	snake_T->bodylook = 'X';
	snake_T->motionNum = 0x4d;
	snake_T->x = 19;
	snake_T->y = 10;
	snake_T->next = NULL;
	snake_T->pre = snake_H;
	*snakeHead = snake_H;
}

/*
	游戏范围：
	左上顶点（1，1）
	右下顶点（40，21）
*/

/*****************************game begin***********************************/
void gameBegin(SnakeBody* snakeHead,Food* food,int *score,RankList *rankList) {
	invisibleCursor();
	prepareUI();
	gameUI(score,rankList);
	initialSnake(snakeHead);
	initialFood(snakeHead,food);
}
void prepareUI() {//绘制欢迎界面
	COORD coord;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	char ch;
	GetConsoleScreenBufferInfo(hout, &csbi);
	coord.X = csbi.dwCursorPosition.X;
	coord.Y = csbi.dwCursorPosition.Y;
	system("cls");
	coord.X = 29;
	coord.Y = 4;
	SetConsoleCursorPosition(hout, coord);
	printf("=-·Hungry Snake·-=");
	coord.X = 31;
	coord.Y++;
	SetConsoleCursorPosition(hout, coord);
	printf("write by: Joezeo");
	coord.X = 24;
	coord.Y = 8;
	SetConsoleCursorPosition(hout, coord);
	printf("Greeting！wellcom to the game！");
	coord.X = 24;
	coord.Y += 3;
	SetConsoleCursorPosition(hout, coord);
	printf("Push the 'S' to start the game!");
	coord.X = 16;
	coord.Y = 17;
	SetConsoleCursorPosition(hout, coord);
	for(int i = 0;i < 43;i++)
		printf("X");
	for (int i = 0; i < 3; i++) {
		coord.Y++;
		coord.X = 58;
		SetConsoleCursorPosition(hout, coord);
		printf("X");
	}
	printf("XXXXXXXXX");
	coord.X = 16;
	coord.Y = 16;
	SetConsoleCursorPosition(hout, coord);
	for (int i = 0; i < 7; i++) {
		printf("X");
		coord.X = 16;
		coord.Y--;
		SetConsoleCursorPosition(hout, coord);
	}
	printf("@");
	coord.X = 8;
	coord.Y = 5;
	SetConsoleCursorPosition(hout, coord);
	printf("*");
	coord.Y = 12;
	coord.X = 38;
	SetConsoleCursorPosition(hout, coord);	
	while (1) {
		ch = getch();
		if (ch == 's' || ch == 'S') break;
	}
}
void gameUI(int *score,RankList *rankList) {//绘制游戏界面
	COORD coord;
	system("cls");
	coord.X = 1;
	coord.Y = 1;
	SetConsoleCursorPosition(hout, coord);
	for (int i = 0; i < 40; i++)
		printf("#");
	for (int i = 0; i < 20; i++) {
		coord.X = 1;
		SetConsoleCursorPosition(hout, coord);
		printf("#");
		coord.X = 40;
		SetConsoleCursorPosition(hout, coord);
		printf("#");
		coord.Y++;
	}
	coord.X = 1;
	SetConsoleCursorPosition(hout, coord);
	for (int i = 0; i < 40; i++)
		printf("#");
	coord.X = 45;
	coord.Y = 1;
	SetConsoleCursorPosition(hout, coord);
	printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
	coord.Y++;
	SetConsoleCursorPosition(hout, coord);
	printf("X");
	coord.Y++;
	SetConsoleCursorPosition(hout, coord);
	printf("@");
	coord.X = 45;
	coord.Y = 21;
	SetConsoleCursorPosition(hout, coord);
	printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
	coord.Y--;
	coord.X = 74;
	SetConsoleCursorPosition(hout, coord);
	printf("X");
	coord.Y--;
	SetConsoleCursorPosition(hout, coord);
	printf("@");
	coord.Y = 4;
	coord.X = 52;
	SetConsoleCursorPosition(hout, coord);
	printf("·Hungry Snake·");
	coord.Y += 3;
	coord.X = 48;
	SetConsoleCursorPosition(hout, coord);
	printf("Your score: %d",*score);
	coord.Y += 3;
	coord.X = 48;
	SetConsoleCursorPosition(hout, coord);
	printf("Rinking List:");
	for (int i = 0; i < 5; i++) {
		coord.X = 48;
		coord.Y += 1;
		SetConsoleCursorPosition(hout, coord);
		printf("%d. %-14s%4d", i + 1, (rankList + i)->name, (rankList + i)->score);
	}
}
void invisibleCursor() {//设置光标不可见
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hout, &CursorInfo);//获取控制台光标信息  
	CursorInfo.bVisible = 0; //隐藏控制台光标  
	SetConsoleCursorInfo(hout, &CursorInfo);//设置控制台光标状态  
}
void initialSnake(SnakeBody* snakeHead) {//初始化蛇
	COORD coord;
	SnakeBody* p = snakeHead;
	while (p != NULL) {
		coord.X = p->x;
		coord.Y = p->y;
		SetConsoleCursorPosition(hout, coord);
		printf("%c", p->bodylook);
		p = p->next;
	}
}
void initialFood(SnakeBody* snakeHead,Food* food) {//初始化食物
	COORD coord;
	SnakeBody* p = snakeHead;
	int a,b,flag;
	while (1) {
		flag = 1;
		srand((int)time(NULL));
		a = (rand() % 38) + 2;
		b = (rand() % 17) + 2;
		while (p != NULL) {
			if (p->x == a && p->y == b) {
				flag = 0;
				break;
			}
			p = p->next;				
		}
		if (flag)
			break;
	}	
	food->x = a;
	food->y = b;
	coord.X = a;
	coord.Y = b;
	SetConsoleCursorPosition(hout,coord);
	printf("*");
}

/******************************game process************************************/
int gameProcess(SnakeBody** snakeHead,Food* food,int *score,RankList *rankList) {
	COORD coord;	
	int ch = 0,judg = 0;
	SnakeBody* temp;
	
	if (_kbhit()) {
		ch = _getch();
	}
	if (judgeGame(*snakeHead)) {
		return 1;
	}
	if (ch != 0) {
		(*snakeHead)->motionNum = ch;		
	}
	moveSnake(*snakeHead);
	if ((*snakeHead)->x == food->x && (*snakeHead)->y == food->y) {
		SnakeBody* newBody;
		newBody = (SnakeBody*)malloc(sizeof(SnakeBody));
		createSnakeBody(snakeHead, newBody);
		createFood(*snakeHead, food);
		recordScore(score);
	}
	showSnake(*snakeHead,food,score,rankList);
	return judg;
}
void moveSnake(SnakeBody* snakeHead) {//按每个身体结点的运动方向进行相应的移动，并返回蛇尾结点未操作前的副本
	SnakeBody* p = snakeHead;
	SnakeBody* temp = NULL;
	while (p->next != NULL) {
		p = p->next;
	}
	while (1) {
		temp = p->pre;
		if (temp == NULL)
			break;
		p->x = temp->x;
		p->y = temp->y;
		p = p->pre;
	}
	switch (snakeHead->motionNum) {
	case 0x50:
		snakeHead->y++;
		break;
	case 0x48:
		snakeHead->y--;
		break;
	case 0x4d:
		snakeHead->x++;
		break;
	case 0x4b:
		snakeHead->x--;
		break;
	}
}
void showSnake(SnakeBody* snakeHead,Food* food,int *score,RankList *rankList) {//打印蛇的身体和食物
	COORD coord;
	SnakeBody* p = snakeHead;
	gameUI(score,rankList);
	while (p != NULL) {
		coord.X = p->x;
		coord.Y = p->y;
		SetConsoleCursorPosition(hout, coord);
		printf("%c", p->bodylook);
		p = p->next;
	}	
	coord.X = food->x;
	coord.Y = food->y;
	SetConsoleCursorPosition(hout, coord);
	printf("*");
}
int judgeGame(SnakeBody* snakeHead) {//判断蛇是否撞到墙或者撞到自身，如果是返回1，否返回0
	SnakeBody* temp = snakeHead;
	SnakeBody* p = snakeHead;
	if (snakeHead->x > 38 || snakeHead->x < 3 ||
		snakeHead->y > 19 || snakeHead->y < 3)
		return 1;	
	return 0;
}
void createSnakeBody(SnakeBody** snakeHead,SnakeBody* newBody) {
	newBody->bodylook = '@';
	newBody->motionNum = (*snakeHead)->motionNum;
	newBody->next = *snakeHead;
	newBody->pre = NULL;
	switch (newBody->motionNum) {
	case 0x48:
		newBody->x = (*snakeHead)->x;
		newBody->y = (*snakeHead)->y - 1;
		break;
	case 0x50:
		newBody->x = (*snakeHead)->x;
		newBody->y = (*snakeHead)->y + 1;
		break;
	case 0x4d:
		newBody->x = (*snakeHead)->x + 1;
		newBody->y = (*snakeHead)->y;
		break;
	case 0x4b:
		newBody->x = (*snakeHead)->x - 1;
		newBody->y = (*snakeHead)->y;
		break;
	}
	(*snakeHead)->bodylook = 'X';
	(*snakeHead)->pre = newBody;
	*snakeHead = newBody;
}
void createFood(SnakeBody* snakeHead,Food* food) {
	SnakeBody* p = snakeHead;
	int a, b, flag;
	while (1) {
		flag = 1;
		srand((int)time(NULL));
		a = (rand() % 38) + 2;
		b = (rand() % 17) + 2;
		while (p != NULL) {
			if (p->x == a && p->y == b) {
				flag = 0;
				break;
			}
			p = p->next;
		}
		if (flag)
			break;
	}
	food->x = a;
	food->y = b;
}
void recordScore(int *score) {//记录分数
	COORD coord;
	*score += 10;
	coord.Y = 7;
	coord.X = 48;
	SetConsoleCursorPosition(hout, coord);
	printf("Your score: %d", *score);
}

/********************************game end**************************************/
void gameEnd(int *score,RankList *rankList) {//游戏结束
	char ch;
	updateRanking(rankList, score);
	endUI(score);
	while (1) {
		ch = getch();
		if (ch == 's' || ch == 'S') {
			break;
		}
	}
}
void endUI(int *score) {//游戏结束界面
	COORD coord;
	system("cls");
	coord.X = 35;
	coord.Y = 10;
	SetConsoleCursorPosition(hout, coord);
	printf("Game Over!");
	coord.X = 32;
	coord.Y += 3;
	SetConsoleCursorPosition(hout, coord);
	printf("your score is %d", *score);
	coord.X = 27;
	coord.Y += 4;
	SetConsoleCursorPosition(hout, coord);
	printf("push 'S' to restart the game");
}
void updateRanking(RankList *rankList, int *score) {//游戏结束更新排行榜
	if (*score < (rankList + 4)->score) return;
	(rankList + 4)->score = *score;
	(rankList + 4)->name = "Joezeo";
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5 - i - 1; j++) {
			RankList tmp;
			if ((rankList + j)->score < (rankList + j + 1)->score) {
				tmp.name = (rankList + j)->name;
				tmp.score = (rankList + j)->score;
				(rankList + j)->name = (rankList + j + 1)->name;
				(rankList + j)->score = (rankList + j + 1)->score;
				(rankList + j + 1)->name = tmp.name;
				(rankList + j + 1)->score = tmp.score;
			}
		}
	}
}
