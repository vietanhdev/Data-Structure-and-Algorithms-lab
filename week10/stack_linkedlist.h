#include <stdlib.h>

#ifndef elType
#define elType int
#endif

#define StackType node_t

typedef struct node {
	elType val;
	struct node * next;
} node_t;

void StackPush(node_t ** head, elType val) {
	node_t * new_node;
	new_node = malloc(sizeof(node_t));
	new_node->val = val;
	new_node->next = *head;
	*head = new_node;
}

elType StackPop(node_t ** head) {
	elType returnVal;

	if (*head == NULL) { // No elem in list
		return returnVal;
	}

	node_t * next_node = (*head)->next;
	returnVal = (*head)->val;
	free(*head);
	*head = next_node;

	return returnVal;
}

int StackIsEmpty(StackType * head) {
	return (head == NULL);
}

void StackInitialize(StackType ** head) {
	while (*head != NULL) {
		StackPop(head);
	}
}