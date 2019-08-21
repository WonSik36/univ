#include <stdio.h>

#define MaxWidth 13
#define MaxHeight 13

// draws a magic square of odd number
int main()
{
	int n = 0;
	int nextx=0,nexty=0;
	int x = 0, y = 0;
	int width = 5;					// default width
	int size = 0;
	int square[MaxHeight][MaxWidth];
	int sum=0;
	
	// read the width of the magic square
	do {
		printf("Input the width of magic square (3~13, default = 5): ");
		scanf("%d", &width);
	} while(width % 2 == 0 || width > MaxWidth || width < 3);

	//create magic square
	//fill square with 0's
	for(x=0;x<width;x++)
		for(y=0;y<width;y++)
			square[x][y]=0;
	//initialize (x, y) with (width - 1, width / 2)
	x=width-1, y=width/2;
	//set size = width * width
	size=width*width;
	//repeat for n from 1 to size
	for(n=1;n<=size;n++)
	{
		//	set square[y][x] by n
		square[y][x]=n;
	//	set (nextx, nexty) by the lower right diagnal neighborhood of (x, y)
		if(x==width-1)
			nextx=0;
		else
			nextx=x+1;
		if(y==width-1)
			nexty=0;
		else
			nexty=y+1;
	//	if square[nexty][nextx] is not filled yet,
	//		update (x,y) with (nextx, nexty)
		if(square[nexty][nextx]==0)
			x=nextx,y=nexty;
	//	otherwise
	//		update (x, y) with (x - 1, y)
		else
			x=x-1,y=y;
	}


	// display the matrix with row sums.
	printf("\n");
	for(y=0;y<width;y++){
		sum=0;
		for(x=0;x<width;x++){
			printf("%5d",square[y][x]);
			sum+=square[y][x];
		}
		printf(" =%5d\n",sum);
	}
	
	for(n=0;n<width;n++)
		printf("=====");
	printf("\n");
	
	//dispalay the matrix with column sums
	for(x=0;x<width;x++){
		sum=0;
		for(y=0;y<width;y++)
			sum+=square[y][x];
		printf("%5d",sum);
	}
	printf("\n");
	return 0;
}
