#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int i, n;
	char *ps;
	char c;

	char s1[256], s2[256];

	printf("Nhap xau 1: ");
	scanf ("%[^\n]%*c", s1);
	printf("Xau 1: %s\n", s1);
	printf("Nhap xau 2: ");
    scanf ("%[^\n]%*c", s2);
	printf("Xau 2: %s\n", s2);

	ps = malloc((strlen(s1) + strlen(s2)) * sizeof(char));

	strcpy(ps, s1);
	strcpy(ps + strlen(s1), s2);

	printf("%s\n", ps);
	
	free(ps);
	return 0;
}
