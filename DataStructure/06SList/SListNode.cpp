/* SListNode.cpp */
/**
 * SListNode is used internally by the SList.  An SList is a singly-linked list, 
 * and an SListNode is a node of a singly-linked list.  
 * Each SListNode has two references:  one to an object or its data item, 
 * and one to the next node in the list.
 * 
 * @author Youngsup Kim
 * 2014/03/15 Creation
 *
 * makeSListNode() (with two parameters) constructs a list node referencing the
 * data item or object, whose next list node is to be "next".
 *
 * item - the data item or the object
 * next - reference to the next node. may be null.
 * This function may return null if the memory cannot be allocated.
 */

#include <malloc.h>
#include <stdio.h>
#include "SList.h"

pSListNode makeSListNode(int item, pSListNode next) {
	// SListNode *newNode = (SListNode *) malloc(sizeof(SListNode));
	pSListNode newNode = (pSListNode)malloc(sizeof(SListNode));
	if (newNode != NULL) {
		newNode->item = item;
		newNode->next = next;
	}
	return newNode;
}