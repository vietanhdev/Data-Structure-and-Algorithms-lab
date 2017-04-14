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
} node_t;

node_t *head = NULL;
node_t *current;

node_t *head2 = NULL;

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


void importDB()
{
	char filename[50];
	char c;
	while((c= getchar()) != '\n' && c != EOF); 
	printf("file name: ");
	fgets(filename, 50, stdin); removeLastChar(filename);
	destroyList();
	FILE *fin = fopen(filename,"rb");
	if (fin == NULL)
	{
		printf("Error opening %s\n\n", filename);
		return;
	}


	int i;

	value_t phone;
	
	int readNum = 0;
	while (!feof(fin)) {
		readNum = fread(&phone,sizeof(PHONE),1,fin);
		if (readNum > 0) {
			pushEnd(&head, phone);
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

	pushEnd(&head, inputAPhone());

	printf("Added a new phone!\n");
}

void insertAtPos() {
	int position;

	do {
		printf("Enter phone index: \n"); scanf("%d", &position);
		if (position <= 0) {
			printf("Index must be a positive number!\n");
		}
	} while (position <= 0);
	
	position--;

	pushAtIndex(position, inputAPhone());

}

void deleteAtPos() {
	int position;

	printf("Enter phone index to delete: \n"); scanf("%d", &position);
	
	if (position <= 0 || position > countList(head)) {
		printf("Position is not in the list!\n");
		return;
	};

	position--;

	popAtIndex(position);
	printf("done!\n");
}

void deleteCurr() {
	popAt(&head, current);
	printf("done!\n");
}

void deleteFirst() {
	popHead(&head);
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
		pushEnd(&head2, node->val);
		popAt(&head, node);
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
		pushEnd(&head2, node->val);
		popAt(&head, node);
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

void reverseList(node_t ** head, node_t ** tail) {
	if (*head == NULL) {
		return;
	}

	if ((*head)->next == NULL) {
		return;
	}

	int i;
	for (i = 0; i < countList(*head); ++i) {
		pushHead(head, tail, popEnd(head, tail));
	}

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
	while (select != 12) {
		printf("PHONE DB\n");
		printf("1. Import from PhongDB.dat\n");
		printf("2. Display\n");
		printf("3. Add new phone\n");
		printf("4. Insert at position\n");
		printf("5. Delete at position\n");
		printf("6. Delete current\n");
		printf("7. Delete first\n");
		printf("8. Search and update\n");
		printf("9. Divide and extract\n");
		printf("10. Reverse list\n");
		printf("11. Save to file\n");
		printf("12. Quit\n");
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
			case 8: searchAndUpdate(); break;
			case 9: divideAndExtract(); break;
			case 10: reverseList(&head, &tail); displayDB(head); break;
			case 11: saveToFile(); break;
			case 111: printf("Enter position: \n"); scanf("%d", &pos); setCurrentIndex(pos, &current); printAPhone(current); break;
			case 222: splitList_Input(); DBtoFile(head, "file1.txt"); DBtoFile(head2, "file2.txt"); break;
			case 12:
			default: printf("Invalid selection!\n");
		}
	}
	return 0;
}