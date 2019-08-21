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
 */
// 
// Author: Youngsup Kim
// 03/20/2014	Created

#ifndef StackOfIntegers_h
#define StackOfIntegers_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct element {
	int  key;
	// add other fields as needed
} element;

typedef struct stack {
	element *item;			// this is called "stack" in the "Horwitz" book
	int capacity;			// stack size
	int N;					// number of items; 0 if empty 
} stack;

stack *createStackOfIntegers(int capacity);	// stack is created with capacity, top= -1
void freeStack(stack *s);
void showStack(stack *);
int size(stack *s);					// return nItems
int capacity(stack *s);				// return its capacity (array size)
int pop(stack *s);					// pop the top item in the stack
int peep(stack *s);					// return the top item, no change in stack
int push(stack *s, int key);		// return key if it pushed OK, otherwise return (key^FFFF)  
int isFull(stack *s);				// return true/false
int isEmpty(stack *s);				// return true/false
char *toString(stack *);			// return a string that contains all values of stack

#endif StackOfIntegers_h



