/** EvaluatePostfix.cpp */

/* This program evaluate a postfix expression.
* This program is basiclly a modified or improved version found
* Horwitz DS book Program 3.13.
* It uses the StackOfIntegers developed for the general purpose.
* It should be able to handle blanks and more multiple characters
* of digits perperaly.
* Also it does not use the any global variables.
*
* examples:
*   EvaluatePostfix("2 3 4 * +") returns 24
*   EvaluatePostfix("6 2 / 3 - 4 2 * +") returns 8
*   EvaluatePostfix("1 2 444  *  +  ") returns 889
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StackOfIntegers.h"
#include "Postfix.h"

void main(int argc, char *argv[]) {
	char postfix[256];

	// NOTE: the following three lines are only for initial testing.
    // it should be replaced by the next block #if 0 block code
#if 0
	strcpy_s(postfix, sizeof(postfix), "234*+");    
	printf("postfix = %s\n", postfix);              
	printf("result = %d \n", EvaluatePostfix(postfix));
#endif
	// the following tests should work when you compelete it
#if 1
	strcpy_s(postfix, sizeof(postfix), "2 3 4 *  +  ");
	printf("postfix = %s\n", postfix);
	printf("result = %d \n", EvaluatePostfix(postfix));

	strcpy_s(postfix, sizeof(postfix), "6 2 / 3 - 4 2 * +");
	printf("postfix = %s\n", postfix);
	printf("result = %d \n", EvaluatePostfix(postfix));

	strcpy_s(postfix, sizeof(postfix), "1 2 444  *  +  ");
	printf("postfix = %s\n", postfix);
	printf("result = %d \n", EvaluatePostfix(postfix));
	system("pause");
#endif
}

