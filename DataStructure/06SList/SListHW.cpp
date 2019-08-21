/* SListHW.cpp */
/* On my honor, I pledge that I have neither received nor provided improper assistance 
 * in the completion of this assignment. Signed: WonSikCheung.
 */
/**
 * The SList is a singly-linked implementation of the linked list abstraction.  
 * SList is a mutable data structure, which can grow at either end.
 *
 * @author WonSikCheung
 * @student number 21300691
 * @e-mail address cws0173@hgu.edu
 * 2014/03/15 Creation
 * 2014/04/16 Modified - delete/insert returns true or false instead of size, 
 *						 except pop() & dequeue()
 */

/********************************************************************************
pSList makeSList();							 Create a singly linked list
int isEmptySList(pSList p);					 return true or false
int lengthSList(pSList p);					 return the size or the number of node

int insertFrontSList(int item, pSList p);	 add a node with item at front, return true or false
int insertEndSList(int item, pSList p);		 add a node with item at end, return true or false
int insertTailSList(int item, pSList p);	 same as insertEndSList, but O(1). return true or false
int deleteSList(int item, pSList p);		 delete a node with item, return true or false
int deleteFrontSList(pSList p);				 delete a node at front, return true or false
int deleteEndSList(pSList p);				 delete a node at end, return true or false

// support stack ADT
int popSList(pSList p);						 delete a node at front, return item
											 if stack is empty or error, do nothing and return false
int pushSList(int item, pSList p);			 add a node at front, return true or false

// support queue ADT
int enqueueSList(int item, pSList p);		 add a node at end, return true or false
int dequeueSList(pSList p);					 delete a node at front, return item
											 if queue is empty or error, do nothing and return false

int nthSList(int position, pSList p);		 return item of n th node
char *toStringSList(pSList p);				 return string of all items
void freeSList(pSList p);					 free nodes as well as list itself
void validateSList(pSList p);				 validate the correctness of SList.size, tail
****************************************************************************************************/

/***********************************************************************************************************
EXAMPLE:
makeSList() -> insertFrontSList(1, pSList) -> insertFrontSList(0, pSList) -> int insertEndSList(2, pSList) -> insertTailSList(3, pSList)
  NULL             [1]                            [0]->[1]                    [0]->[1]->[2]                     [0]->[1]->[2]->[3]
-> deleteSList(2, pSList) -> deleteFrontSList(pSList) -> deleteEndSList(pSList) -> toString(pSList)
   [0]->[1]->[3]                    [1]->[3]                   [1]                   ouput: [ 1 ]
-> pushSList(0, pSList) -> popSList(pSList) -> enqueueSList(0, pSList) -> dequeueSList(pSList)
   [0]->[1]                [1]                   [0]->[1]                   [0]
****************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "SList.h"
#include "verify.h"

/** 
 * This constructs singly linked list with a null pointer;
 */
pSList makeSList() {
	// SList *newSList = (SList *)malloc(sizeof (SList));
	pSList newSList = (pSList)malloc(sizeof(SList));
	if (newSList != NULL) {
		newSList->head = NULL;
		newSList->tail = NULL;
		newSList->size = 0;
	}
	return (newSList);
}

/**
 * freeSList() deallocate all the nodes in the list p and itself as well.
 */
void freeSList(pSList p) {
	pSListNode prev;
	pSListNode curr;
	
	if(p->head != NULL){                         //if p has more than one node.
		prev = p->head;
		curr = prev->next;
		while(curr != NULL){
			free(prev);
			prev = curr;
			curr = curr->next;
		}
	free(prev);
	}

	free(p);

	return; 
}

/**
 *  isEmptySList() indicates whether the list is empty.
 *  @return true(or non zero value) if the list is empty,
 *          false otherwise.
 **/
int isEmptySList(pSList p) {
	return p->size == 0 ? true : false;	
}

/**
 * lengthSList() returns the length of the list p.
 * @return the length of the list p.
 */
int lengthSList(pSList p) {
	return p->size;
}

