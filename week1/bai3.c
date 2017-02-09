#include <stdio.h>
#include <string.h>
#include <ctype.h>


// Dem so lan xuat hien cua moi chu cai trong xau

int main(int argc, char *argv[])
{
    char s[100];

	printf("Nhap xau: "); fgets(s, 100, stdin);
	s[strlen(s)-1] = '\0';

	int len = strlen(s);
	int count[26] = {0};
	for (int i = 0; i < len; i++) {
		count[tolower(s[i])-'a']++;
	}

	printf("So lan xuat hien:\n");
	for (int i = 0; i <= 25; i++) {
		if (count[i])
			printf("%c : %d\n", i+'a', count[i]);
	}
	
    return 0;
}
