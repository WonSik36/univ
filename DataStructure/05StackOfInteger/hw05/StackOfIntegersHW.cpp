/** StackOfIntegers.cpp */
/**
 *   On my honor, I pledge that I have neither received nor provided improper assistance
    in the completion of this assignment. Signed: SungJin Park
 *  
 *  Authors : SungJin Park, Wonsik Cheung
 *  Date : 2014/04/07
 * 
 * This StackOfIntagersHW was expanded code with a resizing array.
 * On resizing array, the size of array is expanded to double
 * when it is full and halves the underlying array when it is on-quater full.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "StackOfIntegers.h"

/**
 * Initializes an empty stack.
 */
stack *createStackOfIntegers(int capacity) {  // StackOfIntegers
	int memorySize;
	stack *s;

	s = (stack *)malloc(sizeof(stack));
	s->capacity = capacity < 1 ? 1 : capacity;	
	s->N = 0;

	memorySize = sizeof(element)* s->capacity;
	s->item = (element *)malloc(memorySize);
	if (s->item == NULL) {
		fprintf(stderr, "Cannot allocate dynamic memory(%d bytes)\n", memorySize);
		exit(EXIT_FAILURE);
	}

	return s;
}

/**
 * deallocate a stack.
 */
void freeStack(stack *s) {
	free(s->item);
	free(s);
}

/**
 * return the stack size N or number of items
 */
int size(stack *s) {
	return s->N;
}

/**
 * return the stack capacity or number of items
 */
int capacity(stack *s) {
	return s->capacity;
}
/**
 * Adds the item to this stack.
 * resizing the stack by repeated doubling when it is full.
 * @param item - the item to add
 */
int push(stack *s, int key) {
	int memorySize;
	
	if (isFull(s)) {
		if(s -> capacity == 0)
			s->capacity = 1;
		else
			s->capacity*=2;
		
		memorySize = s->capacity * sizeof(element);
		s->item = (element *)realloc(s->item, memorySize);
		
		if(s == NULL){
			fprintf(stderr, "Cannot reallocate dynamic memory(%d bytes)\n", memorySize);
			exit(EXIT_FAILURE);
		}
	}

	s->item[s->N++].key = key;
	return key;
}

/**
 * @print "Stack is empty" in stderr and return INT_MIN if this stack is empty
 */
int emptyStack() {
#if _DEBUG
	fprintf(stderr, "Stack is empty.\n");
#endif
	return INT_MIN;					// look for a better way?
}

/**
 * Returns (but does not remove) the item most recently added to this stack.
 * @return the item most recently added to this stack
 * @print "Stack is empty" in stderr and return INT_MIN if this stack is empty
 */
int peep(stack *s) {
	return s->item[(s->N-1)].key;                                                   
}

/**
 * Removes and returns the item most recently added to this stack.
 * The stack is resized by one half when it becomes one quarter full.
 * After resize, the stack is still half full or half empty.
 */
int pop(stack *s) {
	int memorySize;
	
	if (isEmpty(s)) return emptyStack();

	if ((s->N-1 == (s->capacity / 4))  && (s->capacity != 1)) {
		s->capacity/=2;
		memorySize = s->capacity * sizeof(element);
		s->item = (element *)realloc(s->item, memorySize);
		
		if(s == NULL){
			fprintf(stderr, "Cannot reallocate dynamic memory(%d bytes)\n", memorySize);
			exit(EXIT_FAILURE);
		}
	}
	return s->item[--s->N].key;
	
}

/**
 * Is this stack empty?
 * @return true if this stack is empty; false otherwise
 */
int isEmpty(stack *s) {
	return s->N <= 0 ? true : false;
}

/**
 * Is this stack full?
 * @return true if this stack is full; false otherwise
 */
int isFull(stack *s) {
	return (s->N) == s->capacity ? true : false;
}

/**
 * reads all items in this stack into a string
 */
char *toString(stack *s) {
	int i;
	char string[16];		// one element storage in chars
	// max int: 10 digits, sign, null, ' '
	int bufferLength;		// estimated buffer size
	char *buffer;			// the entire stack value in chars 

	if (isEmpty(s)) return "";

	bufferLength = (s->N) * sizeof(char)* sizeof(string);
	buffer = (char *)malloc(bufferLength);
	if(buffer == 0){
		fprintf(stderr, "Cannot allocate dynamic memory(%d bytes)\n", bufferLength);
		exit(EXIT_FAILURE);
	}

	strcpy_s(buffer, bufferLength, "");
	for (i = 0; i < s->N; i++) {
		sprintf_s(string, "%d ", s->item[i].key);
		strcat_s(buffer, bufferLength, string);
	}
	return buffer;
}

/**
 * displays all items in this stack
 */
void showStack(stack *s) {
	int i;
	if (isEmpty(s)) return;

	printf("stack capacity:%d \n", s->capacity);
	printf("stack N items: %d \n", s->N);
	printf("stack elements: ");
	for (i = 0; i < s->N; i++) {
		printf("(%d)=%d ", i, s->item[i].key);
	}
	printf("\n");
	system("PAUSE");
}
