#include <stdio.h>


// include stack element type
#define elType int
#include "stack_linkedlist.h"

StackType * stack;

int main(int argc, char const *argv[])
{
	long int n;
	printf("Nhap so he 10: "); scanf("%ld", &n);
	StackType * stack;

	StackInitialize(&stack);

	while ( n!= 0) {
		StackPush(&stack, n%2);
		n = n/2;
	}

	printf("He 2 : ");
	while (!StackIsEmpty(stack)) {
		printf("%d", StackPop(&stack));
	}
	printf("\n");

	return 0;
}