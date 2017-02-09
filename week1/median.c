#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int n;
	int a[10000];


	printf("n = "); scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		printf("%d : ", i+1); scanf("%d", &a[i]);
	}


	float average = 0;
	for (int i = 0; i < n; i++) {
		average += a[i];
	}

	printf("%f\n", average);
	average /= n;
	printf("%f\n", average);


	int median = a[0];
	

	for (int i = 1; i < n; i++) {
		if (fabs(average-median) > fabs(a[i]-average)) {
			median = a[i];
		}
	}

	printf("Median : %d\n", median);
	
    return 0;
}
