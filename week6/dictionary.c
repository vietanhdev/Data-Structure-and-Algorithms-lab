#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_PER_STR 200

typedef struct dict_struct {
	char word[MAX_CHAR_PER_STR];
	char meanning[MAX_CHAR_PER_STR];
} dict_t;


dict_t *dict;
int n; //Number of words

void readDataFromTxt(){
	FILE *fptr;
	int i;
	char line[MAX_CHAR_PER_STR];

	if ((fptr=fopen("vnedict.txt", "r")) == NULL) {
		printf("Cannot open file to read\n");
		return;
	}

	dict = malloc(0);
	int lenPtr;
	n = 0;
	while (fgets(line, MAX_CHAR_PER_STR, fptr) != NULL) {
		dict = realloc(dict, (n+1) * sizeof(dict_t));
		if (dict == NULL) {
			printf("Cannot allocate memory\n");
			return;
		}
		lenPtr = 0;
		while (lenPtr < strlen(line) && line[lenPtr] != ':') {
		 	dict[n].word[lenPtr] = line[lenPtr];
		 	lenPtr++;
	    }
	    if (lenPtr >= strlen(line)) // Fix buffer overflow
	    	continue;
		dict[n].word[lenPtr-1] = '\0';
		lenPtr++; lenPtr++;
		for (i = 0; i < strlen(line)-lenPtr-1; ++i) {
			dict[n].meanning[i] = line[lenPtr+i];
		}
		dict[n].meanning[strlen(line)-lenPtr] = '\0';
		n++;
	}
	for (i = 0; i < n; ++i) {
		printf("%s : %s\n", dict[i].word, dict[i].meanning);
	}
   	fclose(fptr);
}

void writeData2Binary() {
	FILE *fptr;

	if ((fptr=fopen("vnedict.dat", "wb")) == NULL) {
		printf("Cannot open file to read\n");
		return;
	}
	fwrite(dict, sizeof(dict_t), n, fptr);	
   	fclose(fptr);
}

void readDataFromBinary() {
	FILE *fptr;
	int i;
	
	if ((fptr=fopen("vnedict.dat", "rb")) == NULL) {
		printf("Cannot open file to read\n");
		return;
	}

	int readNum;
	free(dict);
	n = 0;
	dict = malloc(0);
	while (!feof(fptr)) {
		dict = realloc(dict, (n+1) * sizeof(dict_t));
		if (dict == NULL) {
			printf("Cannot allocate memory\n");
			return;
		}
		readNum = fread(&dict[n], sizeof(dict_t), 1, fptr);
		if (readNum > 0) {
			n++;
		}
	}

	for (i = 0; i < n; ++i) {
		printf("%s : %s\n", dict[i].word, dict[i].meanning);
	}

   	fclose(fptr);
}

int main(int argc, char**argv) {
	int select;
	while(1) {
		printf("1: Read data from text file\n2: Write data to binary file\n3: Read data from binary file\n4: Exit\nSelection: "); scanf("%d", &select);
		switch(select) {
			case 1: readDataFromTxt(); break;
			case 2: writeData2Binary(); break;
			case 3: readDataFromBinary(); break;
			case 4: return 0;
		}
	}
  
  return 0;
}
