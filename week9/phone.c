#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define value_t PHONE

typedef struct {
	char Model[50];
	char Memory[20];
	char ScreenSize[30];
	int Price;
} PHONE;

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

	destroyList(&head, &tail);

	value_t phone;
	int readNum = 0;

	int prompt = 0;
	printf("Insert at head or at tail? (1: at head, 0: at tail) : "); scanf("%d", &prompt);

	if (prompt == 1) {
		while (!feof(fin)) {
			readNum = fread(&phone,sizeof(PHONE),1,fin);
			if (readNum > 0) {
				pushHead(&head, &tail, phone);
			}
		}	
	} else {
		while (!feof(fin)) {
			readNum = fread(&phone,sizeof(PHONE),1,fin);
			if (readNum > 0) {
				pushEnd(&head, &tail, phone);
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

	int cnt = 3;
	
	printf("%*s%*s%*s%*s%*s\n",-3,"STT",-50,"MODEL",-20,"MEMORY",-30,"SCREEN SIZE",-15,"PRICE (VND)");
	
	int i = 1;
	node_t *current = head;
	while (current != NULL) {
		printf("%*d%*s%*s%*s%*d\n",-3,i++,-50,current->val.Model,-20,current->val.Memory,-30,current->val.ScreenSize,-15,current->val.Price);
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

void displayDB_Reverse(node_t * head, node_t * tail)
{
	int n;
	if (countList(head) == 0)
	return;

	int cnt = 3;
	
	printf("%*s%*s%*s%*s%*s\n",-3,"STT",-50,"MODEL",-20,"MEMORY",-30,"SCREEN SIZE",-15,"PRICE (VND)");
	
	int i = 1;
	node_t *current = tail;
	while (current != NULL) {
		printf("%*d%*s%*s%*s%*d\n",-3,i++,-50,current->val.Model,-20,current->val.Memory,-30,current->val.ScreenSize,-15,current->val.Price);
		current = current->prev;
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

void DBtoFile(node_t * head, char * filename)
{
	int n;
	if (countList(head) == 0)
	return;

	FILE *f = fopen(filename,"w");
	if (f == NULL)
	{
		printf("Error opening %s\n\n", filename);
		return;
	}
	
	fprintf(f, "%*s%*s%*s%*s%*s\n",-3,"STT",-50,"MODEL",-20,"MEMORY",-30,"SCREEN SIZE",-15,"PRICE (VND)");
	
	int i = 1;
	node_t *current = head;
	while (current != NULL) {
		fprintf(f, "%*d%*s%*s%*s%*d\n",-3,i++,-50,current->val.Model,-20,current->val.Memory,-30,current->val.ScreenSize,-15,current->val.Price);
		current = current->next;
	}

	fclose(f);
}


value_t inputAPhone() {
	value_t phone;
	// clear input buffer
	char c;
	while((c= getchar()) != '\n' && c != EOF);

	printf("Model :"); fgets(phone.Model, 50, stdin); removeLastChar(phone.Model);

	printf("Memory :"); fgets(phone.Memory, 20, stdin); removeLastChar(phone.Memory);

	printf("ScreenSize :"); fgets(phone.ScreenSize, 30, stdin); removeLastChar(phone.ScreenSize);

	printf("Price: "); scanf("%d", &phone.Price);

	return phone;
}

void addNewPhone() {

	printf("Add a phone: \n");

	pushEnd(&head, &tail, inputAPhone());

	printf("Added a new phone!\n");
}

void insertAtPos() {
	int position;

	do {
		printf("Enter phone index: "); scanf("%d", &position);
		if (position <= 0) {
			printf("Index must be a positive number!\n");
		}
	} while (position <= 0);

	printf("%d\n", position);

	value_t new_phone = inputAPhone();
	pushAtIndex(&head, &tail, --position, new_phone);

}

void deleteAtPos() {
	int position;

	printf("Enter phone index to delete: \n"); scanf("%d", &position);
	
	if (position <= 0 || position > countList(head)) {
		printf("Position is not in the list!\n");
		return;
	};

	popAtIndex(&head, &tail, --position);
	printf("done!\n");
}

void deleteCurr() {
	popAt(&head, &tail, current);
	printf("done!\n");
}

void deleteFirst() {
	popHead(&head, &tail);
	printf("done!\n");
}

void searchAndUpdate() {
	char c;
	while((c= getchar()) != '\n' && c != EOF); 
	char model[50];
	printf("Input the model you want to find: ");
	fgets(model, 30, stdin); removeLastChar(model);

	if (countList(head) == 0)
	return;
	
	printf("%*s%*s%*s%*s%*s\n",-3,"STT",-50,"MODEL",-20,"MEMORY",-30,"SCREEN SIZE",-15,"PRICE (VND)");
	node_t *current = head;
	int i = 0;
	int found = 0;
	while (current != NULL) {
		for (int j=0; j+strlen(model)-1<strlen(current->val.Model); j++)
		{
			int check = 1;
			for (int k=0; k<strlen(model); k++)
				if (tolower(model[k]) != tolower(current->val.Model[j+k]))
				{
					check = 0;
					break;
				}
			if (check) {
				found++;
				printf("%*d%*s%*s%*s%*d\n",-3,i++,-50,current->val.Model,-20,current->val.Memory,-30,current->val.ScreenSize,-15,current->val.Price);
				printf("Update value:\n");
				current->val = inputAPhone();
				return;
			}
		}
		current = current->next;
	}
	printf("Found: %d\n", found);
}

void setCurrentIndex(int pos, node_t ** current) {

	if (pos <= 0 || pos > countList(head)) {
		printf("Invalid Position (valid: 1 <= pos <= %d\n", countList(head));
		return;
	}

	int i;
	*current = head;
	for (i = 1; i < pos; ++i) {
		(*current) = (*current)->next;
	}

}

void printAPhone(node_t * current) {
	printf("*** Current: \n");
	printf("Model: %s\n", current->val.Model);
	printf("Memory: %s\n", current->val.Memory);
	printf("ScreenSize: %s\n", current->val.ScreenSize);
	printf("Price: %d\n", current->val.Price);
}


void divideAndExtract() {
	int begin, end;
	printf("Begin: \n"); scanf("%d", &begin);
	if (begin <= 0 || begin > countList(head)) {
		printf("invalid begin pos\n");
		return;
	}
	printf("End: \n"); scanf("%d", &end);
	if (end <= 0 || end > countList(head) || end < begin) {
		printf("invalid end pos\n");
		return;
	}

	node_t * begin_node;
	node_t * end_node;
	setCurrentIndex(begin, &begin_node); printAPhone(begin_node);
	setCurrentIndex(end, &end_node); printAPhone(end_node);

	for (node_t * node = begin_node; node != end_node->next; node = node->next) {
		pushEnd(&head2, &tail2, node->val);
	}

	int n = end - begin + 1;
	for (int i = 0; i < n; ++i) {
		popAtIndex(&head, &tail, begin-1);
	}

	printf("Extracted list:\n");
	displayDB(head2);

	printf("Remaining list:\n");
	displayDB(head);


}



void splitList(int begin, int end) {

	// index (from 0) to pos (from 1)
	begin++;
	end++;
	
	node_t * begin_node;
	node_t * end_node;
	setCurrentIndex(begin, &begin_node);
	setCurrentIndex(end, &end_node);

	for (node_t * node = begin_node; node != end_node->next; node = node->next) {
		pushEnd(&head2, &tail2, node->val);
		popAt(&head, &tail, node);
	}

	printf("Extracted list:\n");
	displayDB(head2);

	printf("Remaining list:\n");
	displayDB(head);

}


void splitList_Input () {
	int begin, end;
	printf("Begin(from 0): \n"); scanf("%d", &begin);
	if (begin < 0 || begin > countList(head)-1) {
		printf("invalid begin index\n");
		return;
	}
	printf("End(from 0): \n"); scanf("%d", &end);
	if (end < 0 || end > countList(head)-1 || end < begin) {
		printf("invalid end index\n");
		return;
	}
	splitList(begin, end);

}

// TODO
void reverseList(node_t ** head) {
	if (*head == NULL) {
		return;
	}

	if ((*head)->next == NULL) {
		return;
	}

	node_t * current = *head;
	node_t * prev_node = NULL;
	node_t * next_node;

	while (current != NULL) {
		next_node = current->next;
		current->next = prev_node;
		prev_node = current;
		current = next_node;
	}

	*head = prev_node;

}

void saveToFile() {
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




int main(int argc, char const *argv[]){
	
	int pos;

	int select;
	while (select != 13) {
		printf("PHONE DB\n");
		printf("1. Import from PhongDB.dat\n");
		printf("2. Display\n");
		printf("3. Add new phone\n");
		printf("4. Insert at position\n");
		printf("5. Delete at position\n");
		printf("6. Delete current\n");
		printf("7. Delete first\n");
		printf("8. Delete last\n");
		printf("9. Search and update\n");
		printf("10. Divide and extract\n");
		printf("11. Reverse list\n");
		printf("12. Save to file\n");
		printf("13. Quit\n");
		printf("111. Set current by Index\n");
		printf("222. splitList\n");
		printf("Your choice: ");
		scanf("%d", &select);
		switch(select) {
			case 1: importDB(); displayDB(head); break;
			case 2: displayDB(head); break;
			case 3: addNewPhone(); break;
			case 4: insertAtPos(); break;
			case 5: deleteAtPos(); break;
			case 6: deleteCurr(); break;
			case 7: deleteFirst(); break;
			case 8: popEnd(&head, &tail); break;
			case 9: searchAndUpdate(); break;
			case 10: divideAndExtract(); break;
			case 11: reverseList(&head); displayDB(head); break;
			case 12: saveToFile(); break;
			case 111: printf("Enter position: \n"); scanf("%d", &pos); setCurrentIndex(pos, &current); printAPhone(current); break;
			case 222: splitList_Input(); DBtoFile(head, "file1.txt"); DBtoFile(head2, "file2.txt"); break;
			case 13:
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


void pushAtIndex(node_t ** head, node_t ** tail, int node_index, value_t val) {
	if (node_index < 0 || node_index >= countList(*head)) {
		printf("Invalid Position!\n");
		return;
	}
	
	// find the node_index position
	node_t * current = *head;
	int i;
	for (i = 0; i < node_index; ++i) {
		current = current->next;
	}

	printAPhone(current);
	pushAt(head, tail, current, val);
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

