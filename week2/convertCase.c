#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
  if (argc != 3) {
    printf("Syntax error. type convertCase <source> <dest>\n");
    return 1;
  }

  FILE *fptr1;
  FILE *fptr2;
  char *filename1 = argv[1];
  char *filename2 = argv[2];

  // Open file
  if ((fptr1 = fopen(filename1, "r")) == NULL || (fptr2 = fopen(filename2, "w")) == NULL) {
    printf("Error on openning file!\n");
    return 1;
  }

  char c;
  while ((c=fgetc(fptr1)) != EOF) {
    if (c >= 'A' && c <= 'Z')
      c = tolower(c);
    else if (c >= 'a' && c <= 'z')
      c = toupper(c);
    fputc(c, fptr2);
  }

  fclose(fptr1);
  fclose(fptr2);
  
  return 0;
}
