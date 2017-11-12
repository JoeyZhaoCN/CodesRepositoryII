/*****************************
*Editor:Joey Zhao
*E-mail:joeyzhaocn@foxmail.com
*Date:2017/10/30/21/30
*****************************/
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

HANDLE hout;
void CreateUI();			//生成用户界面
int opearteCom();			//操作计算器，返回操作结果
void showInScreen(int n);		//在计算显示区显示操作过程或运算结果
void cleanScrenn();			//清屏计算显示区
void messageError();			//计算显示区提示“ERROR”
int main()
{
	hout = GetStdHandle(STD_OUTPUT_HANDLE);	
	CreateUI();	

	while (1) {	
		cleanScrenn();
		int num1 = 0, num2 = 0, ope = 0;
		int cnt = 0, temp = 0, flag = 0;
		for (;;) {
			if((num1 != 42 && num1 != 43 && num1 != 45 && num1 != 47 && num1 != 61) && cnt < 10) {	/*处理第一个数值*/
				num1 = opearteCom();				
				if(num1 != 42 && num1 != 43 && num1 != 45 && num1 != 47 && num1 != 61)
					temp = temp * 10 + num1;
				showInScreen(temp);
				cnt++;
			}	
			if (num1 == 42 || num1 == 43 || num1 == 45 || num1 == 47)
				break;
			if (cnt == 10) {
				messageError();
				temp = 0; num1 = 0;
				break;
			}
		}
		while (cnt == 10) {		/*如果超过最大数值，则提示ERROR，回到开头，初始化计算器*/
			int tmp;
			tmp = getch();
			if (tmp == '\r') {	/*输入回车归0，初始化计算器*/
				flag = 1;
				break;
			}			
		} 
		if(flag) continue;

		while (num1 == 61) {		/*如果处理完第一个数就按“=”，则直接输出结果*/
			cleanScrenn();
			showInScreen(temp);
			int tmp;
			tmp = getch();
			if (tmp == '\r') {
				flag = 1;
				break;
			}
		}
		if(flag) continue;

		cleanScrenn();
		ope = num1;
		num1 = temp;
		temp = 0; cnt = 0;

		for (;;) {
			if ((num2 != 42 && num2 != 43 && num2 != 45 && num2 != 47 && num2 != 61) && cnt < 10) {		/*处理第二个数值*/
				num2 = opearteCom();
				if(num2 != 42 && num2 != 43 && num2 != 45 && num2 != 47 && num2 != 61)
					temp = temp * 10 + num2;
				showInScreen(temp);
				cnt++;
			}
			if (num2 == 42 || num2 == 43 || num2 == 45 || num2 == 47 || num2 == 61)
				break;
			if (cnt == 10) {
				messageError();
				temp = 0; num2 = 0;
				break;
			}
		}
		while (cnt == 10) {			/*如果超过最大数值，则提示ERROR，并且回到开头，初始化计算器*/
			int tmp;
			tmp = getch();
			if (tmp == '\r') {		/*归0，初始化计算器*/
				flag = 1;
				break;
			}
		}
		if(flag) continue;

		while (num2 == 42 || num2 ==43 || num2 == 45 || num2 == 47) {	/*输入完第二个数值后,如果键入“+-/*”,发生错误，回到开头，初始化计算器*/
			messageError();
			int tmp;
			tmp = getch();
			if (tmp == '\r') {
				flag = 1;
				break;
			}
		}
		if (flag) continue;

		num2 = temp;
		temp = 0; cnt = 0;
		switch (ope)
		{
		case 42:
			temp = num1 * num2;
			break;
		case 43:
			temp = num1 + num2;
			break;
		case 45:
			temp = num1 - num2;
			break;
		case 47:
			temp = num1 / num2;
			break;
		default:
			break;
		}
		
		while (temp > 999999999) {		/*如果计算结果超过最大数值，则提示ERROR，回到开头，初始化计算器*/
			messageError();
			int tmp;
			tmp = getch();
			if (tmp == '\r') {
				flag = 1;
				break;
			}
		}
		if(flag) continue;
		
		cleanScrenn();
		showInScreen(temp);
		for (;;) {
			int tmp;
			tmp = getch();
			if (tmp == 0x0d) break;
		}
	}
	getchar();
	return 0;
}

