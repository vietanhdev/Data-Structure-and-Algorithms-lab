#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// e^x =1+x/1! +x^2/2! +....+ x^n/n!
int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3) {
		printf("Incorrect syntax. Please type emx <so_mu> <do_chinh_xac> or emx <so_mu>.\n");
		return 1;
	}

	double epsilon = 0.00000000001;
	if (argc == 3)
		epsilon = atof(argv[2]);

	double x = atof(argv[1]);
	double denomerator = 1;
	double numerator = x;
	double i = 1;
	double old_result = 1;
	double result = 1 + x;
   
	while (fabs(result-old_result) > epsilon) {
		i++;
		numerator *= x;
		denomerator *= i;
		old_result = result;
		result += numerator / denomerator;
	}

	printf("Result: e^%lf = %lf\n", x, result);
	
    return 0;
}
