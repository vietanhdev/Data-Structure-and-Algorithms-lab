#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR_PER_LINE 80
#define MAX_LINE 2000

int main(int argc, char const **argv)
{
	if (argc != 2)
		printf("Syntax error!! Please type : length_of_line <filename>\n");

	FILE *fptr1;
	char *filename1 = argv[1];
	if((fptr1=fopen(filename1, "r")) == NULL) {
		printf("Cannot open file %s to read\n", filename1);
		return 1;
	}

	char s[MAX_CHAR_PER_LINE][MAX_LINE]; int strnum = 0;
	while (fgets(s[strnum], MAX_CHAR_PER_LINE, fptr1) != NULL) {
		strnum++;
	}

	fclose(fptr1);
	if((fptr1=fopen(filename1, "w")) == NULL) {
		printf("Cannot open file %s to write\n", filename1);
		return 1;
	}

	int i;
	for (i = 0; i < strnum; ++i) {
		fprintf(fptr1, "%d %s", strlen(s[i])-1, s[i]);
	}

	fclose(fptr1);
	return 0;
}