void CreateUI() {
	COORD coord;
	int cnt = 7;
	/*起始坐标（22，1）*/
	coord.X = 30;
	coord.Y = 3;
	SetConsoleCursorPosition(hout, coord);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d", cnt);
			coord.X += 3;
			SetConsoleCursorPosition(hout, coord);
			cnt++;
		}
		cnt -= 6;
		coord.Y += 2;
		coord.X = 30;
		SetConsoleCursorPosition(hout, coord);
	}

	coord.X = 33;
	SetConsoleCursorPosition(hout, coord);
	printf("0");	//(3,38)

	coord.X = 40;
	coord.Y = 5;
	SetConsoleCursorPosition(hout, coord);
	printf("+");
	coord.X += 3;
	SetConsoleCursorPosition(hout, coord);
	printf("-");
	coord.X = 40;
	coord.Y += 2;
	SetConsoleCursorPosition(hout, coord);
	printf("x");
	coord.X += 3;
	SetConsoleCursorPosition(hout, coord);
	printf("/");
	coord.Y += 2;
	coord.X = 40;
	SetConsoleCursorPosition(hout, coord);
	printf("=");

	coord.Y = 2;
	coord.X = 28;
	SetConsoleCursorPosition(hout, coord);
	for (int i = 0; i < 11; i++) {
		printf("|");
		coord.X = 44;
		SetConsoleCursorPosition(hout, coord);
		printf("|");
		coord.X = 28;
		coord.Y++;
		SetConsoleCursorPosition(hout, coord);
	}
	coord.Y = 2;
	coord.X = 29;
	SetConsoleCursorPosition(hout, coord);
	printf("---------------");
	coord.Y = 10;
	coord.X = 29;
	SetConsoleCursorPosition(hout, coord);
	printf("---------------");
	coord.Y += 2;
	coord.X = 29;
	SetConsoleCursorPosition(hout, coord);
	printf("---------------");

	coord.Y = 4;
	coord.X = 0;
	SetConsoleCursorPosition(hout, coord);
	printf("说明：");

	coord.Y = 6;
	coord.X = 0;
	SetConsoleCursorPosition(hout, coord);
	printf("这是一个简易计算器");

	coord.Y += 2;
	coord.X = 0;
	SetConsoleCursorPosition(hout, coord);
	printf("按《回车》选取数字和运算符");

	coord.Y += 2;
	coord.X = 0;
	SetConsoleCursorPosition(hout, coord);
	printf("运算结束后按《回车》归0");

	coord.Y += 3;
	coord.X = 0;
	SetConsoleCursorPosition(hout, coord);
	printf("本计算器支持最大数值999999999\n");
	printf("ERROR:表示超过最大数值限制,或者进行了非法操作，按《回车》归0");

}
/*
此计算器光标移动的边界为：
X：29 - 44
Y：02 - 10
数据输出行为：11
*/
int opearteCom() {
	COORD coord;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	coord.X = 29;
	coord.Y = 2;
	SetConsoleCursorPosition(hout, coord);

	int ch;
	STEP1:ch = getch();

	while (1) {
		ch = getch();
		
		if (ch == 0x48) {	//上
			if (coord.Y != 2) coord.Y--;
		}

		if (ch == 0x50) {	//下
			if (coord.Y != 9) coord.Y++;
		}

		if (ch == 0x4b) {	//左
			if (coord.X != 29) coord.X--;
		}

		if (ch == 0x4d) {	//右
			if (coord.X != 43) coord.X++;
		}
		SetConsoleCursorPosition(hout, coord);
		ch = getch();
		if (ch == 0x0d) {
			switch (coord.Y) {
			case 3:
				if (coord.X == 30) ch = 7;
				if (coord.X == 33) ch = 8;
				if (coord.X == 36) ch = 9;
				break;
			case 5:
				if (coord.X == 30) ch = 4;
				if (coord.X == 33) ch = 5;
				if (coord.X == 36) ch = 6;
				if (coord.X == 40) ch = 43;		//+ : 43
				if (coord.X == 43) ch = 45;		//- : 45
				break;
			case 7:
				if (coord.X == 30) ch = 1;
				if (coord.X == 33) ch = 2;
				if (coord.X == 36) ch = 3;
				if (coord.X == 40) ch = 42;		//* : 42
				if (coord.X == 43) ch = 47;		// /: 47
				break;
			case 9:
				if (coord.X == 33) ch = 0;
				if (coord.X == 40) ch = 61;		//= : 61
				break;
			}	
			break;
		}			
	}
	if (ch == 13) goto STEP1;
	return ch;
}

void showInScreen(int n) {
	COORD coord;
	coord.Y = 11;
	coord.X = 29;
	SetConsoleCursorPosition(hout, coord);
	printf("%d", n);
}

void cleanScrenn() {
	COORD coord;
	coord.Y = 11;
	coord.X = 29;
	SetConsoleCursorPosition(hout, coord);
	for (int i = 0; i < 15; i++) {
		printf(" ");
	}	
}

void messageError() {
	COORD coord;
	cleanScrenn();
	coord.Y = 11;
	coord.X = 29;
	SetConsoleCursorPosition(hout, coord);
	printf("ERROR!");
}


