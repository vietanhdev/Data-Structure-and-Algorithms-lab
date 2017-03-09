#include <stdio.h>
#include <stdlib.h>

int main(){


  int i, n, *p;

  printf("How many numbers u want to enter? ");
  scanf("%d", &n);

  p = (int *)malloc(n * sizeof(int));

  if (p == NULL) {
    printf("Cannot allocate the memory");
    return 1;
  }

  for (i = 0; i < n; i++) {
	  printf("Nhap so thu %d: ", i+1); scanf("%d", &p[i]);
  }

  for (i = 0; i < n; i++) {
	  printf(" ::: %d  >>>>  %d\n", i+1, p[i]);
  }
  int c;
  int more;
  printf("Co nhap tiep khong? (1: co; 0: khong)\n");
  scanf("%d", &c);

  if (c == 1) {
	 printf("How many numbers u want to enter? ");
	 scanf("%d", &more);
	 p = realloc(p, n+more);

	  if (p == NULL) {
		  printf("Cannot allocate the memory");
		  return 1;
	  }
	  n = n+more;
	  for (i = n-more; i < n; i++) {
		  printf("Nhap so thu %d: ", i); scanf("%d", &p[i]);
	  }

	  for (i = 0; i < n; i++) {
		  printf(" ::: %d  >>>>  %d\n", i+1, p[i]);
	  }
  }

  free(p);

  return 0;
}
