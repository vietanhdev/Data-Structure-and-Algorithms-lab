#ifndef elType
#define elType int
#endif

#ifndef STACK_MAX
#define STACK_MAX 500
#endif

typedef struct stack_struct {
	elType el[STACK_MAX];
	int top;
} StackType;

void StackInitialize(StackType *stack);
int StackIsEmpty(StackType *stack);
int StackIsFull(StackType *stack);
void StackPush(elType el, StackType *stack);
elType StackPop(StackType *stack);

void StackInitialize(StackType *stack) {
	stack->top = -1;
}
int StackIsEmpty(StackType *stack) {
	return (stack->top < 0);
}
int StackIsFull(StackType *stack) {
	return (stack->top == STACK_MAX);
}
void StackPush(elType el, StackType *stack) {
	if (StackIsFull(stack)) {
		printf("Stack Over Flow\n");
	} else {
		stack->el[++(stack->top)] = el;
	}
}
elType StackPop(StackType *stack) {
	elType returnVal;
	if (StackIsEmpty(stack)) {
		printf("Stack Under Flow\n");
	} else {
		(stack->top)--;
		returnVal = stack->el[stack->top + 1];
	}
	return returnVal;
}