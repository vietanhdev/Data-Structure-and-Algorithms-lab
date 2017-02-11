#include <stdio.h>

int main() {
  FILE *fptr1;
  FILE *fptr2;
  char infile[] = "lab1.txt";
  char outfile[] = "lab1w.txt";

  if ((fptr1 = fopen(infile, "r")) == NULL  || (fptr2 = fopen(outfile, "w+")) == NULL) {
    printf("Cannot open file\n");
    return 0;
  }

  
  char c;
  while ((c = fgetc(fptr1)) != EOF) {
    fputc(c, fptr2);
  }

  fclose(fptr1);
  fclose(fptr2);
  
  return 0;
}
