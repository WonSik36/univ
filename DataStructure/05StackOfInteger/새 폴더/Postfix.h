
/** Postfix.h */

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

#ifndef Postfix_h
#define Postfix_h

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand, blank } precedence;
precedence getPrecedence(char symbol);
precedence getToken(char *expr, char *symbol, int *n);
int EvaluatePostfix(char *postfix);

#endif Postfix_h
