#include <stdio.h>

enum {SUCCESS, FAIL};

int main() {
  FILE *fptr;
  char filename[] = "haiku.txt";
  int reval = SUCCESS;
  if ((fptr = fopen(filename, "r")) == NULL) {
    printf("Cannot open file\n");
    reval = FAIL;
  } else {
    printf("The value of pointer: %p\n", fptr);
    fclose(fptr);
  }
  return reval;
}

