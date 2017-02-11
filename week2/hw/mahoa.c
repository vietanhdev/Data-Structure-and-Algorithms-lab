#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int displace(int begin, int end, int pos, int displacement) {
	int newpos = pos + displacement;
	int length = end - begin + 1;
	if (newpos < begin)
		return newpos + (end - newpos) / length * length;
	if (newpos > end)
		return newpos - (newpos-begin) / length * length;
	return newpos;
}

void encrypt(FILE *fptr, int displacement) {
	char c;
	while ((c = fgetc(fptr)) != EOF) {
		if (c >= 'A' && c <='Z') {
			c = displace('A', 'Z', c, displacement);
			fseek(fptr, -1, SEEK_CUR);
			fputc(c, fptr);
		} else if (c >= 'a' && c <='z') {
			c = displace('a', 'z', c, displacement);
			fseek(fptr, -1, SEEK_CUR);
			fputc(c, fptr);
		}
	}
}


int main(int argc, char *argv[])
{

	if (argc != 4 && (strcmp(argv[1], "mahoa") == 0 || strcmp(argv[1], "giaima") == 0)) {
    printf("Sai cu phap!!\n");
    return 1;
  }

  printf("Ma hoa file vb chi gom chu cai. Cu phap: mahoavb mahoa <tenfile> <dolech> HOAC mahoavb giaima <tenfile> <dolech>\n");

  FILE *fptr;
  char *filename = argv[2];
  char displacement = atoi(argv[3]);

  // Open file
  if ((fptr = fopen(filename, "r+")) == NULL) {
    printf("Cannot open file!\n");
    return 1;
  }
  
  if (strcmp(argv[1], "mahoa") == 0) {
    encrypt(fptr, displacement);
  } else {
    encrypt(fptr, -displacement);
  }

  // Close file
  fclose(fptr);
  
  printf("Done!\n");

  return 0;
}
