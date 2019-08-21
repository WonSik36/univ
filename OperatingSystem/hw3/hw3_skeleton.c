#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <unistd.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

int gThreadContinue = TRUE;		// global var to control threads
pthread_mutex_t mutex;			// mutex for display routines

void DrawBar(int x, int y, int len, char c);
void PrintXY(int x, int y, const char *format, ...);
void gotoxy(int x, int y);
void clrscr();

typedef struct {
	// TO DO: complete this structure
} BarInfo;

void* MoveBarThreadFn(void *vpParam);

int main(int argc, char *argv[])
{
	int noThread = 5;		// default 
	int t = 0;
	int ret = 0;
	pthread_t *tid = NULL;
	BarInfo *barInfo = NULL;

	if(argc > 1){
		noThread = atoi(argv[1]);
		if(noThread == 0){
			printf("Usage: %s <# of threads>\n", argv[0]);
			return -1;
		}
	}

	clrscr();
	ret = pthread_mutex_init(&mutex, NULL);
	if(ret != 0){
		printf("failed to initialize mutex. (file %s, line %d)\n", __FILE__, __LINE__);
		exit(-1);
	}

	// TO DO: allocate tid and barInfo

	
	for(t = 0; t < noThread; t++){
		// TO DO: initialize barInfo[t]

		// TO DO: launch a thread to animate t-th bar.
	}

	/* TO DO:
		Wait for Enter key
		Terminate threadss by assinging zero to gThreadContinue;
		Wait for all children threads
		Clear screen
		Print a good-bye message
		Deallocate memory
	*/

	return 0;
}

void* MoveBarThreadFn(void *vpParam)
{
	// TO DO: fill this function
}

void DrawBar(int x, int y, int len, char c)
{
	pthread_mutex_lock(&mutex);

	gotoxy(x, y);
	for(int i = 0; i < len; i++)
		putchar(c);

	gotoxy(1, 1);

	fflush(stdout);

	pthread_mutex_unlock(&mutex);
}

void PrintXY(int x, int y, const char *format, ...)
{
	va_list vl;

	pthread_mutex_lock(&mutex);

	gotoxy(x, y);

	va_start(vl, format);
	vprintf(format, vl);
	va_end(vl);

	fflush(stdout);

	pthread_mutex_unlock(&mutex);
}

void gotoxy(int x, int y)
{
	printf("%c[%d;%df",0x1B,y,x);
}

void clrscr()
{
	system("clear");
	gotoxy(1, 1);
}
