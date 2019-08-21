//#include <stdio.h>
//#include <time.h>
//#include<stdlib.h>
//#include <windows.h>
//#include <conio.h>
//
//// screen size
//#define COLUMN 80
//#define ROW 24
//
//void gotoxy(int x, int y);	// move cursor to (x, y)
//
//void DrawCross(char array[][COLUMN]);
//void DrawVertical(char array[][COLUMN]);
//void DrawRandom(char array[][COLUMN]);	
//
//void FillRandom();			// provided
//char GetRandomChar();		// provided
//
//void CheckMove(char array[][COLUMN], int x, int y);
//
//int main()
//{
//	char text[ROW][COLUMN];
//	int x = 0, y = 0;
//
//	srand(time(NULL));		// initialize random seed.
//
//	//십자가를 만든다
//	DrawCross(text);
//	
//	FillRandom();		//랜덤으로 채운다
//	getch();
//	DrawVertical(text);		//수평으로 벌어지게 한다
//	
//	gotoxy(1, 24);
//	system("PAUSE");		//잠시 프로그램을 멈춘다
//	
//	FillRandom();		//랜덤으로 채운다
//	getch();
//	DrawRandom(text);		//랜덤으로 십자가가 생기게한다
//
//	gotoxy(1, 24);
//	
//	return 0;	
//}
//
//void DrawCross(char array[][COLUMN])
//{
//	int i=0,j=0;
//	
//	//빈칸으로 전체를 채운다
//	for(j=0;j<24;j++)
//		for(i=0;i<80;i++)
//			array[j][i] = ' ';
//
//	//십자가를 만든다
//	for(i=5;i<21;i++)
//		array[i][40] = '#';
//	for(i=30;i<51;i++)
//		array[10][i] = '#';
//
//	return;
//}
//void DrawVertical(char array[][COLUMN])
//{
//	int i=0,j=0,i2=0;
//
//	for(i=40;i>0;i--){
//		i2=40+(40-i);
//		Sleep(15);
//		for(j=1;j<=ROW;j++){
//			//i와 i2를 이용해 벌어지게한다
//			gotoxy(i,j);
//			putchar(array[j-1][i-1]);
//			gotoxy(i2+1,j);
//			putchar(array[j-1][i2]);
//		}
//	}
//	return;
//}
//
//void DrawRandom(char array[][COLUMN])
//{
//	int i=0;
//	int x=0,y=0;
//	
//	srand(time(NULL));		//랜덤 시드를 초기화한다
//	for(i=0;i<(80*24);i++){
//		//x와 y를 임의로 정한다
//		x=rand()%80;
//		y=rand()%24;
//		CheckMove(array,x,y);
//	}
//	return;
//}
//
//void FillRandom()
//{
//	int x = 0, y = 0;
//	
//	gotoxy(1, 1);
//	for(y = 0; y < ROW; y++)
//		for(x = 0; x < COLUMN; x++)
//			putchar(GetRandomChar());
//}
//
//char GetRandomChar()
//{
//	const int noUpperCase = 26;
//	const int noLowerCase = 26;
//	const int noDigits = 10;
//
//	int x = rand() % (noUpperCase + noLowerCase + noDigits);
//	if(x < noUpperCase)
//		return 'A' + x;
//	else if(x < noUpperCase + noLowerCase)
//		return 'a' + x - noUpperCase;
//	else
//		return '0' + x - (noUpperCase + noLowerCase);
//}
//
//void gotoxy(int x, int y)	// move cursor to (x, y)
//{
//	COORD Pos = {x - 1, y - 1};
//
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
//}
//
////재귀함수를 이용하여 랜덤으로 나타나는 현상을 해결한다
//void CheckMove(char array[][COLUMN], int x, int y)
//{
//	//중복인 경우
//	if(array[y][x] == '+'){
//		if(x == 79){
//			if(y == 23)		//가장 끝인경우 제일 앞으로 보낸다
//				CheckMove(array,0,0);
//			else		//x에서만 끝인경우 다음칸의 앞으로 보낸다
//				CheckMove(array,0,y+1);
//		}
//		else		//나머지 경우 x값만 증가한다
//			CheckMove(array,x+1,y);
//	}
//	//아닌경우 화면에 입력하고 값을 변경한다
//	else{
//		gotoxy(x+1,y+1);
//		putchar(array[y][x]);
//		array[y][x]='+';
//		Sleep(1);
//	}
//
//	return ;
//}