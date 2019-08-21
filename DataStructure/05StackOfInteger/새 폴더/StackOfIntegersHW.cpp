/** StackOfIntegers.cpp */
/**
 *
 * Stack of integers implementation with a resizing array.
 *
 * The StackOfIntegers represents a last-in-first-out (LIFO) stack of integers.
 * It can be expanded to handle a generic element type;
 * It supports the usual push and pop operations, along with methods for peeping at
 * the top item, testing if the stack is empty, and iterating through the items
 * in LIFO order.
 *
 * This implementation uses a resizing array, which double the underlying array
 * when it is full and halves the underlying array when it is one-quarter full.
 * The push and pop operations take constant amortized time.
 * The size, peep, and isEmpty operations takes constant time in the worst case.
 *
 *
 * Author: Youngsup Kim
 * 03/20/2014	Created
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
stack *createStackOfIntegers(int capacity) {
	int memorySize;
	stack *s;

	s = (stack *)malloc(sizeof(stack));
	s->capacity = capacity < 1 ? 1 : capacity;	// StackOfIntegers
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
	printf("ADD YOUR CODE HERE\n");
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
	if (isFull(s)) {
		printf("ADD YOUR CODE HERE to double the stack size by reallocating...\n");
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
	printf("ADD YOUR CODE HERE ....\n");
	return -1;
}

/**
 * Removes and returns the item most recently added to this stack.
 * The stack is resized by one half when it becomes one quarter full.
 * After resize, the stack is still half full or half empty.
 */
int pop(stack *s) {
	if (isEmpty(s)) return emptyStack();

	if (1) {
		printf("ADD YOUR CODE HERE\n");
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

	bufferLength = (s->N) * sizeof(char)* 16;
	buffer = (char *)malloc(bufferLength);
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
}
