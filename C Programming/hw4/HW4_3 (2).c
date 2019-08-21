#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24

void cirsir(int x,int y);
void gotoxy(int x,int y);

int main(void)
{
	int x=SCREEN_WIDTH/2, y=SCREEN_HEIGHT/2;
	int oldx=0, oldy=0;
	int i=0;
	char c=0;

	//������ �����Ѵ�
	printf("Push \'j\' to move left, \'l\' to move right.\n");
	printf("Push \'i\' to move up, \'k\' to move down or \'q\' to quit.");
	
	//�ʱ� Ŀ�� ���� �����Ѵ�
	gotoxy(x,y);
	printf("*");

	//��ư�� ���� ������ �����Ѵ�
	while(c!='q'){
		oldx=x,oldy=y;
		c=getch();
		switch(c){
		//����
		case 'j':
			if(x>1) x--;
			cirsir(oldx,oldy);
			Sleep(500);
			gotoxy(x,y);
			putchar('*');
			break;
		//������
		case 'l':
			if(x<80) x++;
			cirsir(oldx,oldy);
			Sleep(500);
			gotoxy(x,y);
			putchar('*');
			break;
		//��
		case 'i':
			if(y>3) y--;
			cirsir(oldx,oldy);
			Sleep(500);
			gotoxy(x,y);
			putchar('*');
			break;
		//�Ʒ�
		case 'k':
			if(y<24) y++;
			cirsir(oldx,oldy);
			Sleep(500);
			gotoxy(x,y);
			putchar('*');
			break;
		}}
	return 0;
}

//���� ���� ���ִ� �Լ�
void cirsir(int x,int y)
{
	COORD Cur={x-1,y-1};
	unsigned long dwLen=0;

	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 1, Cur, &dwLen);
}

//Ŀ���� �����̴� �Լ�
void gotoxy(int x, int y)
{
	COORD Pos = {x -1, y -1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}