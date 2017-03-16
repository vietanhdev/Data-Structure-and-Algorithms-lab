#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct phoneaddress {
	char name[45];
	char tel[30];
} phoneaddress_t;

void phoneread(const char *filein){

	FILE *fptr;
	int i;
	// Re-read all data
   	phoneaddress_t *data2;
	int n2 = 0;
	int readNum;

	if ((fptr=fopen(filein, "rb")) == NULL) {
		printf("Cannot open file to read\n");
		return;
	}

	data2 = malloc(0);

	while(!feof(fptr)) {
		data2 = realloc(data2, (n2+1) * sizeof(phoneaddress_t));
		if (data2 == NULL) {
			printf("Failed to allocate memory!\n");
		}
		readNum = fread(&data2[n2], sizeof(phoneaddress_t), 1, fptr);
		if (readNum > 0) n2++;
	}

	for (i = 0; i < n2; i++) {
		printf("*** %d ***\n", i+1);
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
	if (argc != 2) {
		printf("Sai cu phap. Nhap : fileread <file>\n");
		return 1;
	}

	const char* filein = argv[1];

	phoneread(filein);
	printf("Done!\n");
  
  return 0;
}
