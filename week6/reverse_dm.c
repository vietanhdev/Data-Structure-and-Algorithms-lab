#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int n;
	int *a;
	int sum = 0;

	scanf("%d", &n);
	int i;

	a = malloc(n * sizeof(int));

	for (i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
		sum += a[i];
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