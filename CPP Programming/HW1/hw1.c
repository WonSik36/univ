/*******************************************************************
							HW1
											21300691
											Cheung Won Sik

	more than 400 lines
	more than 15 functions

	1. Problem definition
		- I want to make a brick-breaking game. 
		  However, I do not have enough time during the semester, so I want to write a ball-bouncing program. 
		  If you just bounce the ball is not fun, add another function.

	2. Design of your program
		- There are three options. 
		- First, it is an option to draw bricks on maps in the game. 
		- Secondly, there is a brick in the place where the ball passes after playing the game. 
		- Finally, erase all the bricks on the map.

	3. Primary codes with comments

	4. Screen show of the result


*******************************************************************/
#include <stdio.h>
#include <stdlib.h> // sleep()
#include <conio.h> // kbhit(), getch()
#include <windows.h> // SetConsoleCursorPosition(), GetStdHandle(), system('pause')

// Define true false boolean
#define TRUE 1
#define FALSE 0

// Adjust position X, Y
#define ADJUST_X 5
#define ADJUST_Y 3

// Boundary constant
#define LEFT_BOUND     1
#define RIGHT_BOUND   80
#define TOP_BOUND      1
#define BOTTOM_BOUND  24

// mapCanvas mode constant
#define MODE_MOVE 0
#define MODE_DRAW 1
#define MODE_ERASE 2
#define MODE_REVERSE 3

// block attribute
#define BLANK 0
#define BLOCK 1
#define WALL_VERTICAL 11
#define WALL_TOP 12
#define WALL_BOTTOM 13

/********* base function *********/
void gotoxy(int x, int y);
void clrscr();
void gotoxyAdjust(int x, int y, int adjX, int adjY);
void printOption();

/****** function for mapCanvas ******/
void mapCanvas(char map[24][80]);
void markXY(int x, int y, int mode, char map[24][80]);
void markBoundary(char map[24][80]);
void initMap(char map[24][80]);
void displayXY(int x, int y, char map[24][80]);
void displayMap(char map[24][80]);

/******* Bouncing ball function  *******/
void bouncingBall(int sx, int sy, int dx, int dy, char map[24][80]);
int absolute(int num);
int isWall(char ch);
int isBlock(char ch);
int isBlank(char ch);
int isWallBlock(char ch);

int main(){
	char ch = 0;
	char screen[24][80];

	// initialize screen array
	clrscr();
  	initMap(screen);
  	markBoundary(screen);

  	// show 3 options and activate 
	do{
		switch(ch){
		
		// option1: draw map
		case '1':
			clrscr();
  			mapCanvas(screen);
  			break;
  		// option2: bouncing ball
  		case '2':
  			clrscr();
  			bouncingBall(10, 10, 2, 1, screen);	
  			break;
  		// option3: clear screen array
  		case '3':
  			clrscr();
  			initMap(screen);
  			markBoundary(screen);
  			break;
		}

		//show options
		clrscr();
		printOption();
		ch = getchar();

	}while(ch!=27);

  	clrscr();
  	gotoxy(1,1);
  	system("pause");
  	return 0;
}

// go screen x,y position 
void gotoxy(int x, int y){
   COORD Pos = {x - 1, y - 1};

   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// clear screen
void clrscr(void){
   COORD Cur= {0, 0};
   unsigned long dwLen;
   FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE) , ' ', 80*25, Cur, &dwLen);
   Cur = {10, 12};
   FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE) , ' ', 80*25, Cur, &dwLen);
}

