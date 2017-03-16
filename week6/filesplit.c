#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct phoneaddress {
	char name[45];
	char tel[30];
} phoneaddress_t;

int n;

void split(char *filein, char *filename1, char *filename2) {
	int readNum;
	FILE *fptr;
	FILE *fin;
	int i;

	if ((fin=fopen(filein, "rb")) == NULL) {
		printf("Cannot open file to read\n");
		return;
	}

	phoneaddress_t *data;
	data = malloc(n * sizeof(phoneaddress_t));
	if (data == NULL) {
		printf("Failed to allocate memory!\n");
	}

	// Write file 1
	if ((fptr=fopen(filename1, "wb")) == NULL) {
		printf("Cannot open file to write\n");
		return;
	}
	readNum = fread(data, sizeof(phoneaddress_t), n, fin);
	fwrite(data, sizeof(phoneaddress_t), readNum, fptr);
	fclose(fptr);

	// Write file 2
	if ((fptr=fopen(filename2, "wb")) == NULL) {
		printf("Cannot open file to write\n");
		return;
	}
	readNum = fread(data, sizeof(phoneaddress_t), n, fin);
	fwrite(data, sizeof(phoneaddress_t), readNum, fptr);
	fclose(fptr);

   	fclose(fin);
   	free(data);
}


int main(int argc, char**argv) {
	if (argc != 4) {
		printf("Sai cu phap. Nhap : filesplit <so ll cat moi file> <file1> <file2>\n");
		return 1;
	}

	n = atoi(argv[1]);
	char filein[] = "phone.dat";
	char *filename1 = argv[2];
	char *filename2 = argv[3];

	split(filein, filename1, filename2);
	printf("Done!\n");

  return 0;
}
