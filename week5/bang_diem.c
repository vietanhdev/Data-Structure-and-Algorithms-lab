#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_CHAR_PER_LINE 256
#define MAX_CHAR_PER_WORD 256
#define MAX_LINE 80
#define MAX_CHAR_PER_STR 256
#define MAX_STUDENT 200

typedef struct students {
	char stdCode[MAX_CHAR_PER_STR];
	char name[MAX_CHAR_PER_STR];
	char phoneNumber[MAX_CHAR_PER_STR];
	float grade;
} student_t;

int getNextWord(char *word, char *s, int *pos) { // return 1: one more word can be get; 0: there is no word left.
	int begin, end;
	int scanPos = *pos;
	while (scanPos < strlen(s))
		if(!isspace(s[scanPos]))
			break;
		else
			scanPos++;
	if (scanPos < strlen(s))
		begin = scanPos;
	else
		return 0;
	while (scanPos < strlen(s) && !isspace(s[scanPos])) scanPos++;
	end = scanPos-1;
	for (int i = begin; i <= end; ++i) {
		word[i-begin] = s[i];
	}
	word[end-begin+1] = '\0';
	*pos = end+1;
	return 1;
}

int containNumber(char *s) {
	for (int i = 0; i < strlen(s); ++i) {
		if (s[i] >= '0' && s[i] <= '9')
			return 1;
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	int i;


	if (argc != 2) {
		printf("Syntax error!! Please type : Bang_diem <filename>\n");
		return 1;
	}

	FILE *fptr1;
	const char *filename1 = argv[1];
	if((fptr1=fopen(filename1, "r+")) == NULL) {
		printf("Cannot open file %s to read\n", filename1);
		return 1;
	}

	student_t *sv;
	sv = malloc(0);

	char s[MAX_CHAR_PER_LINE];
	char word[MAX_CHAR_PER_WORD];
	int pos;
	fgets(s, MAX_CHAR_PER_LINE, fptr1); // Ignore the first line
	int stdNum = 0;
	int oldlen, newlen;
	while (fgets(s, MAX_CHAR_PER_LINE, fptr1) != NULL) {
		sv = realloc(sv, (stdNum+1) * sizeof(student_t));
		pos = 0;
		getNextWord(word, s, &pos); // scan no.
		getNextWord(word, s, &pos); // scan studentCode
		strcpy(sv[stdNum].stdCode, word);
		while(getNextWord(word, s, &pos)) {
			if (!containNumber(word)) {
				if (strlen(sv[stdNum].name) != 0) {
					sv[stdNum].name[strlen(sv[stdNum].name)+1] = '\0';
					sv[stdNum].name[strlen(sv[stdNum].name)] = ' ';
				}
				oldlen = strlen(sv[stdNum].name);
				newlen = strlen(sv[stdNum].name) + strlen(word);
				for (int i = 0; i < strlen(word); ++i) {
				 	sv[stdNum].name[oldlen+i] = word[i];
				} 
				sv[stdNum].name[newlen] = '\0';
				//printf("%s\n", sv[stdNum].name);
			} else {
				strcpy(sv[stdNum].phoneNumber, word); // Scan phone number
				//printf("%s\n", sv[stdNum].phoneNumber);
			}
		}
		getNextWord(word, s, &pos); // scan grade
		sv[stdNum].grade = atof(word); // scan grade
		stdNum++;
	}

	fclose(fptr1); // Finish reading data

	// Print data to screen
	printf("STT MSSV.         Ho ten                            Dien thoai.                  Diem\n");
	for (i = 0; i < stdNum; ++i) {
		//printf("%2d  %.30s  %.30s  %.30s  %.1f\n", i+1, sv[i].stdCode, sv[i].name, sv[i].phoneNumber, sv[i].grade);
		printf("%2d  %-12.12s  %-30.30s  %-30.30s  %-.1f\n", i+1, sv[i].stdCode, sv[i].name, sv[i].phoneNumber, sv[i].grade);
	}

	// Open binary file to write
	FILE *fptr2;
	if((fptr2=fopen("grade.dat", "wb")) == NULL) {
		printf("Cannot open file %s to read\n", "grade.dat");
		return 1;
	}

	for (i = 0; i < stdNum; ++i) {
		fwrite(&sv[i], sizeof(student_t), 1, fptr2);
	}

	fclose(fptr2);


	// ReOpen file
	student_t *sv2;
	sv2 = malloc(0);
	int stdNum2 = 0;
	int readNum;

	if((fptr2=fopen("grade.dat", "rb")) == NULL) {
		printf("Cannot open file %s to read\n", "grade.dat");
		return 1;
	}

	while(!feof(fptr2)) {
		sv2 = realloc(sv2, (stdNum2+1) * sizeof(student_t));
		readNum = fread(&sv2[stdNum2], sizeof(student_t), 1, fptr2);
		if (readNum > 0) stdNum2++; // Increase number of elemnts if can read one element
	}

	fclose(fptr2);

	printf("-------------------------------------------------\n");

	// Print data to screen
	printf("STT MSSV.         Ho ten                            Dien thoai.                  Diem\n");
	for (i = 0; i < stdNum2; ++i) {
		//printf("%2d  %.30s  %.30s  %.30s  %.1f\n", i+1, sv[i].stdCode, sv[i].name, sv[i].phoneNumber, sv[i].grade);
		printf("%2d  %-12.12s  %-30.30s  %-30.30s  %-.1f\n", i+1, sv2[i].stdCode, sv2[i].name, sv2[i].phoneNumber, sv2[i].grade);
	}
	
	return 0;
}
