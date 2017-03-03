#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR_PER_LINE 2000
#define MAX_LINE 80

int main(int argc, char const **argv)
{
	if (argc != 2)
		printf("Syntax error!! Please type : Dong_Cuoi_Cung <filename>\n");

	FILE *fptr1;
	char *filename1 = argv[1];
	if((fptr1=fopen(filename1, "r+")) == NULL) {
		printf("Cannot open file %s to read\n", filename1);
		return 1;
	}

	char s[MAX_CHAR_PER_LINE];
	int linum=0; // number of lines
	char finalLine[MAX_CHAR_PER_LINE];
	while (fgets(s, MAX_CHAR_PER_LINE, fptr1) != NULL) {
		finalLine[linum]=s[0];
		linum++;
	}
	finalLine[linum]='\0';
	fputs(finalLine, fptr1);

	fclose(fptr1);
	return 0;
}