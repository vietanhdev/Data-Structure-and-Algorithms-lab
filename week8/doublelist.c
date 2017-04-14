#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define value_t STUDENT

#define ID_LENGTH 10
#define NAME_LENGTH 30

typedef struct {
	char id[ID_LENGTH];
	char name[NAME_LENGTH];
	int grade;
	int Price;
} STUDENT;

typedef struct node {
	value_t val;
	struct node * next;
	struct node * prev;
} node_t;

node_t *head = NULL;
node_t *tail = NULL;

node_t *current;

void removeLastChar(char *s) {
	if (strlen(s) > 0) {
		if (s[strlen(s)-1] == '\n')
			s[strlen(s)-1] = '\0';
	}
}


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
	if (*head != NULL) {

	}
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
void pushAfter(node_t ** head, node_t * node_ptr, value_t val) {

	// if list is empty
	if (*head == NULL) {
		pushHead(head, val);
		return;
	}

	node_t * current;
	current = *head;

	while (current != NULL) {
		if (current == node_ptr) {
			break;
		}
	}

	// if node_ptr is not in the list
	if (current == NULL) {
		pushEnd(head, val);
	} else {
		node_t * new_node;
		new_node = malloc(sizeof(node_t));
		new_node->val = val;
		new_node->next = current->next;
		current->next = new_node;
	} 

}

void pushAtIndex(int pos, value_t val) {
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
		returnVal = popHead(head);
		return returnVal;
	}
	
	node_t * prev = *head;
	while (prev->next != current && prev != NULL) {
		prev = prev->next;
	}

	if (prev->next != NULL) { // current is in list
		returnVal = current->val;
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

void displayDB(node_t * head)
{
	int n;
	if (countList(head) == 0)
	return;
	
	printf("%*s%*s%*s%*s\n",-3,"STT",-ID_LENGTH,"ID",-NAME_LENGTH,"NAME",5,"GRADE");
	
	int i = 1;
	int cnt;
	node_t *current = head;
	while (current != NULL) {
		printf("%*d%*s%*s%*d\n",-3,i++,-ID_LENGTH,current->val.id,-NAME_LENGTH,current->val.name,5,current->val.grade);
		current = current->next;
		cnt++;
		if (cnt == 25) // reach the final line of a part
		{
			printf("Press any key to continue...");
			char c;
			scanf("%*c%c",&c);
			cnt = 1;
		}
	}
	printf("\n");
}


value_t inputAStudent() {
	value_t val;
	// clear input buffer
	char c;
	while((c= getchar()) != '\n' && c != EOF);

	printf("ID :"); fgets(val.id, ID_LENGTH, stdin); removeLastChar(val.id);
	printf("NAME :"); fgets(val.name, NAME_LENGTH, stdin); removeLastChar(val.name);
	printf("GRADE :"); scanf("%d", &(val.grade));

	return val;
}


void InsertNew() {
	printf("*** Add new student\n");
	value_t student = inputAStudent();
	pushEnd(&head, student);
}


node_t * findOneById(node_t * head, char *id) {
	if (countList(head) == 0)
	return NULL;
	
	node_t *current = head;
	int i = 0;
	while (current != NULL) {
		for (int j=0; j+strlen(id)-1<strlen(current->val.id); j++)
		{
			int check = 1;
			for (int k=0; k<strlen(id); k++)
				if (tolower(id[k]) != tolower(current->val.id[j+k]))
				{
					check = 0;
					break;
				}
			if (check) {
				return current;
			}
		}
		current = current->next;
	}
	return NULL;
}


void SearchByID() {

	printf("\n");
	char c;
	while((c= getchar()) != '\n' && c != EOF); 
	char id[ID_LENGTH];
	printf("Input the id you want to find: ");
	fgets(id, ID_LENGTH, stdin); removeLastChar(id);

	node_t * result = findOneById(head, id);

	if (result == NULL) {
		printf("Not found\n");
		return;
	}

	printf("Matched!\n");
	printf("%*s%*s%*d\n",-ID_LENGTH,result->val.id,-NAME_LENGTH,result->val.name,-5,result->val.grade);

	printf("\n");
}

void DeleteByID() {
	printf("\n");
	char c;
	while((c= getchar()) != '\n' && c != EOF); 
	char id[ID_LENGTH];
	printf("Input the id you want to delete: ");
	fgets(id, ID_LENGTH, stdin); removeLastChar(id);

	node_t * result = findOneById(head, id);

	if (result == NULL) {
		printf("Not found\n");
		return;
	}

	printf("Matched!\n");
	printf("%*s%*s%*d\n",-ID_LENGTH,result->val.id,-NAME_LENGTH,result->val.name,-5,result->val.grade);

	int prompt;
	printf("Do you want to delete this student? (1: yes; 0: no) choice: ");
	scanf("%d", &prompt);

	if (prompt == 1) {
		popAt(&head, result);
	}

	printf("deleted!\n");
}


void SortByGrade(node_t * head) {
	if (head == NULL) {
		return;
	}

	node_t * curr;
	value_t tmp;
	int i;
	int n = countList(head);
	for (i = 0; i < n; i++) {
		for (curr = head; curr->next != NULL; curr = curr->next){
			if (curr->val.grade < curr->next->val.grade) {
				tmp  = curr->val;
				curr->val = curr->next->val;
				curr->next->val = tmp;
			}
		}
		n--;
	}
}


int main(int argc, char const *argv[]){
	
	int pos;

	int select;
	while (select != 12) {
		printf("SMS\n");
		displayDB(head);
		printf("1. Insert a student\n");
		printf("2. Search by ID\n");
		printf("3. Detete by ID\n");
		printf("4. Sort by grade\n");
		printf("5. Quit\n");
		printf("Your choice: ");
		scanf("%d", &select);
		switch(select) {
			case 1: InsertNew(); break;
			case 2: SearchByID(); break;
			case 3: DeleteByID(); break;
			case 4: SortByGrade(head); break;
			case 5:
			default: printf("Invalid selection!\n");
		}
	}
	return 0;
}