/**
 * insertFrontSList() inserts the object (item) at the beginning of the list p.
 * return true if the operation is complete, otherwise return false;
 * @param item - the object to be inserted.
 */
int insertFrontSList(int item, pSList p) {
	if(p->head == NULL){
		p->head = makeSListNode(item, p->head);		// add it to the front
		p->tail = p->head;
	}
	else
		p->head = makeSListNode(item, p->head);		// add it to the front
	
	if (p->head == NULL) return false;
	p->size++;
	return true;
}


/**
 * insertEndSList() inserts the object (item) at the end of the list p.
 * return true if the operation is complete, otherwise return false;
 * @param item - the object to be inserted.
 */
int insertEndSList(int item, pSList p) {
	if (p->head == NULL) {
		p->head = makeSListNode(item, NULL);
		p->tail = p->head;
		if (p->head == NULL) return false;
	}
	else {
		pSListNode node = p->head;
		while (node->next != NULL) {
			node = node->next;
		}			// add it to the end. therefore it must be NULL
		node->next = makeSListNode(item, NULL); 
		p->tail = node->next;
		if (node->next == NULL) return false;
	}
	p->size++;
	return true;
}


/**
 * insertTailList() insert a node with an item at the end of the list p.
 * This function makes insert operation in O(1) instead of O(n) time complexity experienced in insertEndSList().
 * same functionality as insertEndSList.
 * return true if the operation is complete, otherwise return false;
 */
int insertTailSList(int item, pSList p){
	if (p->head == NULL) {
		p->head = makeSListNode(item, NULL);
		p->tail = p->head;
		if (p->head == NULL) return false;
	}
	else{
		(*p).tail->next = makeSListNode(item, NULL);
		p->tail = (*p).tail->next;
	}
	if(p->tail == NULL) return false;
	p->size++;
	return true;
}

/**
 * deleteSList() delete nodes which have the item input.
 * return true if the operation is complete, otherwise return false;
 */
int deleteSList(int item, pSList p){
	pSListNode prev = NULL;
	pSListNode curr = p->head;
	int check = 0;

	if(isEmptySList(p) == true)                         //if p has no node
		return false;

	while(curr != NULL){
		if(curr->item == item){                          //if current node has the item.
			if((prev == NULL) && (curr->next == NULL)){  //if p has one node.
				p->head = NULL;
				p->tail = NULL;
				free(curr);
				check++;
				break;
			}

			else if(prev == NULL){                       //if node that has the item is at the front.
				p->head = curr->next;
				free(curr);
				curr = p->head;
				check++;
				continue;
			}
			
			else if(curr->next == NULL){                 //if node that has the item is at the last.
			prev->next = NULL;
			p->tail = prev;
			free(curr);
			check++;
			break;
			}
			
			else{
				prev->next = curr->next;
				free(curr);
				curr = prev->next;
				check++;
				continue;
			}
		}
			prev = curr;
			curr = curr->next;
	}
	if(check==0)
		return false;
	p->size-=check;
	return check==0 ? false : true;
}

/**
 * deleteFrontSList() delete a node at first of list.
 * return true if the operation is complete, otherwise return false;
 */
int deleteFrontSList(pSList p){
	pSListNode next;
	
	if(isEmptySList(p) == true)                     //if p has no node.
		return false;
	else if((*p).head->next == NULL){               //if p has one node.
		free(p->head);
		p->head = NULL;
		p->tail = NULL;
		p->size--;
		return true;
	}
	else{
		next = (*p).head->next;
		free(p->head);
		p->head = next;
		p->size--;
		return true;
	}
}


/**
 * deleteEndSList() delete a node at last of list.
 * return true if the operation is complete, otherwise return false;
 */
