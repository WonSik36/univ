/* SList.h */
/**
 * SList is a singly-linked implementation of the linked list abstraction.
 * SList is a mutable data structure, which can grow at either end.
 * 
 * SListNode is a node of a singly-linked list SList, used internally.
 * Each SListNode has two fields:  one to an object or its data item,
 * and one to the next node in the list.
 *
 * @author Youngsup Kim
 * 2014/03/15 Creation
 * 2014/04/16 return values are changed to true/false except pop()/dequeue()
 */

#ifndef SList_h
#define SList_h

typedef struct SListNode *pSListNode;
typedef struct SListNode {
	int			item;		// an object, or a data item;
	pSListNode	next;
} SListNode;

/**
 * makeSListNode() (with two parameters) constructs a list node referencing the
 * data item or object, whose next list node is to be "next".
 *
 * item - the data item or the object
 * next - reference to the next node. may be null.
 * This function may return null if the memory cannot be allocated.
 */
pSListNode makeSListNode(int item, pSListNode next);

typedef struct SList *pSList;
typedef struct SList {
	pSListNode	head;
	pSListNode	tail;		// use it when necessary
	int			size;
} SList;

pSList makeSList();							// Create a singly linked list
int isEmptySList(pSList p);					// return true or false
int lengthSList(pSList p);					// return the size or the number of node

int insertFrontSList(int item, pSList p);	// add a node with item at front, return true or false
int insertEndSList(int item, pSList p);		// add a node with item at end, return true or false
int insertTailSList(int item, pSList p);	// same as insertEndSList, but O(1). return true or false
int deleteSList(int item, pSList p);		// delete a node with item, return true or false
int deleteFrontSList(pSList p);				// delete a node at front, return true or false
int deleteEndSList(pSList p);				// delete a node at end, return true or false

// support stack ADT
int popSList(pSList p);						// delete a node at front, return item
											// if stack is empty or error, do nothing and return false
int pushSList(int item, pSList p);			// add a node at front, return true or false

// support queue ADT
int enqueueSList(int item, pSList p);		// add a node at end, return true or false
int dequeueSList(pSList p);					// delete a node at front, return item
											// if queue is empty or error, do nothing and return false

int nthSList(int position, pSList p);		// return item of n th node
char *toStringSList(pSList p);				// return string of all items
void freeSList(pSList p);					// free nodes as well as list itself
void validateSList(pSList p);				// validate the correctness of SList.size, tail

void smoothie(int a[], int n);
void squeezer(pSList p);					// remove the repeated items
void rehearse(pSList p);					// add the same item one after another

#endif SList_h


