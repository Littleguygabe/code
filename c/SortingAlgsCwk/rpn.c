#include "rpn.h"

#include "stack.h"
#include "queue.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* convert an infix expression to postfix (rpn) using the */
/* shunting yard algorithm. */
/* return a queue containing the postfix expression. */
/* if an error occurs during evaluation, return silently with NULL. */


int isLeftAssociative(char c){
	if (c == '+'||c == '-'||c == '*'||c == '/'){
		return 1;
	}

	return 0;
}

int isOperator(char c){
	if (c == '+'||c == '-'||c == '*'||c == '/'||c=='^'){
		return 1;
	}

	return 0;
}

int getPrecedence(char c){
	switch (c)
	{
	case '+': case'-':
		return 1;

	case '*': case'/':
		return 2;

	case '^':
		return 3;

	default:
		return -1;
	}
}

int isNumber(char *expr, int i) {
    if (isdigit(expr[i])) {
        return 1;
    }

    if ((expr[i] == '+' || expr[i] == '-') && 
        (i == 0 || expr[i-1] == '(' || isOperator(expr[i-1]) || expr[i-1] == ' ')) {
        if (isdigit(expr[i+1]) || expr[i+1] == '.') {
            return 1;
        }
    }

    if (expr[i] == '.') {
        if (i > 0 && isdigit(expr[i-1]) && isdigit(expr[i+1])) {
            return 1;
        }
    }

    if (isalpha(expr[i])) {
        return 1;
    }

    return 0;
}




int testPrecedence(int val1, int val2){
	if (val1<val2){
		return -1;
	}

	else if (val1>val2){
		return 1;
	}

	return 0;
}

Queue *infix_to_postfix(char *expr) {
    Queue *Q;
    Stack *opStack;
    char numBuffer[100];
    char currentChar;
    char operatorChar;
    char openParen;
    int numBufferIndex, i, exprLen;

    Q = initialise_queue();
    opStack = initialise_stack();
    numBufferIndex = 0;

    exprLen = strlen(expr);

    for (i = 0; i < exprLen; i++) {
        currentChar = expr[i];

        if (isNumber(expr, i)) {
            numBufferIndex = 0;
            while (i < exprLen && isNumber(expr, i)) {
                numBuffer[numBufferIndex++] = expr[i++];
            }
            numBuffer[numBufferIndex] = '\0';
            push_queue(Q, numBuffer, strlen(numBuffer) + 1);
            memset(numBuffer, 0, sizeof(numBuffer));
            i--;
        }
        else if (isOperator(currentChar)) {
            while (opStack->head &&
                   (getPrecedence(*(char *)peek_stack(opStack)) > getPrecedence(currentChar) ||
                    (getPrecedence(*(char *)peek_stack(opStack)) == getPrecedence(currentChar) && isLeftAssociative(*(char *)peek_stack(opStack))))) {
                operatorChar = *(char *)pop_stack(opStack);
                
                push_queue(Q, &operatorChar, sizeof(char));
            }
            operatorChar = currentChar;
            push_stack(opStack, &operatorChar, sizeof(char));
        }
        else if (currentChar == '(') {
            openParen = currentChar;
            push_stack(opStack, &openParen, sizeof(char));
        }
        else if (currentChar == ')') {
            while (peek_stack(opStack) && *((char *)peek_stack(opStack)) != '(') {
                operatorChar = *(char *)pop_stack(opStack);                
                push_queue(Q, &operatorChar, sizeof(char));
            }
            if (!peek_stack(opStack)) {
                fprintf(stderr, "Mismatched parentheses\n");
                exit(1);
            }
            while (opStack->tail){
                pop_stack(opStack);
            };
        }
    }

    while (opStack->head) {
        operatorChar = *(char *)pop_stack(opStack);
        if (operatorChar == '(') {
            fprintf(stderr, "Mismatched parentheses\n");
            exit(1);
        }
        push_queue(Q, &operatorChar, sizeof(char));
    }

    free_stack(opStack);
    return Q;
}


/* evaluate the rpn expression given in *queue. */
/* return the value of the evaluated expression. */
/* if an error occurs during evaluation, return silently with HUGE_VAL. */
/* assume a precision of eight decimal places when performing arithmetic. */
double evaluate_rpn(Queue *queue)
{
	/* this is just a placeholder return */
	/* you will need to replace it */
	return 0.0;
}