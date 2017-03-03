#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR_PER_LINE 80

int main(int argc, char const **argv)
{
	if (argc != 3)
		printf("Syntax error!! Please type : compareText <file1> <file2>\n");

	FILE *fptr1;
	FILE *fptr2;
	char *filename1 = argv[1];
	char *filename2 = argv[2];
	if((fptr1=fopen(filename1, "r")) == NULL) {
		printf("Cannot open file %s\n", filename1);
		return 1;
	}

	if((fptr2=fopen(filename2, "r")) == NULL) {
		printf("Cannot open file %s\n", filename2);
		return 1;
	}

	FILE *fptr3;
	char filename3[] = "result.txt";
	if((fptr3=fopen(filename3, "w")) == NULL) {
		printf("Cannot open file %s\n", filename3);
		return 1;
	}

	fprintf(fptr3, "Different lines:\n");
	int firstLine = -1;
	int lineNum = 1;
	char s1[MAX_CHAR_PER_LINE];
	char s2[MAX_CHAR_PER_LINE];
	while (1) {	
		if (fgets(s1, MAX_CHAR_PER_LINE, fptr1) == NULL) {
			while (fgets(s2, MAX_CHAR_PER_LINE, fptr2) != NULL) {
				if (firstLine == -1) firstLine = lineNum;
				fprintf(fptr3, "%d\n", lineNum++);
			}
			break;
		};
		if (fgets(s2, MAX_CHAR_PER_LINE, fptr2) == NULL) {
			while (fgets(s1, MAX_CHAR_PER_LINE, fptr1) != NULL) {
				if (firstLine == -1) firstLine = lineNum;
				fprintf(fptr3, "%d\n", lineNum++);
			}
			break;
		};
		if (strcmp(s1,s2) != 0) {
			if (firstLine == -1) firstLine = lineNum;
			fprintf(fptr3, "%d\n", lineNum);
		}
		lineNum++;
	}
	if (firstLine != -1) fprintf(fptr3, "First diff. line: %d\n", firstLine);

	fclose(fptr1);
	fclose(fptr2);
	fclose(fptr3);
	return 0;
}