#include <stdio.h>
#include <string.h>

void showContentByPage(FILE *fptr, int pageLineNum) {
  char c;
  int currLine = 0;
  while ((c = fgetc(fptr)) != EOF) {
    putchar(c);
    if (c == '\n') {
      currLine++;
      if (currLine == pageLineNum) {
	currLine = 0;
	getchar();
      }
    }
  }
}

void showAllContent(FILE *fptr) {
  char c;
  while ((c = fgetc(fptr)) != EOF) {
    putchar(c);
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2 || argc > 3) {
    printf("Syntax error. type cat <filename> or cat <filename> -p\n");
    return 1;
  }

  FILE *fptr;
  char *filename = argv[1];

  // Open file
  if ((fptr = fopen(filename, "r")) == NULL) {
    printf("Cannot open file!\n");
    return 1;
  }

  if (argc == 3 && strcmp(argv[2], "-p") == 0) {
    showContentByPage(fptr, 25);
  } else {
    showAllContent(fptr);
  }
  
  return 0;
}
