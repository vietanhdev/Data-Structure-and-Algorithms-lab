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
	float grade;
} STUDENT;

typedef struct node {
	value_t val;
	struct node * next;
	struct node * prev;
} node_t;

node_t *head = NULL; node_t *tail = NULL;
node_t *head2 = NULL; node_t *tail2 = NULL;
node_t *current;

int countList(node_t * head);

void pushHead(node_t ** head, node_t ** tail, value_t val);
void pushEnd(node_t ** head, node_t ** tail, value_t val);
void pushAfter(node_t ** head, node_t ** tail, node_t * node_ptr, value_t val);
void pushAtIndex(node_t ** head, node_t ** tail, int node_index, value_t val);

value_t popHead(node_t ** head, node_t ** tail);
value_t popEnd(node_t ** head, node_t ** tail);
value_t popAt(node_t ** head, node_t ** tail, node_t * node_ptr);
value_t popAtIndex(node_t ** head, node_t ** tail, int node_index);

void destroyList(node_t ** head, node_t ** tail);


void removeLastChar(char *s);



void destroyList(node_t ** head, node_t ** tail) {
	while (*head != NULL) {
		popHead(head, tail);
	}
}


void importDB()
{
	//========================= OPEN FILE =============================
	char filename[50];
	char c;
	while((c= getchar()) != '\n' && c != EOF); 
	printf("File to import: ");
	fgets(filename, 50, stdin); removeLastChar(filename);
	
	FILE *fin = fopen(filename,"rb");
	if (fin == NULL)
	{
		printf("Error opening %s\n\n", filename);
		return;
	}

	//========================= READ FILE =============================

	value_t val;
	int readNum = 0;

	int prompt = 0;
	printf("Insert at head or at tail? (1: at head, 0: at tail) : "); scanf("%d", &prompt);

	if (prompt == 1) {
		while (!feof(fin)) {
			readNum = fread(&val,sizeof(value_t),1,fin);
			if (readNum > 0) {
				if (val.grade > 8) {
					pushHead(&head, &tail, val);
				} else {
					pushHead(&head2, &tail2, val);
				}
			}
		}	
	} else {
		while (!feof(fin)) {
			readNum = fread(&val,sizeof(value_t),1,fin);
			if (readNum > 0) {
				if (val.grade > 8) {
					pushEnd(&head, &tail, val);
				} else {
					pushEnd(&head2, &tail2, val);
				}
			}
		}	
	}
	

	fclose(fin);
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
		printf("%*d%*s%*s%.1f\n",-3,i++,-ID_LENGTH,current->val.id,-NAME_LENGTH,current->val.name,current->val.grade);
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
	printf("GRADE :"); scanf("%f", &(val.grade));

	return val;
}


void saveToFile(node_t * head) {
	char filename[50];
	char c;
	while((c= getchar()) != '\n' && c != EOF); 
	printf("file name: ");
	fgets(filename, 50, stdin); removeLastChar(filename);

	FILE *f = fopen(filename,"wb");
	if (f == NULL)
	{
		printf("Error opening %s\n\n", filename);
		return;
	}

	node_t * current = head;
	while (current != NULL) {
		fwrite(&(current->val),sizeof(value_t),1,f);
		current = current->next;
	}

	fclose(f);
}


