#include "rpn.h"

#include "stack.h"
#include "queue.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <math.h>
#include <stdlib.h>
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
        fprintf(stderr,"error: unable to parse expression");
        exit(1);
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
    char *operatorCopy, *numCopy;
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
            numCopy = malloc(strlen(numBuffer) + 1);
            if (!numCopy) {
                fprintf(stderr, "Memory allocation failed\n");
                free_stack(opStack);
                free_queue(Q);
                exit(1);
            }
            strcpy(numCopy, numBuffer);
            push_queue(Q, numCopy, strlen(numCopy) + 1);
            free(numCopy);
            i--;
        } else if (isOperator(currentChar)) {
            while (opStack->head &&
                   (getPrecedence(*(char *)peek_stack(opStack)) > getPrecedence(currentChar) ||
                    (getPrecedence(*(char *)peek_stack(opStack)) == getPrecedence(currentChar) &&
                     isLeftAssociative(*(char *)peek_stack(opStack))))) {
                operatorCopy = pop_stack(opStack);
                if (operatorCopy) {
                    push_queue(Q, operatorCopy, strlen(operatorCopy) + 1);
                    free(operatorCopy);
                }
            }
            operatorCopy = malloc(2);
            if (!operatorCopy) {
                fprintf(stderr, "Memory allocation failed\n");
                free_stack(opStack);
                free_queue(Q);
                exit(1);
            }
            operatorCopy[0] = currentChar;
            operatorCopy[1] = '\0';
            push_stack(opStack, operatorCopy, strlen(operatorCopy) + 1);
            free(operatorCopy);
        } else if (currentChar == '(') {
            operatorCopy = malloc(2);
            if (!operatorCopy) {
                fprintf(stderr, "Memory allocation failed\n");
                free_stack(opStack);
                free_queue(Q);
                exit(1);
            }
            operatorCopy[0] = currentChar;
            operatorCopy[1] = '\0';
            push_stack(opStack, operatorCopy, strlen(operatorCopy) + 1);
            free(operatorCopy);
        } else if (currentChar == ')') {
            while (peek_stack(opStack) && *((char *)peek_stack(opStack)) != '(') {
                operatorCopy = pop_stack(opStack);
                if (operatorCopy) {
                    push_queue(Q, operatorCopy, strlen(operatorCopy) + 1);
                    free(operatorCopy);
                }
            }
            operatorCopy = pop_stack(opStack);
            if (operatorCopy) {
                free(operatorCopy);
            }
        }
    }

    while (opStack->head) {
        operatorCopy = pop_stack(opStack);
        if (operatorCopy) {
            if (operatorCopy[0]=='('){
                fprintf(stderr,"invalid parenthesis");
                exit(1);
            }
            push_queue(Q, operatorCopy, strlen(operatorCopy) + 1);
            free(operatorCopy);
        }
    }

    free_stack(opStack);
    return Q;
}



/* evaluate the rpn expression given in *queue. */
/* return the value of the evaluated expression. */
/* if an error occurs during evaluation, return silently with HUGE_VAL. */
/* assume a precision of eight decimal places when performing arithmetic. */
double evaluateExpression(double val1,double val2, char operator){
    switch (operator)
    {
    case '+':
        return val1+val2;
    
    case '-':
        return val1-val2;

    case '*':
        return val1*val2;

    case '/':
        return val1/val2;

    case '^':
        return pow(val1,val2); 

    default:
        return 0;
    }

}


double evaluate_rpn(Queue *queue) {
    Stack *dataStack = initialise_stack();
    double finalValue = 0.0;
    Node *cur;
    char *token;
    double operand1, operand2;
    size_t tokenLen;
    double *result;

    cur = queue->head;
    while (cur) {
        token = (char *)(cur->data);
        
        if (isOperator(*token) && ((cur == queue->tail) || (!(isdigit(*(token + 1)))))) {
            operand2 = *((double *)pop_stack(dataStack));
            operand1 = *((double *)pop_stack(dataStack));

            result = malloc(sizeof(double));
            if (result == NULL) {
                perror("Memory allocation failed");
                exit(1);
            }
            *result = evaluateExpression(operand1, operand2, *token);
            push_stack(dataStack, (void *)result, sizeof(double));
        } else {
            operand1 = strtod(token, NULL);
            push_stack(dataStack, (void *)&operand1, sizeof(double));
        }

        cur = cur->next;
    }

    finalValue = *((double *)pop_stack(dataStack));

    
    free_stack(dataStack);
    return finalValue;
}

