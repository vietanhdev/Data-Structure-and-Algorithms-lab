#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_CHAR_PER_LINE 2000
#define MAX_CHAR_PER_WORD 10
#define MAX_LINE 80

int getNextWord(char *s, int scanPos, int *begin, int *end) { // return 1: one more word can be get; 0: there is no word left.
	while (scanPos < strlen(s))
		if(!isspace(s[scanPos]))
			break;
		else
			scanPos++;
	if (scanPos < strlen(s))
		*begin = scanPos;
	else
		return 0;
	while (scanPos < strlen(s) && !isspace(s[scanPos])) scanPos++;
	*end = scanPos-1;
	return 1;
}

int isInWordList(char *s, int begin, int end, int wordNum, char *wordList[]) {
	int inWordList;
	for (int i = 0; i < wordNum; ++i)
	{
		inWordList = 1;
		if (strlen(wordList[i]) != end - begin + 1) {
			continue;
		}
		for (int j = 0; j < strlen(wordList[i]); ++j)
		{
			if (toupper(s[begin+j]) != toupper(wordList[i][j])){
				inWordList = 0;
				break;
			}
		}
		if (inWordList) return 1;
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	if (argc != 3) {
		printf("Syntax error!! Please type : filter <filename> <replacing char>\n");
		return 1;
	}

	FILE *fptr1;
	const char *filename1 = argv[1];
	const char replaceChar = argv[2][0];
	if((fptr1=fopen(filename1, "r+")) == NULL) {
		printf("Cannot open file %s to read\n", filename1);
		return 1;
	}

	int wordNum = 3;
	char *wordList[MAX_CHAR_PER_LINE] = {
		"hello",
		"fuck",
		"hi"
	};
	printf("%c\n", wordList[0][1]);

	char s[MAX_CHAR_PER_LINE];
	int begin, end;
	while (fgets(s, MAX_CHAR_PER_LINE, fptr1) != NULL) {
		begin = 0;
		while (getNextWord(s, begin, &begin, &end)) {
			if (isInWordList(s, begin, end, wordNum, wordList)) {
				for (int i = begin; i <= end; ++i) {
					s[i] = replaceChar;
				}
			}
			begin = end + 1;
		}
		printf("%s", s);
	}

	fclose(fptr1);
	return 0;
}