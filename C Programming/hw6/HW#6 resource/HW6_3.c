#include <stdio.h>
#include <windows.h>
#include <conio.h>

void clrscr(void);			// clear the screen
void gotoxy(int x, int y);	// move cursor to (x, y)

#define LeftBound 1
#define RightBound 80
#define TopBound 1
#define BottomBound 23

int main()
{
	int barLength = 5;
	int x = (LeftBound + RightBound - barLength) / 2;
	int y = BottomBound;

	int i = 0;
	int dx = 0;
	int oldx = -1;
	char key = 0;

	clrscr();
	
	gotoxy(LeftBound, BottomBound);
	putchar('|');
	gotoxy(RightBound, BottomBound);
	putchar('|');

	gotoxy(1, 1);
	printf("Move bar with 'j' and 'l'.");

	gotoxy(1, BottomBound + 1);
	printf("Press ESC to go next");

	gotoxy(x, y);
	for(i = 0; i < barLength; i++)
		printf("=");


	do {
		// save old coordinate
		oldx = x;
		key = 0;
		// if the key is pressed
		if(kbhit()){
			// read a key by getch()
			key = getch();
			}
		switch(key){
		case 'l': /*dx can be [-3,3](except 0). 
					than dx can make acceleration. */
			if(dx==3)
				break;
			else if(dx>0&&dx<3)
				dx++;
			else 
				dx=1;
			break;
		case 'j':
			if(dx==-3)
				break;
			else if(dx<0&&dx>-3)
				dx--;
			else
				dx=-1;
			break;
		}
		
		if(dx != 0){
			//update x using dx
			x+=dx;
			// check if the bar hits the boundary
			if(x<2)
				x=2,dx=0;
			else if(x>75)
				x=75,dx=0;
		}

		if(x != oldx){		// if the bar moved
			//erase old bar
			gotoxy(oldx,y);
			for(i=0;i<5;i++)
				putchar(' ');
			//draw new bar
			gotoxy(x,y);
			for(i=0;i<5;i++)
				putchar('=');
		}

		Sleep(50);
	} while (key != 27);			// 27 is the ASCII code of ESC

	clrscr();
	gotoxy(1, 1);

	return 0;
}

void clrscr(void)			// clear the screen
{
	COORD Cur = {0, 0};
	unsigned long dwLen = 0;

	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 80*25, Cur, &dwLen);
}

void gotoxy(int x, int y)	// move cursor to (x, y)
{
	COORD Pos = {x - 1, y - 1};

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
