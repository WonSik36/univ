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
//	//���ڰ��� �����
//	DrawCross(text);
//	
//	FillRandom();		//�������� ä���
//	getch();
//	DrawVertical(text);		//�������� �������� �Ѵ�
//	
//	gotoxy(1, 24);
//	system("PAUSE");		//��� ���α׷��� �����
//	
//	FillRandom();		//�������� ä���
//	getch();
//	DrawRandom(text);		//�������� ���ڰ��� ������Ѵ�
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
//	//��ĭ���� ��ü�� ä���
//	for(j=0;j<24;j++)
//		for(i=0;i<80;i++)
//			array[j][i] = ' ';
//
//	//���ڰ��� �����
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
//			//i�� i2�� �̿��� ���������Ѵ�
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
//	srand(time(NULL));		//���� �õ带 �ʱ�ȭ�Ѵ�
//	for(i=0;i<(80*24);i++){
//		//x�� y�� ���Ƿ� ���Ѵ�
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
////����Լ��� �̿��Ͽ� �������� ��Ÿ���� ������ �ذ��Ѵ�
//void CheckMove(char array[][COLUMN], int x, int y)
//{
//	//�ߺ��� ���
//	if(array[y][x] == '+'){
//		if(x == 79){
//			if(y == 23)		//���� ���ΰ�� ���� ������ ������
//				CheckMove(array,0,0);
//			else		//x������ ���ΰ�� ����ĭ�� ������ ������
//				CheckMove(array,0,y+1);
//		}
//		else		//������ ��� x���� �����Ѵ�
//			CheckMove(array,x+1,y);
//	}
//	//�ƴѰ�� ȭ�鿡 �Է��ϰ� ���� �����Ѵ�
//	else{
//		gotoxy(x+1,y+1);
//		putchar(array[y][x]);
//		array[y][x]='+';
//		Sleep(1);
//	}
//
//	return ;
//}