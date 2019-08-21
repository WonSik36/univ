#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <unistd.h>
#include <pthread.h>

#include <time.h>

#define TRUE 1
#define FALSE 0
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

int gThreadContinue = TRUE;
pthread_mutex_t mutex;

void DrawBar(int x, int y, int len, char c);
void PrintXY(int x, int y, const char * format, ...);
void gotoXY(int x, int y);
void clrscr();
void* MoveBarThreadFn(void* vpParam);

typedef struct{
	int x, y;
	int dx;
	int len;
	int interval;
}Barinfo;

int main(int argc, char * argv[]){
	int noThread = 5;
	int t = 0;
	int ret = 0;
	pthread_t * tid = NULL;
	Barinfo* barinfo = NULL;

	srand(time(NULL));

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
		printf("Failed to initialize mutex. (file %s, line %d)\n", __FILE__, __LINE__);
		exit(-1);
	}

	//Allocate tid and barinfo
	tid = (pthread_t*)malloc(sizeof(pthread_t)*noThread);
	if(tid == NULL){
		printf("Failed to allocate memory to thread\n");
		return -1;
	}
		
	barinfo = (Barinfo*)malloc(sizeof(Barinfo)*noThread);
	if(barinfo == NULL){
		printf("Failed to allocate memory to bar information\n");
		return -1;
	}
	
	for(t=0; t<noThread; t++){
		//initialzie barinfo[t]
		barinfo[t].x = 1;		
		barinfo[t].y = (SCREEN_HEIGHT-1)/noThread*t + 2;		
		barinfo[t].dx = 1;		
		barinfo[t].len = rand()%6+5;		
		barinfo[t].interval = (rand()%100+1)*1000;

		//launch a thread to animate t-th bar
		pthread_create(&tid[t], NULL, MoveBarThreadFn, (void*)&barinfo[t]);
	}

	PrintXY(0,0,"%s","Press Enter button to quit\n");
	
	getchar();

	gThreadContinue = 0;
	
	for(t=0; t<noThread; t++)
		pthread_join(tid[t], NULL);
	
	clrscr();
	PrintXY(0,0,"%s","Good Bye~\n");

	free(tid);
	free(barinfo);
	
	pthread_mutex_destroy(&mutex);

	return 0;
}

void* MoveBarThreadFn(void* vpParam){
	Barinfo * barinfo = (Barinfo*) vpParam;

	DrawBar(barinfo->x, barinfo->y, barinfo->len, '=');
	usleep(barinfo->interval);

	while(gThreadContinue){
		DrawBar(barinfo->x, barinfo->y, barinfo->len, ' ');

		if((((barinfo->x)+(barinfo->dx)) < 1) || ((barinfo->x)+(barinfo->dx)+(barinfo->len) > SCREEN_WIDTH))
			barinfo->dx *= -1;

		barinfo->x += barinfo->dx;
		DrawBar(barinfo->x, barinfo->y, barinfo->len, '=');
	
		usleep(barinfo->interval);
	}
	pthread_exit(0);
}

void DrawBar(int x, int y, int len, char c){
	pthread_mutex_lock(&mutex);
	
	gotoXY(x, y);
	for(int i =0;i<len;i++)
		putchar(c);

	gotoXY(1,1);

	fflush(stdout);

	pthread_mutex_unlock(&mutex);
}

void PrintXY(int x, int y, const char * format, ...){
	va_list vl;

	pthread_mutex_lock(&mutex);

	gotoXY(x,y);

	va_start(vl, format);
	vprintf(format, vl);
	va_end(vl);

	fflush(stdout);

	pthread_mutex_unlock(&mutex);
}

void gotoXY(int x, int y){
	printf("%c[%d;%df",0x1B,y,x);
}

void clrscr(){
	system("clear");
	gotoXY(1,1);
}
