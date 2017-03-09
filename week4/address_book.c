#include <stdio.h>
#include <stdlib.h>


typedef struct phoneaddress {
	char name[20];
	char tel[11];
	char email[25];
} phoneaddress_t;


int main(int argc, char**argv) {
	FILE *fptr;
	int i;

	phoneaddress_t *data;
	int n = 0;

	printf("Number of input: \n"); scanf("%d", &n);
	data = malloc(n * sizeof(phoneaddress_t));
	for (i = 0; i < n; i++) {
		printf("Number %d\n", i+1);
		printf("Name: "); scanf ("%[^\n]%*c", data[i].name);
		printf("Tel: "); scanf ("%[^\n]%*c", data[i].tel);
		printf("Name: "); scanf ("%[^\n]%*c", data[i].email);
	}

	if ((fptr=fopen("phonebook.dat", "wb")) == NULL) {
		printf("Cannot open file to read\n");
		return 1;
	}

	for (i = 0; i < n; i++) {
		fwrite(data[i], sizeof(phoneaddress_t), 1, fptr);
	}
		
   fclose(fptr);
  
  return 0;
}
