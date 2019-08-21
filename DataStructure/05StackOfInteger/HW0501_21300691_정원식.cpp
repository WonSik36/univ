/** EvaluatePostfix.cpp */
/**
 *   On my honor, I pledge that I have neither received nor provided improper assistance
    in the completion of this assignment. Signed: WonSik Cheung
 *  
 *  Authors : SungJin Park, Wonsik Cheung
 *  Date : 2014/04/08
 * 
 * This program evaluate a postfix expression.
 * This program is basiclly a modified or improved version found
 * Horwitz DS book Program 3.13.
*  Now, it can handle blanks and more multiple characters of digits well.

 * examples:
 *   EvaluatePostfix("2 3 4 * +") returns 24
 *   EvaluatePostfix("6 2 / 3 - 4 2 * +") returns 8
 *   EvaluatePostfix("1 2 444  *  +  ") returns 889
 
 *  Group work : I modify getToken. We think about professors intension
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

precedence getToken(stack* s, char expr[], int* n) {                    //To get precedence
	char symbol;
	char *address = &expr[*n];
	int i = 1, j = 0;
	char num[16];
	int number;

 	symbol = expr[(*n)++];
	if(expr[(*n)-1] == ' ' || expr[(*n)] == ' ' || expr[(*n)] == NULL){         //To search operator or 1-digit oprandm or blank
		if(isdigit(expr[(*n)-1]))
			push(s, symbol - '0');
		return getPrecedence(symbol);
	}
	else if (symbol == NULL)             //To search eos
		return getPrecedence(symbol);
	else{                               //To change a string that more multiple characters of digits operands to integer
		while(expr[(*n)++] != ' ')
			i++;                            //check the number of oprands' digit 
		for(j = 0; j < i; j++)              //put more multiple digit into array 'num[]' as character 
			num[j] = *(address + j) ;
		num[j] = NULL;
		number = atoi(num);
		push(s, number);

		return operand;
	}
}

int EvaluatePostfix(char *postfix) {
	//char symbol;
	int n = 0;
	int op1, op2;
	int value;
	stack *s;
	precedence token;

	s = createStackOfIntegers(1);			// NOTE: Begin with 1 when you test your code

	token = getToken(s, postfix, &n);
	while (token != eos) {
		if (token == operand || token == blank) {
			;
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
		token = getToken(s, postfix, &n);
	}
	
	value = pop(s);                          //stored value of pop(s)
	freeStack(s);
	return value;
}


