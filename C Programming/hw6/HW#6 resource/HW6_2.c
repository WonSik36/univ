#include <stdio.h>
#include <string.h>

#include <windows.h>
#include <conio.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24

void clrscr(void);			// clear the screen
void gotoxy(int x, int y);	// move cursor to (x, y)

void ExtendString(char str[], int newLen);
void ShiftString(char str[]);

int main()
{
	char message[SCREEN_WIDTH + 1];
	char key = 0;

	clrscr();
	gotoxy(1, 1);
	printf("Input a long message : ");
	gets(message);
	printf("Press ESC to quit.");

	ExtendString(message, SCREEN_WIDTH);
	
	do {
		gotoxy(1, SCREEN_HEIGHT / 2);
		printf(message);
		ShiftString(message);

		if(kbhit())
			key = getch();
			
		Sleep(50);
	} while(key != 27);			// 27 is the ASCII code of ESC
	
	clrscr();
	gotoxy(1, 1);
	printf("Bye!\n");

	return 0;
}

void ExtendString(char str[], int newLen)
// Appends ' 's at the end of str to make its length newLen
{	
	//		get current length of str
	int i=0, length=strlen(str);
	//		append ' ' at the end of str (newLen - curLen) times
	for(i=length;i<80;i++)
		str[i]=' ';
	//append the null character ('\0') at the end of str
	str[80]='\0';

	return;
}

void ShiftString(char str[])
// Shifts all the characters in str one step right
// The last character should move to str[0].
{
	int length=0, i=0;
	int temp=0;
	// 	get the length of str
	length = strlen(str);
	// 	save the last character in a temporary variable.
	temp=str[79];
	// 	for each i (in reverse order from len - 1 to 0)
	for(i=length-1;i>0;i--)
	{
	//	copy (i-1)-th character to i-th position
	str[i]=str[i-1];
	}
	//  copy the saved last character to str[0]
	str[0]=temp;
	return;
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
