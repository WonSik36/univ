/** File: HeapSort.cpp */
/*On my honor, I pledge that I have neither received nor provided improper
assistance in the completion of this programming assignment. Signed: Wonsik Cheung*/
/* This implements the heap sort algorithm (in-place). 
 * A given arbitrary input array goes through two passes. 
 * 1st pass: heap construction (heapify)
 * 2nd pass: successively remove the root(max) and 
 *           add it to the end of array
 * The follwing outputs show how the algorithm flows.
  NOTE: N=?? k=? .... lines are outputs at the end of each sink()

  Unsorted:a[] S O R T E X A M P L E
    N=10  k=5: S O R T E X A M P L E
    N=10  k=4: S O R T L X A M P E E
    N=10  k=3: S O R T L X A M P E E
    N=10  k=2: S O X T L R A M P E E
    N=10  k=1: S T X P L R A M O E E
    N=10  k=0: X T S P L R A M O E E
 Heap ordered: X T S P L R A M O E E
    N= 9  k=0: T P S O L R A M E E
    N= 8  k=0: S
    N= 7  k=0: R 
    N= 6  k=0: P 
    N= 5  k=0: O 
    N= 4  k=0: M 
    N= 3  k=0: L 
    N= 2  k=0: E 
    N= 1  k=0: E 
    N= 0  k=0: A
    Sorted:a[] A E E L M O P R S T X
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
	Key t = a[i];	a[i] = a[j];		a[j] = t;
}

void swim(Key *a, int k) {
	while (k > 0 && less(a, (k-1) / 2, k)) {
		swap(a, (k-1) / 2, k);
		k =(k-1) / 2;
	}
}

void sink(Key *a, int k, int N) {
	int kk = k;
	while (2 * k + 1<= N) {
		int j = 2 * k + 1;
		if (j < N  && less(a, j, j + 1)) j++;
		if (!less(a, k, j)) break;
		swap(a, k, j);
		k = j;
	}

	printf("   N=%2d  k=%d: ", N, kk);
	for (k = 0; k <= N; k++) printf("%c ", a[k]);
	printf("\n");
	
}

void HeapSort(Key *a, int N) {
	int k;
	// 1st pass: restore the max heap property

	for(int i = (N-2)/2 + 1; i>=0; i--)
		sink(a, i, N-1);
	
	printf("Heap ordered: "); 
	for (k = 0; k < N; k++) printf("%c ", a[k]);
	printf("\n");

	// 2nd pass: get the max out (from root to the end)
	for(int i = 1; i<=N-1; i++){
		swap(a, 0, N - i);
		sink(a, 0, N - i -1);
	}
}

// Don't change the main function.
void main()	{
	//Key a[] = { 20, 16, 18, 14, 8, 15, 1, 5, 9, 7 };
	Key a[] = { 'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E' };	
	int i;
	int N = sizeof(a) / sizeof(a[0]);

	printf("Unsorted:a[i] ");
	for (i = 0; i < N; i++) printf("%c ", a[i]);
	printf("\n");

	HeapSort(a, N);
	printf("  Sorted:a[i] ");
	for (i = 0; i < N; i++) printf("%c ", a[i]);
	printf("\n");
}
