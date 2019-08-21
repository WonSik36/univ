/** File: HeapSortN.cpp */
/* This implements the heap sort algorithm (in-place).
* A given arbitrary input array goes through two passes.
* 1st pass: heap construction (heapify)
* 2nd pass: successively remove the root(max) and
*           add it to the end of array
* The follwing outputs show how the algorithm flows.
NOTE: This implementation does not sort the first element in the array.
NOTE: N=?? k=? .... lines are outputs at the end of each sink()
Unsorted:a[]: S O R T E X A M P L E
   N=11  k=6: S O R T E X A M P L E
   N=11  k=5: S O R T L X A M P E E
   N=11  k=4: S O R T L X A M P E E
   N=11  k=3: S O X T L R A M P E E
   N=11  k=2: S T X P L R A M O E E
   N=11  k=1: X T S P L R A M O E E
Heap ordered: X T S P L R A M O E E
   N=10  k=1: T P S O L R A M E E
   N= 9  k=1: S
   N= 8  k=1: R
   N= 7  k=1: P
   N= 6  k=1: O     [A Part of Homework]
   N= 5  k=1: M
   N= 4  k=1: L
   N= 3  k=1: E
   N= 2  k=1: E
   N= 1  k=1: A
  Sorted:a[]: A E E L M O P R S T X
*
* Author: Youngsup Kim
* 2014/04/30	YSK	Creation
*/

#include <stdio.h>
#include "PQc.h"

//////////// helper functions to restore the PQ invariant ///////////
int less(Key *a, int i, int j) {
	return a[i] < a[j];
}

void swap(Key *a, int i, int j) {
	Key t = a[i];
	a[i] = a[j];
	a[j] = t;
}

void swim(Key *a, int k) {
	while (k > 1 && less(a, k / 2, k)) {
		swap(a, k / 2, k);
		k = k / 2;
	}
}

void sink(Key *a, int k, int N) {
	int kk = k;
	while (2 * k <= N) {
		int j = 2 * k;
		if (j < N && less(a, j, j + 1)) j++;
		if (!less(a, k, j)) break;
		swap(a, k, j);
		k = j;
	}

	printf("   N=%2d  k=%d: ", N, kk);
	for (k = 1; k <= N; k++) printf("%c ", a[k]);
	printf("\n");
}

void HeapSort(Key *a, int N) {
	int k;
	printf("1st pass begins:\n");
	// 1st pass: restore the max heap property
	// Place your code here (start at the last internal node)


	printf("Heap ordered: ");
	for (k = 1; k <= N; k++) printf("%c ", a[k]);
	printf("\n");

	// 2nd pass: get the max out (from root to the end)
	// Place your code here 
	printf("2nd pass begins:\n");


}

// Don't change the main function.
void main()	{
	//Key a[] = { -1, 20, 16, 18, 14, 8, 15, 1, 5, 9, 7 };
	//Key a[] = { '0', 'T', 'P', 'R', 'N', 'H', 'O', 'A', 'E', 'I', 'G' };
	Key a[] = { '0', 'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E' };	// first element unsorted
	int i;
	int N = sizeof(a) / sizeof(a[0]) - 1;

	printf("Unsorted:a[]: "); 
	for (i = 1; i <= N; i++) printf("%c ", a[i]);
	printf("\n");
	
	HeapSort(a, N);
	printf("  Sorted:a[]: ");
	for (i = 1; i <= N; i++) printf("%c ", a[i]);
	printf("\n");
}



