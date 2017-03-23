#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

void removeLastChar(char *s) {
	s[strlen(s)-1] = '\0';
}

node_t *head = NULL;
node_t *current;

void pushEnd(node_t * head, value_t val) { // Insert to the end
	node_t * current = head;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = malloc(sizeof(node_t));
	current->next->val = val;
	current->next->next = NULL;
}

void pushHead(node_t ** head, value_t val) {
	node_t * new_node;
	new_node = malloc(sizeof(node_t));
	new_node->val = val;
	new_node->next = *head;
	*head = new_node;
}

value_t popEnd(node_t * head) {
	value_t returnVal;

	// If the list has only 1 elem
	if (head->next == NULL) {
		returnVal = head->val;
		free(head);
		return returnVal;
	}

	node_t * current;
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


void destroyList() {
	while (head != NULL) {
		popHead(&head);
	}
}



int countList() {
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


void importFromTxt()
{
	FILE *fi = fopen("PhoneDB.txt","r");
	if (fi == NULL)
	{
		printf("Error opening PhoneDB.txt\n");
		return;
	}
	FILE *fo = fopen("PhoneDB.dat","wb");
	PHONE phone;
	while (ftell(fi) != SEEK_END)
	{
		phone.Model[0] = '\0';
		fscanf(fi,"%s%s%s%d",phone.Model,phone.Memory,phone.ScreenSize,&phone.Price);
		if (strlen(phone.Model) == 0) break;
		fwrite(&phone,sizeof(PHONE),1,fo);
	}
	fclose(fi);
	fclose(fo);
	printf("Import data from text successfully!\n\n");
}



void get_input(int start,int end)
{
	char c;
	while((c= getchar()) != '\n' && c != EOF);
	char filename[30];
	printf("Enter data filename: "); 
	fgets(filename, 30, stdin); removeLastChar(filename);
	destroyList();
	FILE *f = fopen(filename,"rb");
	if (f == NULL)
	{
		printf("Error opening %s\n\n", filename);
		return;
	}
	if (end == -1) // All
	{
		fseek(f,0,SEEK_END);
		end = ftell(f) / sizeof(PHONE);
	}

	if (start > end) {
		printf("Start position is incorrect\n");
		return;
	}

	int n = end - start + 1;

	if (fseek(f,(start - 1) * sizeof(PHONE),SEEK_SET))
	{
		printf("Error in fseek\n\n");
		return;
	}

	int i;
	value_t phone;
	for (i = 0; i < n; ++i) {
		fread(&phone,sizeof(PHONE),1,f);
		pushHead(&head, phone);
	}
	fclose(f);
}



void importFromDB()
{
	printf("You want:\n");
	printf(" 1. Full list\n");
	printf(" 2. A part\n");
	printf("Your choice: ");
	int choice,start,end = 0;
	scanf("%d",&choice);
	switch (choice) {
		case 1:
			start = 1;
			end = -1; // Read full
			break;
		case 2:
			printf("Input the start point: ");
			scanf("%d",&start);
			if (start <= 0)
			{
				printf("The start point must be a positive number\n\n");
				return;
			}
			printf("Input the end point: ");
			scanf("%d",&end);
			break;
		default:
			printf("Invalid command\nThe choice must be from 1 to 2\n\n");
			return;
	}
	get_input(start,end);
	if (countList() == 0) {
		return;
	}

	printf("%*s%*s%*s%*s%*s\n",-3,"STT",-50,"MODEL",-20,"MEMORY",-30,"SCREEN SIZE",-15,"PRICE (VND)");
	
	node_t *current = head;
	int i = 0;
	while (current != NULL) {
		printf("%*d%*s%*s%*s%*d\n",-3,i+start,-50,current->val.Model,-20,current->val.Memory,-30,current->val.ScreenSize,-15,current->val.Price);
		current = current->next;
		i++;
	}
	printf("\n");
}

void printDB()
{
	int n;
	if (countList() == 0)
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

void searchByModelName()
{
	char c;
	while((c= getchar()) != '\n' && c != EOF); 
	char model[50];
	printf("Input the model you want to find: ");
	fgets(model, 30, stdin); removeLastChar(model);

	if (countList() == 0)
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
			}
		}
		current = current->next;
	}
	printf("Found: %d\n", found);
	
}

void searchByMaxPrice() {
	int maxPrice;
	printf("Input Max Price: ");
	scanf("%d", &maxPrice);

	if (countList() == 0)
	return;
	
	int found = 0;
	printf("%*s%*s%*s%*s%*s\n",-3,"STT",-50,"MODEL",-20,"MEMORY",-30,"SCREEN SIZE",-15,"PRICE (VND)");
	node_t *current = head;
	int i = 1;
	while (current != NULL) {
		if (current->val.Price <= maxPrice) {
			printf("%*d%*s%*s%*s%*d\n",-3,i++,-50,current->val.Model,-20,current->val.Memory,-30,current->val.ScreenSize,-15,current->val.Price);
			found++;
		}
		current = current->next;
	}
	printf("Found: %d\n", found);

}

void exportToDataFile() {
	char c;
	while((c= getchar()) != '\n' && c != EOF);
	char filename[30];
	printf("Enter data filename: "); 
	fgets(filename, 30, stdin); removeLastChar(filename);
	FILE *f = fopen(filename,"wb");
	if (f == NULL)
	{
		printf("Error opening %s\n\n", filename);
		return;
	}

	node_t *current = head;
	int i = 0;
	while (current != NULL) {
		fwrite(&current->val,sizeof(PHONE),1,f);
		current = current->next;
		i++;
	}
	fclose(f);
	printf("Done!\n");
}

int main()
{
	int select;
	while (select != 7) {
		printf("\n\n");
		printf(" 1. Import DB from text\n");
		printf(" 2. Import from .dat file\n");
		printf(" 3. Print all database\n");
		printf(" 4. Find by model name\n");
		printf(" 5. Search by max price\n");
		printf(" 6. Export to .dat file\n");
		printf(" 7. Exit\n");
		printf("Your choice: ");
		scanf("%d",&select);
		switch (select) {
		case 1: importFromTxt(); break;
		case 2: importFromDB(); break;
		case 3: printDB(); break;
		case 4: searchByModelName(); break;
		case 5: searchByMaxPrice(); break;
		case 6: exportToDataFile(); break;
		case 7: break;
		default:
			printf("Not a valid! only 1 > 7\n\n");
			break;
		}
	}
}
