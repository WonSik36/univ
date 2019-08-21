/** StackOfIntegersDriver.cpp */
/**
* This program tests StackOfIntegers.cpp 
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
*/
// 
// Author: Youngsup Kim
// 03/20/2014	Created

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "StackOfIntegers.h"

int main(int argc, char *argv[]) {
	stack *s;

	printf("Welcome to the stack world!\n");

	s = createStackOfIntegers(1);
	printf("Stack should be empty: pop()=%d\n", pop(s));
	printf("push %d\n", push(s, 1));
	printf("push %d\n", push(s, 2));
	printf("push %d\n", push(s, 3));
	printf("The stack should have 1 2 3. Now the stack has %s\n", toString(s));
	printf("The stack capcity should be 4. Now it is %d\n", capacity(s));
	printf("pop %d\n", pop(s));
	printf("pop %d\n", pop(s));
	printf("pop %d\n", pop(s));
	printf("pop %d\n", pop(s));
	printf("push %d\n", push(s, 5));
	printf("push %d\n", push(s, 6));
	printf("push %d\n", push(s, 7));
	printf("The stack should have 5 6 7. Now the stack has %s\n", toString(s));
	printf("pop %d\n", pop(s));
	printf("push %d\n", push(s, 9));
	printf("The stack should have 5 6 9. Now the stack has %s\n", toString(s));
	printf("pop %d, pop %d\n", pop(s), pop(s));
	printf("The stack capacity should be 4, Now it is %d \n", capacity(s));

	showStack(s);
	freeStack(s);
	printf("The end of the statck world\n");
}
