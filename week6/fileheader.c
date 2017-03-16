#include <stdio.h>
#include <stdlib.h>

typedef struct header_s {
	int filesize;
	char author[30];
	int d, m, y; // Ngay tao header
} header_t;

int main(int argc, char const *argv[])
{
	header_t header;


	char filename[256];
	int select;
	while (select != 3) {
		printf(" *** FILE HEADER ***\n");
		printf("1: Write header\n");
	}






	FILE *fout;
	if ( (fout = fopen("out.txt", "w")) == NULL ) {
		printf("Cannot open out.txt\n");
	}

	for (i = n-1; i >= 0; --i) {
		fprintf(fout, "%d ", a[i]);
	}

	fprintf(fout, "%d ", sum);

	fclose(fout);
	return 0;
}