// go screen x,y position which adjusted by adjX, adjY
void gotoxyAdjust(int x, int y, int adjX, int adjY){
   COORD Pos = {x + adjX - 1, y + adjY - 1};

   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// print option
void printOption(){
	gotoxy(30, 8); 
	printf("##############################");
	gotoxy(30, 9); 
	printf("#                            #");
	gotoxy(30, 10); 
	printf("#     Draw Bouncing Ball     #");
	gotoxy(30, 11); 
	printf("#                            #");
	gotoxy(30, 12); 
	printf("#   1. Draw Map              #");
	gotoxy(30, 13); 
	printf("#   2. Start Bouncing Ball   #");
	gotoxy(30, 14); 
	printf("#   3. Clear Screen          #");
	gotoxy(30, 15); 
	printf("#                            #");
	gotoxy(30, 16); 
	printf("#   Push ESC to End          #");
	gotoxy(30, 17); 
	printf("##############################");
	gotoxy(30, 18); 
}


// draw map by block before start game
void mapCanvas(char map[24][80]){
    int key = 0;
    int x = 0, y = 0;
    int oldx = 0, oldy = 0;
	int mode = MODE_MOVE;
	int oldMode = -1;
	char *message = "1: Move, 2: Draw, 3: Erase, 4: Reverse  ||  i: up, j: left, l: right, k: down ";

	// initialize part
	displayMap(map);

    gotoxy(2, 2);
    printf("Map Canvas ");
	gotoxyAdjust(1, BOTTOM_BOUND+1, ADJUST_X, ADJUST_Y);
	printf(message);

    gotoxyAdjust(1, BOTTOM_BOUND+2, ADJUST_X, ADJUST_Y);
    printf("Press ESC to go next");

    oldx = x = (LEFT_BOUND + RIGHT_BOUND) / 2;
    oldy = y = (TOP_BOUND + BOTTOM_BOUND) / 2;

    // draw part
	do {
		gotoxyAdjust(x, y, ADJUST_X, ADJUST_Y);
		putchar('*');

		if(oldx != x || oldy != y)
			displayXY(oldx, oldy, map);

		 key = getch();

		oldx = x;
		oldy = y;

		oldMode = mode;

		switch(key){
		// move cursor
		case 'j':
			if(x - 1 > LEFT_BOUND)
				x--;
			break;
		case 'l':
			if(x + 1 < RIGHT_BOUND)
				x++;
			break;
		 case 'i':
			if(y - 1 > TOP_BOUND)
				y--;
			break;
		 case 'k':
			if(y + 1 < BOTTOM_BOUND)
				y++;
			break;

		// change drawing mode
		 case '1':
			mode = MODE_MOVE;
			break;
		 case '2':
			mode = MODE_DRAW;
			break;
		 case '3':
			mode = MODE_ERASE;
			break;
		 case '4':
			mode = MODE_REVERSE;
			break;
		 }

		 markXY(x, y, mode, map);
	// while loop break when player enter ESC
	} while (key != 27);

	clrscr();
	gotoxy(1, 1);
}

// initialize map array attribute to 0
void initMap(char map[24][80]){
	int x, y;

	for(y = TOP_BOUND; y < BOTTOM_BOUND; y++){
		for(x = LEFT_BOUND; x < RIGHT_BOUND; x++)
			map[y][x] = 0;
	}
}

// draw attribute by given mode
void markXY(int x, int y, int mode, char map[24][80]){
	switch(mode){
	case MODE_MOVE:
		break;
	case MODE_DRAW:
		map[y][x] = BLOCK;
		break;
	case MODE_ERASE:
		map[y][x] = BLANK;
		break;
	case MODE_REVERSE:
		map[y][x] = 1 - map[y][x];
		break;
	}
}

// set two dimension array surface to surface attribute
void markBoundary(char map[24][80]){
	int x = 0, y = 0;

	for(y = TOP_BOUND; y <= BOTTOM_BOUND; y++){
		map[y][LEFT_BOUND] = WALL_VERTICAL;
		map[y][RIGHT_BOUND] = WALL_VERTICAL;
	}

	for(x = LEFT_BOUND; x <= RIGHT_BOUND; x++){
		map[TOP_BOUND][x] = WALL_TOP;
		map[BOTTOM_BOUND][x] = WALL_BOTTOM;
	}
}

// display character in window x, y position
void displayXY(int x, int y, char map[24][80]){
	gotoxyAdjust(x, y, ADJUST_X, ADJUST_Y);
	switch(map[y][x]){
	case BLANK:
		putchar(' ');
		break;
	case BLOCK:
		putchar('#');
		break;
	case WALL_VERTICAL:
		putchar('|');
		break;
	case WALL_TOP:
		putchar('_');
		break;
	case WALL_BOTTOM:
		putchar('-');
		break;
	}
}

// move two dimension array attribute to window and display it
void displayMap(char map[24][80]){
	int x, y;

	for(y = TOP_BOUND; y <= BOTTOM_BOUND; y++){
		for(x = LEFT_BOUND; x <= RIGHT_BOUND; x++){
			displayXY(x, y, map);
		}
	}
}

// Bouncing ball appear and continue bounce and draw block
void bouncingBall(int sx, int sy, int dx, int dy, char map[24][80])
{
	// sx, sy : first position of x, y
	// dx, dy : x, y 's speed 

	// x,y : current position
	// oldx, oldy : where x, y passess position
	// fdx, fdy : real speed of x, y
	// max : speed control variable. The smaller the speed, the faster.
	// n : clock variable when n%max == 0 cursor move
	float x = sx, y = sy;
	float oldx = 0, oldy = 0;
	float fdx = 0., fdy = 0.;
	int max = dx;

	char key = 0;
	int n = 0;

	// set fdx, fdy, max
	if(dx != 0 && absolute(dx) >= absolute(dy)){
		fdx = (dx > 0 ? 1. : -1.);
		fdy = dy / (float)absolute(dx);
	} else if(dy != 0){
		fdx = dx / (float)absolute(dy);
		fdy = (dy > 0 ? 1. : -1.);
		max = dy;
	} else {
		fdx = dx;
		fdy = dy;
	}

	// for safety
	if(max <= 0)		
		max = 1;

	// initialize part
	displayMap(map);

	gotoxy(2, 2);
    printf("Bouncing Ball ");
    gotoxyAdjust(1, BOTTOM_BOUND + 1, ADJUST_X, ADJUST_Y);
    printf("Press ESC to go next");

	x = oldx = sx;
	y = oldy = sy;


	do {
		if(n % max == 0){
			// display ball
			gotoxyAdjust((int)x, (int)y, ADJUST_X, ADJUST_Y);
			putchar('*');

			// erase previous ball
			if(x != oldx || y != oldy){
				markXY(oldx, oldy, MODE_DRAW, map);
				gotoxyAdjust((int)oldx, (int)oldy, ADJUST_X, ADJUST_Y);
				putchar('#');
			}
		}

		Sleep(100 / max);

		// save current position
		if(n % max == 0){
			oldx = x;
			oldy = y;
		}

		x += fdx;
		y += fdy;

		if(isWallBlock(map[(int)y][(int)x])){
			// meet vertical wall
			if(isWallBlock(map[(int)oldy][(int)x]) && isBlank(map[(int)y][(int)oldx])){ 
				fdx = -fdx;
				x = oldx + fdx;
				// bounced again
				if(isWallBlock(map[(int)y][(int)x])){	
					// corner
					if(isBlank(map[(int)oldy][(int)oldx])){
						x = oldx;
						y = oldy;
						fdy = -fdy;
					} else {
						fdx = -fdx;
						x = oldx;
					}
				}
			// meet horizontal wall
			} else if(isBlank(map[(int)oldy][(int)x]) && isWallBlock(map[(int)y][(int)oldx])){ 
				fdy = -fdy;
				y = oldy + fdy;
				// bounced again
				if(isWallBlock(map[(int)y][(int)x])){
					// corner	
					if(isBlank(map[(int)y][(int)oldx])){
						x = oldx;
						y = oldy;
						fdx = -fdx;
					} else {
						fdy = -fdy;
						y = oldy;
					}
				}
			// corner
			} else {			
				fdx = -fdx;
				fdy = -fdy;
				x = oldx + fdx;
				y = oldy + fdy;
				// bounced again
				if(isWallBlock(map[(int)y][(int)x])){	
					x = oldx;
					y = oldy;
				}
			}
		}

		if(kbhit())
			key = getch();
		n++;
	} while (key != 27);
}

// return absolute number
int absolute(int num){
	return num>=0 ? num : -(num);
}

// check char is wall
int isWall(char ch){
	if(ch>10 && ch<15)
		return TRUE;
	return FALSE;
}

// check char is block
int isBlock(char ch){
	if(ch == BLOCK)
		return TRUE;
	return FALSE;
}

// check char is wall or block
int isWallBlock(char ch){
	if(isBlock(ch) || isWall(ch))
		return TRUE;
	return FALSE;
}

// check char is blank
int isBlank(char ch){
	if(ch == BLANK)
		return TRUE;
	return FALSE;	
}
