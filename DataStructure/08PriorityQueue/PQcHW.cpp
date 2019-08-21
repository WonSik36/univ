// file: PQc
/**
*  The PQi or PQc represents a priority queue of int or char key, respectively.
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

#include "PQc.h"	// determine PQ key data type
#include "PQ.h"		// PQi.h or PQc.h must proceed. 

/**
* instantiate a new pq and return the new pq pointer.
*/
pq newPQ(int capacity) {
	pq p = (pq)malloc(sizeof(PQ));
	verify(p != NULL, "PQ: cannot allocate memory.");

	p->N = 0;
	p->capacity = capacity < 2 ? 2 : capacity;
	p->node = (Key *)malloc(sizeof(Key)* p->capacity);
	verify(p->node != NULL, "PQ: cannot allocate memory.");
	return p;
}

/**
* deallocate a PQ.
*/
void freePQ(pq p) {
	if (p == NULL) return;
	free(p->node);
	free(p);
}

/**
* return the number of items in PQ
*/
int size(pq p) {
	return p->N;
}

/**
* return level based on num of nodes
*/
int level(int n){
	if(n==0) return 0;
	int level = 1;
	
	while(n>1){
		n/=2;
		level++;
	}
	
	return level;
}

/**
* return its capacity (array size)
*/
int capacity(pq p){
	return p->capacity;
}

/**
* resize the PQ array data structure
* If successfully resize, return true/ else return false
*/
int resize(pq p, int newCapacity) {
	// realloc() : The contents of the block are unchanged up to the shorter 
	// of the new and old sizes, although the new block can be in a different location.
	p->node = (Key*)realloc(p->node, newCapacity * sizeof(Key));
	p->capacity = newCapacity;
	if(p->node == NULL)
		return false;
	else return true;
}

/**
* Is this pq full?
* @return true if this pq is full; false otherwise
*/
int isFull(pq p) {
	return (p->N == p->capacity - 1) ? true : false;
}

/**
* Is this pq empty?
* @return true if this pq is empty; false otherwise
*/
int isEmpty(pq p) {
	return (p->N == 0) ? true : false;
}

/**
* inserts a new key to the priority queue.
* @param key the new key to add to the proirity queue
* @returns key on success, returns key^0xFFFF on failure
*/
int insertMax(pq p, Key key) {
	if (isFull(p)) 
		resize(p, p->capacity * 2);
	if(p==NULL) return 65535;		//0xFFFF = 65535

	p->node[++p->N] = key;			// add key and swim up to maintain PQ invariant
	swim(p, p->N);
	return key;
}

/**
* Removes and returns a largest key on the priority queue.
* @returns a largest key on the priority queue
* @returns INT_MIN if priority queue is empty.
*/
int deleteMax(pq p) {
	if (isEmpty(p)) return INT_MIN;

	int maxKey = p->node[1];
	swap(p, 1, p->N--);
	sink(p, 1);

	if ((p->N > 0) && (p->N == p->capacity / 4  -1))
		resize(p,p->capacity / 4);
	return maxKey;
}

//////////// helper functions to restore the PQ invariant ///////////
int less(pq p, int i, int j) {
	return p->node[i] < p->node[j];
}

void swap(pq p, int i, int j) {
	Key t = p->node[i];
	p->node[i] = p->node[j];
	p->node[j] = t;
}

void swim(pq p, int k) {
	while (k > 1 && less(p, k / 2, k)) {
		swap(p, k / 2, k);
		k = k / 2;
	}
}

void sink(pq p, int k) {
	while (2 * k <= p->N) {
		int j = 2 * k;
		if (j < p->N && less(p, j, j + 1)) j++;
		if (!less(p, k, j)) break;
		swap(p, k, j);
		k = j;
	}
}

/*************************************************************************
*  Check integrity of MaxPQ data structure
*************************************************************************/
// instantiate a complete binary tree with given data and its size.
pq newCBT(Key *a, int aSize) {
	int n = 1;
	double m = aSize+1;
	int i;
	while(m>1){
		m/=2.0f;
		n*=2;
	}

	pq p = (pq)malloc(sizeof(PQ));
	p->node = (Key*)malloc(n);
	p->capacity = n;
	for(i=0; i<aSize; i++){
		p->node[i+1] = a[i];
	}
	p->N = i;
	return p;
}

// restore the max heap property - parent key is larger than children's
void heapify(pq p) {
	int i, j , max;
	char temp;
	for(i = 1; i < p->N; i++) {
		max = i;
		for(j = i+1; j <= p->N; j++)
			if (p->node[j] > p->node[max])
				max = j;
		temp = p->node[i];
		p->node[i] = p->node[max];
		p->node[max] = temp;
	}
}

/** is PQ[1..N] a max PQ? */
int isMaxHeap(pq p) {
	int i = p->N;
	while(i>1){
		if(less(p, i/2, i))
			return false;
		i--;
	}
	return true;
}

/**
* display all keys in this PQ and status of the PQ.
* this may be enhanced to show the levels nicely such as
* L:1	T
* L:2	P	R
* L:3   N   H   O   A
* L:4   E	I	G
*
* L:1	20
* L:2	16	18
* L:3   14	8  15   1
* L:4   5	9  7
*/
void showHeap(pq p) {
	int i = p->N;
	int j = 1;
	if (p == NULL || isEmpty(p)) { printf("Heap is empty.\n"); 	return; }
	
	while(i>1){
		i/=2;
		j++;
	}

	printf("Heap Capacity: %d, N: %d\n", p->capacity, p->N);
	for (int i=1, n =1, k=1;j>0; j--, n++){
		printf("L:%d   ",n);
		for(int l = 0; l<k ; l++, i++){
			if(i>p->N) break;
			printf("%c   ", p->node[i]);
		}
		printf("\n");
		k*=2;
	}

	for (i = 1; i <= p->N; i++) {
		printf("[%d]=%c ", i, p->node[i]);		//// Key dependent ////
	}
	printf("\n");
}

/**
* It reads all items in a PQ in level order and makes them into a string.
* Note that the returned string buffer must be deallocated by the caller.
* @return the string that stores values of all items in PQ
*
* This is tailored only for Key int type.
* If Key change from int to double or char, this should be changed properly.
*/
char *toString(pq p) {
	int i;
	char string[3];		//// Key dependent ////
	// Use string[16] for Key int type storage in chars
	// max int: 10 digits, sign, null, ' '
	if (p == NULL || isEmpty(p)) return NULL;

	int bufferLength = (p->N) * sizeof(char)* sizeof(string)+1;	// not strlen();
	char *buffer = (char *)malloc(bufferLength);	// the entire PQ value in chars 
	if (buffer == NULL) return NULL;

	strcpy_s(buffer, bufferLength, "");
	for (i = 1; i <= p->N; i++) {
		sprintf_s(string, "%c ", p->node[i]);		//// Key dependent ////
		strcat_s(buffer, bufferLength, string);
	}
	return buffer;
}

