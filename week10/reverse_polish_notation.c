#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Common stack
#define elType char
#include "stack_linkedlist.h"

#define MAX_STR_LEN 1000


void removeLastChar(char *s) {
	if (strlen(s) > 0) {
		if (s[strlen(s)-1] == '\n')
			s[strlen(s)-1] = '\0';
	}
}

void Reverse_Polish_Notation(char * expression, char * notation) {
	int i;

	StackType * calculation = NULL;

	StackInitialize(&calculation);

	char tmp[MAX_STR_LEN];

	notation[0] = '\0';
	for (i = 0; i < strlen(expression); ++i) {
		if (expression[i] >= '0' && expression[i] <= '9') {
			snprintf(tmp, sizeof(tmp), "%s %c", notation, expression[i]);
			strcpy(notation, tmp);
		} else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
			StackPush(&calculation, expression[i]);
		}
	}

	while (!StackIsEmpty(calculation)) {
		snprintf(tmp, sizeof(tmp), "%s %c", notation, StackPop(&calculation));
		strcpy(notation, tmp);
	}

	// free memory
	StackFree(&calculation);
}

int main(int argc, char const *argv[])
{
	char expression[MAX_STR_LEN];
	char notation[MAX_STR_LEN];
	
	printf("Expression: ");
	fgets(expression, MAX_STR_LEN, stdin); removeLastChar(expression);


	Reverse_Polish_Notation(expression, notation);

	printf("Reverse Polish Notation: %s\n", notation);
	
	return 0;
}