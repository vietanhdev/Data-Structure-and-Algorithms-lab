#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct phoneaddress {
	char name[45];
	char tel[30];
} phoneaddress_t;

void writeData() {
	FILE *fptr;
	int i;

	phoneaddress_t *data;
	int n = 0;

	printf("Number of input: "); scanf("%d", &n);
	data = malloc(n * sizeof(phoneaddress_t));
	if (data == NULL) {
		printf("Failed to allocate memory!\n");
	}
	while ( getchar() != '\n' );
	for (i = 0; i < n; i++) {
		printf("*** Number %d\n", i+1);
		printf("Name: "); fgets(data[i].name, 45, stdin); data[i].name[strlen(data[i].name) - 1] = '\0';
		printf("Tel: "); fgets(data[i].tel, 30, stdin); data[i].tel[strlen(data[i].tel) - 1] = '\0';
	}

	if ((fptr=fopen("phone.dat", "wb")) == NULL) {
		printf("Cannot open file to write\n");
		return;
	}

	for (i = 0; i < n; i++) {
		fwrite(&data[i], sizeof(phoneaddress_t), 1, fptr);
	}
		
   	fclose(fptr);
   	free(data);
}


void readData(){
	FILE *fptr;
	int i;
	// Re-read all data
   	phoneaddress_t *data2;
	int n2 = 0;
	int readNum;

	if ((fptr=fopen("phone.dat", "rb")) == NULL) {
		printf("Cannot open file to read\n");
		return;
	}

	while(!feof(fptr)) {
		data2 = realloc(data2, (n2+1) * sizeof(phoneaddress_t));
		if (data2 == NULL) {
			printf("Failed to allocate memory!\n");
		}
		readNum = fread(&data2[n2], sizeof(phoneaddress_t), 1, fptr);
		if (readNum > 0) n2++;
	}

	for (i = 0; i < n2; i++) {
		printf("*** Number %d\n", i+1);
		printf("Name: %s\n", data2[i].name);
		printf("Tel: %s\n", data2[i].tel);
	}

	for (i = 0; i < n2; i++) {
		fwrite(&data2[i], sizeof(phoneaddress_t), 1, fptr);
	}
		
   	fclose(fptr);
   	free(data2);
}


int main(int argc, char**argv) {
	int select;
	while(1) {
		printf("1: Read data file\n2: Write data\n3: Exit\nSelection: "); scanf("%d", &select);
		switch(select) {
			case 1: readData(); break;
			case 2: writeData(); break;
			case 3: return 0;
		}
	}
  
  return 0;
}
