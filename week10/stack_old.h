#define MAX 50

#define elType int

typedef elType StackType[MAX];

int top = -1;


void StackInitialize(StackType stack);
int StackIsEmpty(StackType stack);
int StackIsFull(StackType stack);
void StackPush(elType el, StackType stack);
elType StackPop(StackType stack);

void StackInitialize(StackType stack) {
	top = -1;
}
int StackIsEmpty(StackType stack) {
	return (top == 0);
}
int StackIsFull(StackType stack) {
	return (top < MAX);
}
void StackPush(elType el, StackType stack) {
	if (StackIsFull(stack)) {
		printf("Stack Over Flow\n");
	} else {
		stack[++top] = el;
	}
}
elType StackPop(StackType stack) {
	if (StackIsEmpty(stack)) {
		printf("Stack Under Flow\n");
	} else {
		top--;
		return stack[top+1];
	}
}