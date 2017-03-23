#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct address_struct {
	char name[20];
	char tel[11];
	char email[25];
} address_t;

struct node {
	address_t data;
	struct list_el *next;
};

typedef struct list_el node_addr_t;


node_addr_t *root;
node_addr_t *cur;
address_t contact;



void removeLastChar(char *s) {
	s[strlen(s)-1] = '\0';
}

node_addr_t * insertBefore(address_t addr, node_addr_t *next) {
	node_addr_t * new = (node_addr_t *)malloc(sizeof(node_addr_t));
	new->data = addr;
	new->next = next;
	return new;
}

void insertAtHead(address_t addr) {
	root = insertBefore(addr, root);
}

node_addr_t * inserAfter(address_t addr, node_addr_t *prev) {
	node_addr_t * new = (node_addr_t *)malloc(sizeof(node_addr_t));
	new->data = addr;
	new->next = prev->next;
	prev->next = new;
	return new;
}

void inputContact (address_t *contact) {
	printf("============================\n");
	printf("Nhap ten: ");
	fgets(contact->name, 20, stdin); removeLastChar(contact->name);
	printf("Nhap sdt: ");
	fgets(contact->tel, 11, stdin); removeLastChar(contact->tel);
	printf("Nhap email: ");
	fgets(contact->email, 25, stdin); removeLastChar(contact->email);
	printf("============================\n");
}

void printContact (address_t contact) {
	printf("============================\n");
	printf("Ten: %s\n", contact.name);
	printf("Dien thoai: %s\n", contact.tel);
	printf("Email: %s\n", contact.email);
	printf("============================\n");
}

void printAll() {
	node_addr_t *p;
	for ( p = root; p != NULL; p = p->next) {
		printContact(p->data);
	}
}

void readFromDAT() {
	int readNum;
	FILE *fptr;
	int i;
	address_t contact;

	if ((fptr=fopen("phonebook.dat", "rb")) == NULL) {
		printf("Cannot open file to read\n");
		return;
	}

	while(!feof(fptr)) {
		readNum = fread(&contact, sizeof(address_t), 1, fptr);
		if (readNum > 0) {
			insertAtHead(contact);
		}
	}	
   	fclose(fptr);
}


int main(int argc, char const *argv[])
{

	// inputContact(&contact);
	// root = insertBefore(contact, NULL);
	// cur = root;

	// inputContact(&contact);
	// cur = insertBefore(contact, root); // Insert at Head
	// root = cur;

	// inputContact(&contact);
	// cur = inserAfter(contact, cur); // Insert after cur

	// printf("============================\n");
	// printf("============================\n");
	// printf("============================\n");


	// printContact(root->data);
	// printContact(root->next->data);
	// printContact(root->next->next->data);

	readFromDAT();
	printAll();

	return 0;
}