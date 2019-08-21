/* 테트리스와 슈팅게임을 합친 게임을 만드려고 한다.
오른쪽 슈팅게임에서 넘어오는 파괴된 블록을 기준으로 테트리스의 블록을 만든다.
참조: 윤성우의 열혈자료구조 ch.7 (큐)
      네이버 지식인(테트리스)*/
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<limits.h>
#include<time.h>
#include<stdlib.h>

#define TRUE	1
#define FALSE	0
#define EMPTY 0
#define BLOCK 1
#define MISILE -2
#define AIRCRAFT 2
#define WALL 3
#define DEADBLOCK
#define SPACE 32

typedef struct point{
	int x;
	int y;
}Point;

//슈팅게임에서 넘어오는 자료의 저장및 출력을 위한 큐
typedef struct _tQueue
{
	int front;
	int rear;
	int queArr[100];
} Queue;

//슈팅게임 비행기 표시
Point SAirc[4]={-1,0,0,-1,0,0,1,0};

//테트리스 블록 선언
Point Shape[6][4][4]={
	//막대기형
	{ {0,0,1,0,2,0,-1,0}, {0,0,0,1,0,-1,0,-2}, {0,0,1,0,2,0,-1,0}, {0,0,0,1,0,-1,0,-2} },
	//네모형
	{ {0,0,1,0,0,1,1,1}, {0,0,1,0,0,1,1,1}, {0,0,1,0,0,1,1,1}, {0,0,1,0,0,1,1,1} },
	//뫼산형
	{ {0,0,-1,-1,0,-1,1,0}, {0,0,-1,0,-1,1,0,-1}, {0,0,-1,-1,0,-1,1,0}, {0,0,-1,0,-1,1,0,-1} },
	//쇠파이프형
	{ {0,0,-1,0,1,0,-1,-1}, {0,0,0,-1,0,1,-1,1}, {0,0,-1,0,1,0,1,1}, {0,0,0,-1,0,1,1,-1} },
	//역쇠파이프형
	{ {0,0,1,0,-1,0,1,-1}, {0,0,0,1,0,-1,-1,-1}, {0,0,1,0,-1,0,-1,1}, {0,0,0,-1,0,1,1,1} },
	//꽈배기형
	{ {0,0,-1,0,1,0,0,1}, {0,0,0,-1,0,1,1,0}, {0,0,-1,0,1,0,0,-1}, {0,0,-1,0,0,-1,0,1} } 
};

//큐관련 함수
void QueueInit(Queue * pq);
int QIsEmpty(Queue * pq);
void Enqueue(Queue * pq, int data);
int Dequeue(Queue * pq);
int NextPosIdx(int pos);

//화면 함수
void clrscr(void);
void gotoxy(int x, int y);

//슈팅게임 관련 함수
void Shoot(void);
void ShootMakeWall(int (*arr)[30]);
void MoveAirCraft(int (*arr)[30],Point* p, int key);
void ShootView(int (*arr)[30]);
void MoveBar(int (*arr)[30]);
void Misile(int (*arr)[30], Point a);
void drawScreen(int(*arr)[12]);

//테트리스 관련 함수
void printScore(void);
int eraseBrick(int(*arr)[12]);
int processKey(int(*arr)[12]);
int moveDown(int(*arr)[12]);
int colCheck(int(*arr)[12], int x, int y, int b, int r);
void printBrick(int show);

long long Ptime=0;
Queue TetrisQueue;
int bdelay[3]={0,0,0};
int mdelay=3, cnt=0;
int bar[3][2][3]={{BLOCK,BLOCK,BLOCK,BLOCK,BLOCK,BLOCK},
		{BLOCK,BLOCK,BLOCK,BLOCK,BLOCK,BLOCK},
	{BLOCK,BLOCK,BLOCK,BLOCK,BLOCK,BLOCK}};
int score=0;
int x=0,y=0;
int r=0;
int Brick=0;

