#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Common stack
#include "stack_linkedlist_int.h"


// String stack
#define MAX_STR_LENGTH_IN_STACK 30
#include "stack_linkedlist_string.h"


StackType * intStack;
StrStackType * strStack;


void addANumber() {
	int num;
	printf("Number to add: "); scanf("%d", &num);

	StackPush(&intStack, num);

	// Save action in string stack
	char str[MAX_STR_LENGTH_IN_STACK];
	snprintf(str, sizeof(str), "PUSH %d", num);
	StrStackPush(&strStack, str);
}

void printTop() {
	if (StackIsEmpty(intStack)) {
		printf("Stack is empty!\n");
	} else {
		printf("Top element: %d\n", StackTop(intStack));
	}
}

void popAElem() {

	int num;

	if (StackIsEmpty(intStack)) {
		printf("Stack is empty!\n");
	} else {
		num = StackPop(&intStack);
		printf("Taken out: %d\n", num);

		// Save action in string stack
		char str[MAX_STR_LENGTH_IN_STACK];
		snprintf(str, sizeof(str), "POP %d", num);
		StrStackPush(&strStack, str);
	}

}

void undo() {

	if (StrStackIsEmpty(strStack)) {
		return;
	}
	
	char str[MAX_STR_LENGTH_IN_STACK];
	int num;
	StrStackPop(&strStack, str);

	char action[MAX_STR_LENGTH_IN_STACK];
	strcpy(action, strtok(str, " "));
	num = atoi(strtok(NULL, " "));

	if (strcmp(action, "PUSH") == 0) {
		StackPop(&intStack);
	} else if (strcmp(action, "POP") == 0) {
		StackPush(&intStack, num);
	}
}

int main(int argc, char const *argv[])
{

	StackInitialize(&intStack);
	StrStackInitialize(&strStack);

	int select = 0;
	while (select != 5) {
		printf("\n***** Undo function demo *****\n");
		printf("1. Them mot so nguyen\n");
		printf("2. Xem top\n");
		printf("3. Lay ra mot phan tu\n");
		printf("4. Undo\n");
		printf("5. Thoat\n");
		printf("Your selection: "); scanf("%d", &select);


		switch(select) {
			case 1: addANumber(); break;
			case 2: printTop(); break;
			case 3: popAElem(); break;
			case 4: undo(); break;
			case 5: break;
			default: printf("Your selection is invalid!\n");
		}
	}
	return 0;
}