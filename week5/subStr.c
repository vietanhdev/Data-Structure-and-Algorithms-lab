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
	char s[30];
	int offset, number;
	printf("Nhap xau:\n");
	fgets(s, 100, stdin);
	printf("Nhap offset va number:\n");
	scanf("%d %d", &offset, &number);
	printf("Xau me la: %s\n", s);
	printf("Xau kq: %s\n", subStr(s, offset, number));
	return 0;
}