void InsertNew() {
	printf("*** Add new student\n");
	value_t student = inputAStudent();
	if (student.grade > 8) {
		pushEnd(&head, &tail, student);
	} else {
		pushEnd(&head2, &tail2, student);
	}
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


void move() {
	node_t * node;
	node_t * node_next;
	for (node = head2; node != NULL; node = node_next) {
		node_next = node->next;
		if (node->val.grade >= 7.5) {
			pushEnd(&head, &tail, popAt(&head2, &tail2, node));
		}
	}
}

void concat2to1() {
	node_t * node;
	node_t * node_next;
	for (node = head2; node != NULL; node = node_next) {
		node_next = node->next;
		pushEnd(&head, &tail, node->val);
	}
}

void sortByGrade(node_t * head) {
	if (head == NULL) {
		return;
	}

	node_t * curr;
	node_t * next_node;
	value_t tmp;
	int i;
	int n = countList(head);
	for (i = 0; i < n; i++) {
		for (curr = head; curr->next != NULL; curr = curr->next){
			next_node = curr->next;
			if (curr->val.grade < next_node->val.grade) {
				tmp  = curr->val;
				curr->val = next_node->val;
				next_node->val = tmp;
			}
		}
		n--;
	}
}

int main(int argc, char const *argv[]){
	
	int pos;

	int select;
	while (select != 8) {
		printf("SMS\n");
		printf("LIST 1\n");
		displayDB(head);
		printf("LIST 2\n");
		displayDB(head2);
		printf("1. Insert a student\n");
		printf("2. Save list 1 to file\n");
		printf("3. Save list 2 to file\n");
		printf("4. Load from file\n");
		printf("5. Move grade>=7.5 from list2 to list1\n");
		printf("6. Concat list 2 to list 1\n");
		printf("7. Concat list 2 to list 1 and sort\n");
		printf("8. Quit\n");
		printf("Your choice: ");
		scanf("%d", &select);
		switch(select) {
			case 1: InsertNew(); break;
			case 2: saveToFile(head); break;
			case 3: saveToFile(head2); break;
			case 4: importDB(); break;
			case 5: move(); break;
			case 6: concat2to1(); break;
			case 7: concat2to1(); sortByGrade(head); break;
			case 8: break;
			default: printf("Invalid selection!\n");
		}
	}
	return 0;
}



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

void pushHead(node_t ** head, node_t ** tail, value_t val) {
	node_t * new_node;
	new_node = malloc(sizeof(node_t));
	new_node->val = val;

	new_node->next = *head;

	if (*head == NULL) {
		*tail = new_node;
	} else {
		(*head)->prev = new_node;
	}

	*head = new_node;
}

void pushEnd(node_t ** head, node_t ** tail, value_t val) {
	if (*tail == NULL) {
		pushHead(head, tail, val);
		return;
	}

	node_t * new_node;
	new_node = malloc(sizeof(node_t));
	new_node->val = val;
	new_node->prev = *tail;
	(*tail)->next = new_node;
	new_node->next = NULL;

	*tail = new_node;
	
}


void pushAt(node_t ** head, node_t ** tail, node_t * node_ptr, value_t val) {

	node_t * current = *head;
	while (current != NULL) {
		if (current == node_ptr) {
			break;
		}
		current = current->next;
	}

	// if node_ptr is not in the list
	if (current == NULL) {
		pushEnd(head, tail, val);
		return;
	};

	// create new node
	node_t * new_node;
	new_node = malloc(sizeof(node_t));
	new_node->val = val;

	// connect before
	new_node->prev = current->prev;
	if (current->prev != NULL)
		current->prev->next = new_node;

	// connect after
	new_node->next = current;
	current->prev = new_node;

}


void pushAfter(node_t ** head, node_t ** tail, node_t * node_ptr, value_t val) {

	// if list is empty
	if (*head == NULL) {
		pushHead(head, tail, val);
		return;
	}

	node_t * current;
	current = *head;

	// find node_ptr position
	while (current != NULL) {
		if (current == node_ptr) {
			break;
		}
	}

	// if node_ptr is not in the list
	if (current == NULL) {
		pushEnd(head, tail, val);
		return;
	}

	// there is only one element in list || insert position at the end of list
	if (*tail == NULL || current->next == NULL) {
		pushEnd(head, tail, val);
		return;
	}

	// create new node
	node_t * new_node;
	new_node = malloc(sizeof(node_t));
	new_node->val = val;

	// connect after
	new_node->next = current->next;
	current->next->prev = new_node;

	// connect before
	new_node->prev = current;
	current->next = new_node;

}


value_t popHead(node_t ** head, node_t ** tail) {
	value_t returnVal;

	if (*head == NULL) { // No elem in list
		return returnVal;
	}

	node_t * next_node = (*head)->next;

	// the is > 1 elem in list
	if (next_node != NULL) {
		next_node->prev = NULL;
	// the is 1 elem in list
	} else {
		*tail = NULL;
	}

	returnVal = (*head)->val;
	free(*head);
	*head = next_node;

	return returnVal;
}

value_t popEnd(node_t ** head, node_t ** tail) {
	value_t returnVal;

	if (*head == NULL) { // No elem in list
		return returnVal;
	}

	// previous node of tail
	node_t * prev_node = (*tail)->prev;

	// the is > 1 elem in list
	if (prev_node != NULL) {
		prev_node->next = NULL;
	// the is 1 elem in list
	} else {
		*head = NULL;
	}

	returnVal = (*tail)->val;
	free(*tail);
	*tail = prev_node;

	return returnVal;
}


value_t popAt(node_t ** head, node_t ** tail, node_t * node_ptr) {
	value_t returnVal;

	// node_ptr at head
	if (node_ptr == *head) {
		returnVal = popHead(head, tail);
		return returnVal;
	}

	// node_ptr at tail
	if (node_ptr == *tail) {
		returnVal = popEnd(head, tail);
		return returnVal;
	}
	
	node_t * current = *head;
	while (current != NULL) {
		if (current == node_ptr) {
			break;
		}
		current = current->next;
	}

	if (current != NULL) { // current is in list
		returnVal = current->val;

		current->prev->next = current->next;
		current->next->prev = current->prev;

		free(current);
	}

	return returnVal;
}


value_t popAtIndex(node_t ** head, node_t ** tail, int node_index) {
	value_t returnVal;
	if (node_index < 0 || node_index >= countList(*head)) {
		return returnVal;
	}

	// find the node_index position
	node_t * current = *head;
	int i;
	for (i = 0; i < node_index; ++i) {
		current = current->next;
	}

	returnVal = popAt(head, tail, current);

	return returnVal;
}

