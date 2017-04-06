#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define value_t int

typedef struct node {
	value_t val;
	struct node * next;
} node_t;

void removeLastChar(char *s) {
	s[strlen(s)-1] = '\0';
}

node_t *head = NULL;
node_t *current;

int countList(node_t * head) {
	if (head == NULL)
		return 0;
	int n = 1;
	node_t * current = head;
	while (current->next != NULL) {
		current = current->next;
		n++;
	}
	return n;
}

void pushHead(node_t ** head, value_t val) {
	node_t * new_node;
	new_node = malloc(sizeof(node_t));
	new_node->val = val;
	new_node->next = *head;
	*head = new_node;
}

void pushEnd(node_t ** head, value_t val) { // Insert to the end
	if (*head == NULL) {
		pushHead(head, val);
		return;
	}
	node_t * current = *head;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = malloc(sizeof(node_t));
	current->next->val = val;
	current->next->next = NULL;
}

void pushAfterIndex(int pos, value_t val) {
	if (pos < 0 || pos >= countList(head)) {
		printf("Invalid Position!\n");
		return;
	}
	
	node_t * current = head;
	int i;
	for (i = 1; i < pos; ++i) {
		current = current->next;
	}

	node_t * new_node;
	new_node = malloc(sizeof(node_t));
	new_node->val = val;
	new_node->next = current->next;
	current->next = new_node;
}
void pushBeforeIndex(int pos, value_t val) {
	if (pos < 0 || pos >= countList(head)) {
		printf("Invalid Position!\n");
		return;
	}

	if (pos == 0) {
		pushHead(&head, val);
		return;
	}
	
	node_t * prev = head;
	int i;
	for (i = 0; i < pos-1; ++i) {
		prev = prev->next;
	}

	node_t * new_node;
	new_node = malloc(sizeof(node_t));
	new_node->val = val;
	new_node->next = prev->next;
	prev->next = new_node;
}

value_t popHead(node_t ** head) {
	value_t returnVal;

	if (*head == NULL) { // No elem in list
		return returnVal;
	}

	node_t * next_node = (*head)->next;
	returnVal = (*head)->val;
	free(*head);
	*head = next_node;

	return returnVal;
}

value_t popEnd(node_t ** head) {
	value_t returnVal;

	// If the list has 0 elem
	if (*head == NULL) {
		return returnVal;
	}

	// If the list has only 1 elem
	if ((*head)->next == NULL) {
		returnVal = (*head)->val;
		free(*head);
		*head = NULL;
		return returnVal;
	}

	node_t * current = *head;
	// Travel to last elem
	while (current->next->next != NULL) {
		current = current->next;
	}

	// Remove the last elem and return its value
	returnVal = current->next->val;
	free(current->next);
	current->next = NULL;
	return returnVal;

}


value_t popAt(node_t ** head, node_t * current) {
	value_t returnVal;

	if (current == *head) {
		popHead(head);
		return returnVal;
	}
	
	node_t * prev = *head;
	while (prev->next != current && prev != NULL) {
		prev = prev->next;
	}

	if (prev->next != NULL) { // current is in list
		prev->next = current->next;
		free(current);
	}

	return returnVal;
}

void pushAt(node_t ** head, node_t * current, value_t val) {

	if (current == *head) {
		pushHead(head, val);
		return;
	}
	
	node_t * prev = *head;
	while (prev->next != current && prev != NULL) {
		prev = prev->next;
	}

	if (prev->next == NULL) {
		printf("Error: Position to Push at is not in the list\n");
		return;
	};

	current = malloc(sizeof(node_t));
	current->val = val;
	current->next = prev->next;
	prev->next = current;

}

value_t popAtIndex(int pos) {
	value_t returnVal;
	if (pos < 0 || pos >= countList(head)) {
		printf("Invalid Position!\n");
		return returnVal;
	}

	if (pos == 0) {
		popHead(&head);
		return returnVal;
	}
	
	node_t * prev = head;
	int i;
	for (i = 0; i < pos-1; ++i) {
		prev = prev->next;
	}

	node_t * next_node = prev->next->next;
	returnVal = prev->next->val;
	free(prev->next);
	prev->next = next_node;

	return returnVal;
}


void destroyList() {
	while (head != NULL) {
		popHead(&head);
	}
}



void printInt() {
	node_t * current = head;
	printf("[");
	while (current != NULL) {
		printf(" %d", current->val);
		current = current -> next;
	}
	printf(" ]\n");
	printf("Number of elem: %d\n", countList(head));
}

void initData() {
	destroyList();
	pushHead(&head, 1);
	pushHead(&head, 2);
	pushHead(&head, 3);
	pushHead(&head, 4);
	pushHead(&head, 5);
}


void setCurrentIndex(int pos) {
	if (pos < 0 || pos >= countList(head)) {
		printf("Invalid Position\n");
	}
	int i;
	current = head;
	for (i = 0; i < pos; ++i) {
		current = current->next;
	}
	printf("Current data: %d\n", current->val);
}


int main(int argc, char const *argv[])
{
	value_t val;
	int pos;
	int choice = 0;
	while (choice != 13) {
		printf("LINKED LIST EXAMPLES IN C\n");
		printf("Author: Viet Anh Nguyen\n");
		printf("1: Init Data\n");
		printf("2: Destroy List\n");
		printf("3: Push Head\n");
		printf("4: Push End\n");
		printf("5: Pop Head\n");
		printf("6: Pop End\n");
		printf("7: Push After Index\n");
		printf("8: Push Before Index\n");
		printf("9: Pop At Index\n");
		printf("10: Pop At current\n");
		printf("11: Set current\n");
		printf("12: Push At current\n");
		printf("13: Exit\n");
		printf("Your choice: ");
		scanf("%d", &choice);
		switch (choice) {
			case 1: initData(); printInt(); break;
			case 2: destroyList(); printInt(); break;
			case 3: {
				printf("Data: ");
				scanf("%d", &val); 
				pushHead(&head, val);
				printInt(); break;
			}
			case 4: {
				printf("Data: ");
				scanf("%d", &val); 
				pushEnd(&head, val);
				printInt(); break;
			}
			case 5: {
				printf("Head: %d\n", popHead(&head));
				printInt(); break;
			}
			case 6: {
				printf("End: %d\n", popEnd(&head));
				printInt(); break;
			}
			case 7: {
				printf("Data: ");
				scanf("%d", &val);
				printf("Position to Push After Index: ");
				scanf("%d", &pos);
				pushAfterIndex(pos, val);
				printInt(); break;
			}
			case 8: {
				printf("Data: ");
				scanf("%d", &val);
				printf("Position to Push Before Index: ");
				scanf("%d", &pos); 
				pushBeforeIndex(pos, val);
				printInt(); break;
			}
			case 9: {
				printf("Position to Pop Index: ");
				scanf("%d", &pos); 
				popAtIndex(pos);
				printInt(); break;
			}
			case 10: {
				popAt(&head, current);
				printInt(); break;
			}
			case 11: {
				printf("Position to set curent: ");
				scanf("%d", &pos);
				setCurrentIndex(pos);
				break;
			}
			case 12: {
				printf("Data: ");
				scanf("%d", &val); 
				pushAt(&head, current, val);
				printInt(); break;
			}
		}
	}

	return 0;
}