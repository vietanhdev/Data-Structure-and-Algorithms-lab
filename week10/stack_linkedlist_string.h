#include <stdlib.h>
#include <string.h>

#define StrStackType str_node_t
#ifndef MAX_STR_LENGTH_IN_STACK
#define MAX_STR_LENGTH_IN_STACK 30
#endif

typedef struct str_node {
	char str[MAX_STR_LENGTH_IN_STACK];
	struct str_node * next;
} str_node_t;

void StrStackPush(str_node_t ** head, char * str) {
	str_node_t * new_node;
	new_node = malloc(sizeof(str_node_t));
	strcpy(new_node->str, str);
	new_node->next = *head;
	*head = new_node;
}

void StrStackPop(str_node_t ** head, char * str) {
	if (*head == NULL) { // No elem in list
		strcpy(str, "");
		return;
	}

	str_node_t * next_node = (*head)->next;
	strcpy(str, (*head)->str);
	free(*head);
	*head = next_node;
}

void StrStackTop(StrStackType * head, char * str) {
	if (head != NULL) {
		strcpy(str, head->str);
	} else {
		strcpy(str, "");
	}
}

int StrStackIsEmpty(StrStackType * head) {
	return (head == NULL);
}

void StrStackInitialize(StrStackType ** head) {
	char tmp[MAX_STR_LENGTH_IN_STACK];
	while (*head != NULL) {
		StrStackPop(head, tmp);
	}
}