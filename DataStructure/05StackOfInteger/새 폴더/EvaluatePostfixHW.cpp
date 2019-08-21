
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

precedence getPrecedence(char symbol) {
	switch (symbol) {
	case '(': return lparen;	// postfix expr does not have ( ) at all
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case ' ': return blank;
	case '\0': return eos;		// end of string
	default: return operand;	// a char such as '5' 'a' ' '
	}
	return operand;
}

precedence getToken(char *expr, char *symbol, int *n) {
	*symbol = expr[(*n)++];
	return getPrecedence(*symbol);
}

int EvaluatePostfix(char *postfix) {
	char symbol;
	int n = 0;
	int op1, op2;
	stack *s;
	precedence token;

	s = createStackOfIntegers(100);			// NOTE: Begin with 1 when you test your code

	token = getToken(postfix, &symbol, &n);
	while (token != eos) {
		if (token == operand) {
			push(s, (int)(symbol - '0'));
		}
		else {  // pop two operands, perform operation, and push result to the stack 
			op2 = pop(s);
			op1 = pop(s);
			switch (token) {
			case plus: push(s, op1 + op2); 		break;
			case minus: push(s, op1 - op2);		break;
			case times: push(s, op1 * op2);		break;
			case divide: push(s, op1 / op2);	break;
			case mod: push(s, op1 % op2);		break;
			}
		}
		token = getToken(postfix, &symbol, &n);
	}
	return pop(s);
	freeStack(s);
}


