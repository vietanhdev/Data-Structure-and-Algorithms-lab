// Solve ax^2 + bx + c = 0
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    if (argc != 4) {
		printf("Syntax error. Please type : sde <a> <b> <c>\n");
	}
	float a = atof(argv[1]); printf("a = %f\n", a);
	float b = atof(argv[2]); printf("b = %f\n", b);
	float c = atof(argv[3]); printf("c = %f\n", c);

	float delta = b*b - 4*a*c;
	if (delta == 0) {
		printf("The equation has only solution: x = %f\n", -b/2/a);
	} else if (delta > 0) {
		printf("The equation has two solutions:\n");
		printf("x1 = %f\n", (-b-sqrt(delta))/2/a);
		printf("x2 = %f\n", (-b+sqrt(delta))/2/a);
	} else {
		printf("The equation has no solution.\n");
	}
    return 0;
}