int deleteEndSList(pSList p){
	if(isEmptySList(p) == true)                         //if p has no node.
		return false;
	else if((*p).head->next == NULL){                              //if p has one node.
		p->head = NULL;
		p->tail = NULL;
		free(p->head);
		p->size--;
		return true;
	}
	else{
		pSListNode prev = p->head;
		pSListNode curr = prev->next;

		while(curr->next != NULL){
			prev = curr;
			curr = curr->next;
		}
		p->tail = prev;
		prev->next = NULL;
		free(curr);
		p->size--;
		return true;
	}
}


/**
 * popSList() delete a node with an item at the front of the list p.
 * return item if the operation is complete, otherwise return false(if stack is empty or error);
 */
int popSList(pSList p){
	int item;

	if(isEmptySList(p) == true)
		return false;
	else{
		item = (*p).head->item;
		if(deleteFrontSList(p) == true)
			return item;
		else
			return false;
	}
}


/**
 * pushSList() insert a node with an item at the front of the list p.
 * return true if the operation is complete, otherwise return false;
 */
int pushSList(int item, pSList p) {
	return insertFrontSList(item, p);
}

/**
 * enqueueSList() insert a node with an item at the end of the list p.
 * return true if the operation is complete, otherwise return false;
 */
int enqueueSList(int item, pSList p) {
	return insertEndSList(item, p);
}

/**
 * depueueSList() delete a node with an item at the front of the list p.
 * return item if the operation is complete, otherwise return false(if queue is empty or error);
 */
int dequeueSList(pSList p){
	return popSList(p);
}


/**
 * nthSList() returns the item at the specified position.  
 * If position < 1 or position > this.length(), 0 or NULL is returned. 
 * NOTE: When the item becomes an object or a referenced variable type, 
 *       the function return type should should be the reference type, 
 *       also return NULL;
 * Otherwise, the item at position "position" is returned.  
 * The list p does not change.
 *
 * @param position - the desired position, from 1 to length(), in the list p.
 * @return the item at the given position in the list.
 */

int nthSList(int position, pSList p) {
	pSListNode currentNode;

	if ((position < 1) || (p->head == NULL)) {
		return 0;			// NULL;
	}
	else {
		currentNode = p->head;
		while (position > 1) {
			currentNode = currentNode->next;
			if (currentNode == NULL) {
				return 0;	// NULL;
			}
			position--;
		}
		return currentNode->item;
	}
}

/**
 * toStringSList() converts the list to a String.
 * @return a String representation of the list p.
 * The caller of toStringSList() must free it after its use.
 */

char *toStringSList(pSList p) {
	char *oneStr;
	char *sumStr;

	oneStr = (char *)malloc(sizeof(SList));
	sumStr = (char *)malloc(sizeof(SList) * lengthSList(p)); // too big?
	strcpy(sumStr, "[ ");

	pSListNode curr = p->head;

	while (curr != NULL) {
		sprintf(oneStr, "%d ", curr->item);
		strcat(sumStr, oneStr);
		curr = curr->next;
	}
	strcat(sumStr, "]");
	free(oneStr);
	return sumStr;
}

/**
 * It verifies the correctness (or integrity) of SList data structure.
 * It goes through the list, it counts the number of nodes and gets the last node.
 * Then it compares them with SList.tail and SList.size.
 */
void validateSList(pSList p) {
	pSListNode curr, prev;
	int nodeCount = 0;
	char message[512];

	if (p == NULL) return;
	if (p->head == NULL) {
		sprintf(message, "Its length(%d) should be 0.", p->size);
		verify(p->size == 0, message);

		// Uncomment the following two lines when you are ready to test tail stuff
		// sprintf(message, "Its tail(%x) should be NULL.", p->tail);
		// verify(p->tail == NULL, message);
		return;
	}

	curr = p->head;
	do {
		prev = curr;
		++nodeCount;
		curr = curr->next;
	} while (curr != NULL);

	sprintf(message, "Its length(%d) is different from %d.", p->size, nodeCount);
	verify(nodeCount == p->size, message);

	// Uncomment the following two lines when you are ready to test tail stuff
	// sprintf(message, "Its tail(%x) is different from %x.", p->tail, prev);
	// verify((prev == p->tail), message);
	return;
}