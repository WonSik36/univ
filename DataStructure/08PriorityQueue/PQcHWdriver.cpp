
// file: PQcDriver.cpp
/**
*  This program test and verify the priority queue implmentation based on
*  heap data structure. *  The PQi or PQc represents a priority queue of 
*  int or char key, respectively.
*  It supports the usual insert and delete-the-maximum operations,
*  along with methods for peeking at the maximum key, testing if the priority
*  queue is empty, and iterating through the keys.
*
*  This implementation uses a binary heap or PQ.cpp
*  The insert and delete-the-maximum operations take logarithmic amortized time.
*  The max, size, and isEmpty operations take constant time.
*  Construction takes time proportional to the specified capacity or
*  the number of items used to initialize the data structure.
*  It uses successive doulbing to increase the memory as the number of nodes
*  increases. Similarly, it deallocates its memory dynamically as the nodes
*  get removed. A one - based and one dimensional array is used to simplify
*  parent and child calculations.
*
*  @author Youngsup Kim
*  2014/04/01	YSK	Creation
*
*/
#include "PQc.h"
#include "PQ.h"

void testInsert(pq p, Key a[], int aSize) {
	char *b;
	int i;
	
	for (i = 0; i < aSize; i++) insertMax(p, a[i]);
	verify(isMaxHeap(p) == true, "It is not a max Heap.");
	showHeap(p);
	printf("toString: %s\n", b = toString(p)); free(b);
	printf("\n");

	insertMax(p, 'S');
	verify(isMaxHeap(p) == true, "It is not a max Heap.");
	showHeap(p);
	printf("toString: %s\n", b = toString(p)); free(b);
	printf("\n");
}

void testDelete(pq p) {
	char *b;
	int i;

	deleteMax(p);
	verify(isMaxHeap(p) == true, "It is not a max Heap.");
	showHeap(p);
	printf("toString: %s\n", b = toString(p)); free(b);
	printf("\n");

	deleteMax(p);
	showHeap(p);
	printf("toString: %s\n", b = toString(p)); free(b);
	verify(isMaxHeap(p) == true, "It is not a max Heap.");
	printf("\n");

	insertMax(p, 'S');
	verify(isMaxHeap(p) == true, "It is not a max Heap.");
	showHeap(p);
	printf("toString returns %s\n", b = toString(p)); free(b);
	printf("\n");

	// delete all the nodes 
	int aSize = size(p);
	for (i = 0; i < aSize; i++) {
		printf("deleted: %c\n", deleteMax(p));			//// Key dependent ////
		showHeap(p);
		printf("toString: %s\n", b = toString(p)); free(b);
		verify(isMaxHeap(p) == true, "It is not a max Heap.");
		printf("\n");
	}
}

void testHeapify() {
	char *b;	
	int aSize;
	Key cbt[] = { 'B', 'D', 'E', 'G', 'C', 'J', 'H', 'A', 'I', 'F'}; 
	//Key cbt[] = { 2, 4, 5, 7, 3, 10, 8, 1, 9, 6 };
	aSize = sizeof(cbt) / sizeof(cbt[0]);

	pq p = newCBT(cbt, aSize);		// create a complete binary tree
	showHeap(p);
	printf("toString: %s\n", b = toString(p)); free(b);
	verify(isMaxHeap(p) == true, "It is not a max Heap.");
	printf("\n");

	printf("Let's heapify()\n");
	heapify(p);
	showHeap(p);
	printf("toString: %s\n", b = toString(p)); free(b);;
	verify(isMaxHeap(p) == true, "It is not a max Heap.");
	printf("\n");

	freePQ(p);
}

//////////////////////////////////////////////////////////////////////////////
// PQcDriver - test the implementation of a max/min PQ data structure //
// Key  a[] = { 20, 16, 18, 14, 8, 15, 1, 5, 9, 7 };
//////////////////////////////////////////////////////////////////////////////
void main(int argc, char *argv[]) {
	Key a[] = { 'T', 'P', 'R', 'N', 'H', 'O', 'A', 'E', 'I', 'G' }; //// Key dependent ////
	int aSize = sizeof(a) / sizeof(a[0]);
	pq p;

	// NOTE: newPQ(128) should be replaced by newPQ(1) to test the 
	// successive memory doubling, or deallocation. 
	p = newPQ(2);
	verify(p != NULL, "newPQ() does not work.");
	verify(isEmpty(p) == true, "isEmpty() does not work.");

	testInsert(p, a, aSize);
	testDelete(p);
	freePQ(p);

	testHeapify(); 

	printf("End of PQc - Good work!\n");
}

