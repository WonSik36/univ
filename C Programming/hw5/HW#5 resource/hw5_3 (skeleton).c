#include <stdio.h>
#include <windows.h>
#include <conio.h>


void clrscr(int x, int y, char c);			// 지정된 자리에 원하는 문자로 채운다
void gotoxy(int x, int y);	// move cursor to (x, y)

#define ScreenWidth 80
#define ScreenHeight 24

// Relative coordinate with respect to the center position
int Block_x[4][4] = {			// x coordinates
		{ -1, 0, 0, 1},			// dir 0
		{ -1, 0, 0, 0},			// dir 1
		{ -1, 0, 0, 1},			// dir 2
		{ 0, 0, 0, 1}			// dir 3
	};

int Block_y[4][4] = {			// y coordinates
		{ 0, 0, -1, 0},			// dir 0
		{ 0, 0, 1, -1},			// dir 1
		{ 0, 0, 1, 0},			// dir 2
		{ -1, 0, 1, 0}			// dir 3
	};

void DrawBoundary();

void DrawBlock(int x, int y, int dir, char c);

int main()
{
	int x = ScreenWidth / 2, y = ScreenHeight / 2;
	int dir = 0;

	int oldx = -1, oldy = -1;
	int oldDir = -1;

	char key = 0;

	DrawBoundary();
	DrawBlock(x, y, dir, 'O');

	while(key != 27){			// ESC
 		// save old coordinates and direction
 		oldx = x, oldy = y;
		oldDir = dir;
 		// read a key using getch()
 		key = getch();
 		// update x, y, and dir according to the key
 		switch(key){
			//방향이동의 경우
		case'i':
			if(dir==2){
				if(y>2)
					y--;}
			else if(y>3)
				y--;
			break;
		case'j':
			if(dir==3){
				if(x>2)
					x--;}
			else if(x>3)
				x--;
			break;
		case'k':
			if(dir==0){
				if(y<23)
					y++;}
			else if(y<22)
				y++;
			break;
		case'l':
			if(dir==1){
				if(x<79)
					x++;}
			else if(x<78)
				x++;
			break;
			//회전의 경우
		case'u':
			if(y==23||y==2)
				break;
			if(x==2||x==79)
				break;
			dir = (dir+1)%4;
			break;
		case'o':
			if(y==23||y==2)
				break;
			if(x==2||x==79)
				break;
			dir = (dir+3)%4;
			break;
		}
		DrawBlock(oldx, oldy, oldDir, ' ');		// erase previous shape
		DrawBlock(x, y, dir, 'O');						// draw the shape using new coordinates and direction
	}

	return 0;
}

void DrawBoundary()
{
 	int i;

	for(i=1;i<25;i++)
		clrscr(1,i,'0');
	for(i=1;i<25;i++)
		clrscr(80,i,'0');
	for(i=1;i<81;i++)
		clrscr(i,1,'0');
	for(i=1;i<81;i++)
		clrscr(i,24,'0');

	return;
}


void DrawBlock(int x, int y, int dir, char c)
// Draw the shape of a direction at (x, y)
// c is the symbol to draw
// 		If c == 'O', draw the shape.
//		If c == ' ', erase the shape.
{
 	int i=0;
	for(i=0; i<4; i++)
	{
		gotoxy(x + Block_x[dir][i], y + Block_y[dir][i]);
		putchar(c);
	}

	return;
}
void clrscr(int x, int y, char c)			// 지정된 자리에 원하는 값으로 채운다
{
	COORD Cur = {x - 1, y - 1};
	unsigned long dwLen = 0;

	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), c, 1, Cur, &dwLen);
}

void gotoxy(int x, int y)	// move cursor to (x, y)
{
	COORD Pos = {x - 1, y - 1};

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
