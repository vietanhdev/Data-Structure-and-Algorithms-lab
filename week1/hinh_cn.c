#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
		printf("Input error!!\n");
		printf("hinh_cn <height> <width>\n");
	} else {
		float h = atof(argv[1]);
		float w = atof(argv[2]);
		printf("C = %f\n", 2*(h+w));
		printf("S = %f\n", h*w);
	}
    return 0;
}
