#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



int main(int argc, char *argv[])
{

  if (argc != 2) {
    printf("Syntax error!! Please enter: thongkechucai <filename>\n");
    return 1;
  }

  // Process input file
  FILE *fptr;
  char *filename = argv[1];

  // Open file
  if ((fptr = fopen(filename, "r")) == NULL) {
	  printf("Cannot open file \"%s\"\n", filename);
	  return 1;
  }

  int stats[256] = {0};
  char c;
  while ((c=fgetc(fptr)) != EOF) {
	  stats[toupper(c)]++;
  }
  
  fclose(fptr);

  // Process output file
   // Open file
  char fout[] = "sourcestats.txt";
  if ((fptr = fopen(fout, "w")) == NULL) {
	  printf("Cannot create file \"%s\"", fout);
	  return 1;
  }

  for (int i = 0; i < 256; i++) {
	  if (!isspace(i) && stats[i] > 0)
		  fprintf(fptr, "%c : %d\n", i, stats[i]);
  }
  
  fclose(fptr);
  
  printf("Done!\n");

  return 0;
}