int main(void){
	int n=0;
	int i=0,j=0;
	int shootarr[20][30]={0};
	int tetrisarr[22][12]={0};
	Point aircraft={15,17};
	char c=0;
	Queue *pq;

	srand((int)time(NULL));
	QueueInit(&TetrisQueue);

	//슈팅게임 시작
	ShootMakeWall(shootarr);
	while(n<3){
		bdelay[n]=rand()%5+3;
		n++;
	}
	for(n=0;n<4;n++)
		shootarr[aircraft.y+SAirc[n].y][aircraft.x + SAirc[n].x]=AIRCRAFT;
	

		while(c!=27){
		
			if(Ptime==LONG_MAX){
				clrscr();
				gotoxy(0,0);
				printf("Time End!!\n");
				return ;
				}
		
		if(kbhit())
			c=getch();
		
		MoveBar(shootarr);
		MoveAirCraft(shootarr,&aircraft,c);
		ShootView(shootarr);
		Misile(shootarr, aircraft);

		pq=&TetrisQueue;
		if(NextPosIdx(pq->rear)==pq->front)
			break;
		Ptime++;
		Sleep(50);
			}

		//테트리스 시작
		for (i=0;i<22;i++){
			for(j=0;j<12; j++){
				tetrisarr[i][j]=EMPTY;
				if(i==0) tetrisarr[i][j]=WALL;
				if(i==21) tetrisarr[i][j]=WALL;
				if(j==0) tetrisarr[i][j]=WALL;
				if(j==11) tetrisarr[i][j]=WALL;
			}
		}
	drawScreen(tetrisarr);
	c=0;

		while(1){
		if(Ptime==LONG_MAX){
			clrscr();
			gotoxy(0,0);
			printf("Time End!!\n");
			return ;
			}
		printScore();
		x=10 /2;
		y=3;
		r=0;
		printScore();
		Brick=Dequeue(&TetrisQueue);
		cnt=0;

			while(1){
				
				cnt++;

				if(cnt==20){
						if(moveDown(tetrisarr))
							break;
						cnt=0;
				}
				if(processKey(tetrisarr))
						break;
					Sleep(30);
					}
					while(TRUE){
						if(!eraseBrick(tetrisarr)) break;
					}
		Ptime++;
		Sleep(50);
	
		}
	gotoxy(0,0);
	printf("Bye!!\n");
	return 0;
}

//슈팅게임 테두리
void ShootMakeWall(int (*arr)[30])
{
	int n=0;

	for(n=0;n<30;n++){
		arr[0][n]=WALL;
		arr[19][n]=WALL;
	}
	for(n=0;n<20;n++){
		arr[n][0]=WALL;
		arr[n][29]=WALL;
	}

	return;
}

//슈팅게임 비행기 움직이기
void MoveAirCraft(int (*arr)[30],Point* p, int key)
{
	int oldx=p->x;
	int n=0;

	switch(key){
		case'j':
			if(p->x==2)
				p->x=2;
			else
				p->x--;
			break;
		case'l':
			if(p->x==27)
				p->x=27;
			else
				p->x++;
			break;
	}

	for(n=0;n<4;n++)
		arr[17+SAirc[n].y][oldx+SAirc[n].x]=EMPTY;
	for(n=0;n<4;n++)
		arr[17+SAirc[n].y][p->x + SAirc[n].x]=AIRCRAFT;

	return;
}

//화면 비우기
void clrscr(void)			// clear the screen
{
	COORD Cur = {0, 0};
	unsigned long dwLen = 0;

	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 80*25, Cur, &dwLen);
}

