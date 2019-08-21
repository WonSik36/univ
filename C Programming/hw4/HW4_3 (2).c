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

	//사용법을 설명한다
	printf("Push \'j\' to move left, \'l\' to move right.\n");
	printf("Push \'i\' to move up, \'k\' to move down or \'q\' to quit.");
	
	//초기 커서 값을 설정한다
	gotoxy(x,y);
	printf("*");

	//버튼에 따른 조작을 설정한다
	while(c!='q'){
		oldx=x,oldy=y;
		c=getch();
		switch(c){
		//왼쪽
		case 'j':
			if(x>1) x--;
			cirsir(oldx,oldy);
			Sleep(500);
			gotoxy(x,y);
			putchar('*');
			break;
		//오른쪽
		case 'l':
			if(x<80) x++;
			cirsir(oldx,oldy);
			Sleep(500);
			gotoxy(x,y);
			putchar('*');
			break;
		//위
		case 'i':
			if(y>3) y--;
			cirsir(oldx,oldy);
			Sleep(500);
			gotoxy(x,y);
			putchar('*');
			break;
		//아래
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

//이전 별을 없애는 함수
void cirsir(int x,int y)
{
	COORD Cur={x-1,y-1};
	unsigned long dwLen=0;

	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 1, Cur, &dwLen);
}

//커서를 움직이는 함수
void gotoxy(int x, int y)
{
	COORD Pos = {x -1, y -1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}