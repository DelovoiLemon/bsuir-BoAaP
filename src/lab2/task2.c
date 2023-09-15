#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define DIVBYZEROMSG "Error! Zero division!\n"
#define NONUMMSG "Error! No number entered!\n"
#define PI 	3.1415926
#define MATH_E	2.7182818

enum {mode1 = 1, mode2 = 2, mode3 = 3};


double my_abs(double num) {
    return (num > 0) ? num : -num;
}

double etha(double x, int mode) {
	switch(mode) {
		case mode1:
			return 2*x;
		case mode2:
			return x*x;
		case mode3:
			return x/3;
		default:
			printf("Error! Incorrect mode!");
			exit(1);
	}
}

double y(double a, double b, double z, int mode) {
	double x;
	if(z > 0) {
		printf("z > 0. Solving with x = 1/(z^2 + 2*z)\n");
		x = (1.0/(z*z + 2*z));
	} else {
		printf("z <= 0. Solving with x = 1 - z^3\n");
		x = 1 - z*z*z;
	}
	if(log(my_abs(x)) + etha(x, mode) == 0) {
		printf(DIVBYZEROMSG);
		exit(1);
	}
	return (2.5*a*pow(MATH_E, -3*x) - 4*b*x*x) / (log(my_abs(x))+etha(x, mode));
}


int main() {
	double a, b, z;
	int mode;

	printf("Etha function mode:\n 1: 2*x\n 2: x^2\n 3: x/3\nEnter a, b, z, mode: ");

	if(scanf("%lf %lf %lf %i", &a, &b, &z, &mode) < 2) {
		printf(NONUMMSG);
		exit(1);
	}

	printf("Result: y = %f\n", y(a, b, z, mode));

	return 0;
}
