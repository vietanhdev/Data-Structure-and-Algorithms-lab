#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct phoneaddress {
	char name[45];
	char tel[30];
} phoneaddress_t;

void merge(FILE *fout, FILE *fin) {
	int readNum;
	int i;
	phoneaddress_t *data;
	data = malloc(10 * sizeof(phoneaddress_t));
	if (data == NULL) {
		printf("Failed to allocate memory!\n");
		return;
	}
	while(!feof(fin)) {
		readNum = fread(data, sizeof(phoneaddress_t), 10, fin);
		fwrite(data, sizeof(phoneaddress_t), readNum, fout);
	}
}


int main(int argc, char**argv) {
	if (argc != 4) {
		printf("Sai cu phap. Nhap : filemerge <file1> <file2> <file-ghep>\n");
		return 1;
	}
	char *fileout = argv[3];
	char *filename1 = argv[1];
	char *filename2 = argv[2];

	FILE *fout, *fin1, *fin2;

	if ((fin1=fopen(filename1, "rb")) == NULL) {
		printf("Cannot open file to read : %s\n", filename1);
		return 1;
	}
	if ((fin2=fopen(filename2, "rb")) == NULL) {
		printf("Cannot open file to read : %s\n", filename2);
		return 1;
	}
	if ((fout=fopen(fileout, "wb")) == NULL) {
		printf("Cannot open file to read : %s\n", fileout);
		return 1;
	}

	merge(fout, fin1);
	merge(fout, fin2);

	fclose(fout);
	fclose(fin1);
	fclose(fin2);
	printf("Done!\n");

  return 0;
}