//커서 움직이기
void gotoxy(int x, int y)	// move cursor to (x, y)
{
	COORD Pos = {x, y};

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//슈팅게임 화면에 나타내기
void ShootView(int (*arr)[30])
{
	int i=0,j=0;
	int n=0;
	Point m[30];

	for(j=2;j<22;j++){
		for(i=48;i<78;i++){
			
			if(arr[j-2][i-48]==MISILE){
				m[n].x=i-48, m[n].y=j-2; 
				n++;
			}

			gotoxy(i,j);
			switch(arr[j-2][i-48]){
			case EMPTY:
				putchar(' ');
				break;
			case BLOCK:
				putchar('*');
				break;
			case MISILE:
				putchar('!');
				break;
			case AIRCRAFT:
				putchar('A');
				break;
			case WALL:
				putchar('0');
				break;
			default:
				putchar(' ');
				break;
			}
		}
	}
	n--;
	for(;n>=0;n--){
		if(arr[(m[n].y)-1][m[n].x]!=WALL){
			arr[m[n].y-1][m[n].x] +=arr[(m[n].y)][m[n].x];
		}
		arr[m[n].y][m[n].x]=EMPTY;
	}
	return;
}

//슈팅게임속 바 움직이기
void MoveBar(int (*arr)[30])
{
	int i=0, j=0;
	int a=0, b=0;
	static int x[3]={28,28,28}, y[3]={1,4,7};
	int n=0;
	int data[3]={0};

	for(n=0;n<3;n++){
		
		for(j=0;j<2;j++){
			for(i=0;i<3;i++){
				if(arr[y[n]+j][x[n]+i+1]==-1)
					bar[n][j][i]=EMPTY;
			}}
		if(Ptime%bdelay[n]==0){
			y[n]=1+3*n;
		for(j=0;j<2;j++){
			for(i=0;i<3;i++){
					if((x[n]+i)>0&&(x[n]+i)<29)
					{
							arr[y[n]+j][x[n]+i]=bar[n][j][i];
							if(arr[y[n]+j][x[n]+i+1]!=WALL)
								arr[y[n]+j][x[n]+i+1]=EMPTY;
					}
			}
		
		}if(x[n]==-2)
				{
				arr[y[n]][1]=EMPTY;
				arr[y[n]+1][1]=EMPTY;
			}
		x[n]--;
		}
		if(x[n]==-3){
			
			for(a=0;a<2;a++)
				for(b=0;b<3;b++)
					data[n]+=bar[n][a][b];
			
			x[n]=28;
			bdelay[n]=rand()%5+3;
			
			for(a=0;a<2;a++)
				for(b=0;b<3;b++)
					bar[n][a][b]=BLOCK;
			if(data[n]==6)
				data[n]=5;
			Enqueue(&TetrisQueue, data[n]);
			data[n]=0;
		}
	}
	return;
}

//슈팅 게임 미사일 초기값 설정
void Misile(int (*arr)[30], Point a)
{
	Point m={0};

	if(Ptime%mdelay==0)
	{
		m.x=a.x, m.y=a.y-2;
		arr[m.y][m.x]=MISILE;
	}
}

//테트리스 점수 표시
void printScore(){
	gotoxy(30,10);
	printf("Score : %d",score);
}
int eraseBrick(int(*arr)[12]){
	int isErase=FALSE,isFull;
	int i=0,j=0,k=0;
	
	for(i=20;i>0;i--){
		isFull=TRUE;
		for(j=1;j<=10;j++){
			if(arr[i][j]==EMPTY)
				isFull=FALSE;
		}
		if(isFull){
			isErase=TRUE;
			for(j=i;j>1;j--){
				for(k=1;k<=10;k++){
					arr[j][k]=arr[j-1][k];
				}
			}
			drawScreen(arr);
			score+=10;
		}
	}
	return isErase;
}
int processKey(int(*arr)[12]){
	char c=0;
	if(kbhit())
		c=getch();
		if(c== SPACE){
			while(TRUE){
				if(!colCheck(arr,x,y+1,Brick,r))
					moveDown(arr);
				else break;
			}
		}
		if(c== 'a' && !colCheck(arr,x-1,y,Brick,r)){
			printBrick(FALSE);
			x--;
			printBrick(TRUE);
			
		}
		if(c== 'd' && !colCheck(arr,x+1,y,Brick,r)){
			printBrick(FALSE);
			x++;
			printBrick(TRUE);
		}
		if(c== 's' ){
			if(moveDown(arr)){
				cnt=0;
				return moveDown(arr);
			}
		}
		if(c== 'w' && !colCheck(arr,x,y,Brick,(r+1)%4)){
			printBrick(FALSE);
			r++;
			r%=4;
			printBrick(TRUE);
		}
	
	return FALSE;
}

//테트리스 블록 움직이기
int moveDown(int(*arr)[12]){
	int i;
	
	if(colCheck(arr,x,y+1,Brick,r)){
		for(i =0 ;i<4;i++){
			arr[Shape[Brick][r][i].y+y+1][Shape[Brick][r][i].x+x+1]=BLOCK;
		}
		return TRUE;
	}
	
	printBrick(FALSE);
	y++;
	printBrick(TRUE);

	return FALSE;
}

//테트리스 현재 블록의 아래 확인
int colCheck(int(*arr)[12], int x, int y, int b, int r){
	int i=0;

	for(i=0;i<4;i++){
		if(arr[Shape[b][r][i].y+y+1][Shape[b][r][i].x+x+1] != EMPTY){
			return TRUE;
		}
	}
	return FALSE;
}

//블록 움직이기
void printBrick(int show){
	int b;
	int i;
	if(show==TRUE){
		b=BLOCK;
	}
	else{
		b=EMPTY;
	}
	for(i=0;i<4;i++){
		gotoxy((x+1+Shape[Brick][r][i].x)*2,(y+1+Shape[Brick][r][i].y));
		putchar(b==BLOCK ? '#' : ' ');
	}
}

//테트리스 화면에 나타내기
void drawScreen(int(*arr)[12]){
	char b;
	int i,j;

	for (i=0;i<22;i++){
		for(j=0;j<12; j++){
			gotoxy(j*2,i);
			switch(arr[i][j]){
			case EMPTY:
				putchar(' ');
				break;
			case BLOCK:
				putchar('#');
				break;
			case WALL:
				putchar('0');
				break;
			default:
				putchar(' ');
				break;
			}
		}
	}
}

//큐 초기화
void QueueInit(Queue * pq)
{
	pq->front = 0;
	pq->rear = 0;
	return;
}

//큐 비였는지 확인
int QIsEmpty(Queue * pq)
{
	if(pq->front == pq->rear)
		return TRUE;
	else
		return FALSE;
}

//큐의 효율적 사용을 위한 함수
int NextPosIdx(int pos)
{
	if(pos == 99)
		return 0;
	else
		return pos+1;
}

//큐에 값 저장
void Enqueue(Queue * pq, int data)
{
	if(NextPosIdx(pq->rear) == pq->front)
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	pq->rear = NextPosIdx(pq->rear);
	pq->queArr[pq->rear] = data;
}

//큐에 값 내보내기
int Dequeue(Queue * pq)
{
	if(QIsEmpty(pq))
	{
		return rand()%6;
	}

	pq->front = NextPosIdx(pq->front);
	return pq->queArr[pq->front];
}

