#include <stdio.h>

#define MaxWidth 13
#define MaxHeight 13

// draws a magic square of odd number
int main()
{
	int n = 0;
	
	int x = 0, y = 0;
	int width = 5;					// default width
	int size = 0;
	int square[MaxHeight][MaxWidth];
	
	// read the width of the magic square
	do {
		printf("Input the width of magic square (3~13, default = 5): ");
		scanf("%d", &width);
	} while(width % 2 == 0 || width > MaxWidth || width < 3);

/*	TO DO: create magic square
	fill square with 0's
	initialize (x, y) with (width - 1, width / 2)
	set size = width * width

	repeat for n from 1 to size
	{
		set square[y][x] by n
		set (nextx, nexty) by the lower right diagnal neighborhood of (x, y)
		
		if square[nexty][nextx] is not filled yet,
			update (x,y) with (nextx, nexty)
		otherwise
			update (x, y) with (x - 1, y)
	}
*/

	// TO DO: display the matrix with row/column sums.

	return 0;
}
