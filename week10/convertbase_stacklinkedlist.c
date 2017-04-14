#include <stdio.h>


// include stack lib & set max, element type
#define STACK_MAX 50
#define elType int
#include "stack.h"



int main(int argc, char const *argv[])
{
	int n;
	printf("Nhap so he 10: "); scanf("%d", &n);
	StackType stack;

	StackInitialize(&stack);

	while ( n!= 0) {
		StackPush(n%2, &stack);
		n = n/2;
	}

	printf("He 2 : ");
	while (!StackIsEmpty(&stack)) {
		printf("%d", StackPop(&stack));
	}
	printf("\n");

	return 0;
}