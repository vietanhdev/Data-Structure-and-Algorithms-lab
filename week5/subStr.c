#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * subStr(char *s1, int offset, int number) {
	int i;
	if (strlen(s1) <= offset + number)
		number = strlen(s1) - offset;
	char *s2;
	s2 = malloc(number * sizeof(char));
	if (s2 == NULL)
		return NULL;
	for (i = 0; i < number; ++i) {
		s2[i] = s1[offset+i];
	}
	s2[number] = '\0';
	return s2;
}

int main(int argc, char const *argv[])
{
	char s[100] = "Xin chao cac ban nhe";
	printf("%s\n", subStr(s, 0, 1));
	printf("%s\n", subStr(s, 4, 4));
	printf("%s\n", subStr(s, 4, 100));
	return 0;
}