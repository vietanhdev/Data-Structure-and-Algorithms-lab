#include <stdio.h>


int main(int argc, char *argv[])
{
	int n;
	int a[10000];


	printf("n = "); scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		printf("a[%d] : ", i+1); scanf("%d", &a[i]);
	}

	int num_of_zero = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] == 0)
			num_of_zero++;
	}
	printf("Number of 0 : %d\n", num_of_zero);

    int max_len_0=0;
	int step = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] == 0) {
			step++;
		} else if (max_len_0 < step){
			max_len_0 = step;
			step = 0;
		}
	}
	if (max_len_0 < step){
		max_len_0 = step;
	}
	printf("Max length : %d\n", max_len_0);
	

	// c
	int tmp;
	for (int i = 0; i < n-1; i++) {
		for (int j = n-2; j >= i; j--) {
			if (a[j] > a[j+1]) {
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}
	}

	for ( int i = 0; i < n; i++) {
		printf("%d; ", a[i]);
	}

	if (n>0) {
		printf("So lan xuat hien: \n");
		int count = 1;
		for (int i = 1; i < n; i++) {
			if (a[i] == a[i-1])
				count++;
			else {
				printf("%d : %d\n", a[i-1], count);
				count=1;
			}
		}
		if (count) {
			printf("%d : %d\n", a[n-1], count);
		}
	}

	
    return 0;
}
