#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_CHAR_PER_LINE 2000

char file1[256];
char file2[256];


void copyByChar() {
	FILE *fptr1;
	FILE *fptr2;
	if ((fptr1=fopen(file1, "r")) == NULL) {
		printf("Cannot open file to read\n");
		return;
	}
	if ((fptr2=fopen(file2, "w")) == NULL) {
		printf("Cannot open file to write\n");
		return;
	}
	int ch;
	while((ch = fgetc(fptr1)) != EOF) {
		fputc(ch, fptr2);
	} 
	fclose(fptr1);
	fclose(fptr2);
}

void copyByLine() {
	FILE *fptr1;
	FILE *fptr2;
	if ((fptr1=fopen(file1, "r")) == NULL) {
		printf("Cannot open file to read\n");
		return;
	}
	if ((fptr2=fopen(file2, "w")) == NULL) {
		printf("Cannot open file to write\n");
		return;
	}
	char *s;
	s = malloc(MAX_CHAR_PER_LINE * sizeof(char));
	if (s == NULL) {
		printf("Cannot alocate memory!\n");
		return;
	}
	while(fgets(s, MAX_CHAR_PER_LINE, fptr1) != NULL) {
		fputs(s, fptr2);
	} 
	fclose(fptr1);
	fclose(fptr2);
}

void copyByBlock() {
	FILE *fptr1;
	FILE *fptr2;
	if ((fptr1=fopen(file1, "rb")) == NULL) {
		printf("Cannot open file to read\n");
		return;
	}
	if ((fptr2=fopen(file2, "wb")) == NULL) {
		printf("Cannot open file to write\n");
		return;
	}

	void *mem;
	int blockSize;
	int readNum;
	printf("Enter size of block: \n"); scanf("%d", &blockSize);
	mem = malloc(blockSize);
	if (mem == NULL) {
		printf("Cannot allocate memory!\n");
		return;
	}
	while(!feof(fptr1)) {
		readNum = fread(mem, 1, blockSize, fptr1);
		fwrite(mem, 1, readNum, fptr2);
	} 
	fclose(fptr1);
	fclose(fptr2);
}


clock_t beginTimer, endTimer;
void beginTime() {
	beginTimer = clock();
}
void endTime() {
	endTimer = clock();
	double time_spent = (double)(endTimer - beginTimer) / CLOCKS_PER_SEC;
	printf("Exe. Time: %lf\n", time_spent);
}

int main(int argc, char**argv) {
	if (argc > 1) {
		strcpy(file1, argv[1]);
		strcpy(file2, argv[2]);
	} else { // Use default
		strcpy(file1, "file1.txt");
		strcpy(file2, "file2.txt");
	}

	int select;
	
	while(1) {
		printf("*** COPY _ MULTIMODE ***\n");
		printf("1: By character\n2: By line\n3: By block\n4: Exit\nSelection: "); scanf("%d", &select);
		switch(select) {
			case 1: beginTime(); copyByChar(); endTime(); break;
			case 2: beginTime(); copyByLine(); endTime(); break;
			case 3: beginTime(); copyByBlock(); endTime(); break;
			case 4: return 0;
		}
	}
  
  return 0;
}
