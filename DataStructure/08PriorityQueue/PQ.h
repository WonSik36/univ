#ifndef pq_h
#define pq_h

// this pq_h is required to have Key defined 
// include PQi.h for int type keys
// include PQc.h for char type keys.
// or make your own type, then implement toString() and showPQ(). 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "verify.h"

#ifndef PQKeyTypeDefined
#define PQKeyTypeDefined
#include "PQi.h"					// define default one
#endif

typedef struct PQ *pq;
typedef struct PQ {					// heap or min/max priority queue 
	Key *node;						// an array of nodes (key only for simplicity)
	int capacity;					// array size of node or key, item
	int N;							// the number of nodes in the heap or PQ
} PQ;

pq newPQ(int capacity);				// PQ is created with capacity(or array size)
void freePQ(pq p);					// deallocate PQ
int size(pq p);						// return nItems in PQ currently
int level(int n);					// return level based on num of nodes
int capacity(pq p);					// return its capacity (array size)
int resize(pq p, int size);			// resize the array size (= capacity)
int isFull(pq p);					// return true/false
int isEmpty(pq p);					// return true/false	

int insertMax(pq p, Key key);		// insert in max queue
int deleteMax(pq p);				// delete in max queue

// helper functions to support insert/delete functions
int less(pq p, int i, int j);		// used in MaxPQ
void swap(pq p, int i, int j);		// exchange two node
void swim(pq p, int k);				// bubble up
void sink(pq p, int k);				// tickle down

// helper functions to check Heap ADT

pq newCBT(Key *a, int size);	// instantiate a complete BT with given data & size
void heapify(pq p);				// restore the max heap property from a complete BT
int isMaxHeap(pq p);			// is PQ[1..N] a max PQ? 
void showHeap(pq p);		//// Key dependent //// prints details of PQ status
char *toString(pq p);		//// Key dependent //// return a string that has all keys

#endif pq_h