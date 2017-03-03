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
	if (argc != 2) {
		printf("Syntax error!! Please type : Sinh_vien <filename>\n");
		return 1;
	}

	FILE *fptr1;
	const char *filename1 = argv[1];
	if((fptr1=fopen(filename1, "r+")) == NULL) {
		printf("Cannot open file %s to read\n", filename1);
		return 1;
	}

	student_t sv[MAX_STUDENT];
	char s[MAX_CHAR_PER_LINE];
	char word[MAX_CHAR_PER_WORD];
	int pos;
	fgets(s, MAX_CHAR_PER_LINE, fptr1); // Ignore the first line
	int stdNum = 0;
	int oldlen, newlen;
	while (fgets(s, MAX_CHAR_PER_LINE, fptr1) != NULL) {
		pos = 0;
		getNextWord(word, s, &pos); // scan no.
		//printf("%s\n", word);
		getNextWord(word, s, &pos); // scan studentCode
		strcpy(sv[stdNum].stdCode, word);
		//printf("%s\n", sv[stdNum].stdCode);
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
				strcpy(sv[stdNum].phoneNumber, word);
				//printf("%s\n", sv[stdNum].phoneNumber);
			}
		}
		stdNum++;
	}

	fclose(fptr1);

	for (int i = 0; i < stdNum; ++i)
	{
		printf("Nhap diem sinh vien %s - %s : ", sv[i].name, sv[i].stdCode);
		scanf("%f", &sv[i].grade);
	}

	FILE *fptr2;
	 if((fptr2=fopen("Bang_diem.txt", "w")) == NULL) {
	 	printf("Cannot open file %s to write\n", "Bang_diem.txt");
	 	return 1;
	 }

	fprintf(fptr2, "STT.   MSSV.     Ho ten                Dien thoai.               Diem\n");
	for (int i = 0; i < stdNum; ++i)
	{
		//printf("%2d  %.30s  %.30s  %.30s  %.1f\n", i+1, sv[i].stdCode, sv[i].name, sv[i].phoneNumber, sv[i].grade);
		fprintf(fptr2, "%2d  %-12.12s  %-30.30s  %-30.30s  %-.1f\n", i+1, sv[i].stdCode, sv[i].name, sv[i].phoneNumber, sv[i].grade);
	}

	fclose(fptr2);
	
	return 0;
}