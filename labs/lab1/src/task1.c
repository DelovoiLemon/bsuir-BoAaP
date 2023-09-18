#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define DIVBYZEROMSG "Error! Zero division!\n"
#define NONUMMSG "Error! No number entered!\n"

double z1(double a) {
	if(1+cos(4*a) == 0 || 1+cos(2*a) == 0 ) {
		printf(DIVBYZEROMSG);
		exit(1);
	}
	return (sin(4*a)/(1+cos(4*a)))*(cos(2*a)/(1+cos(2*a)));
}

double z2(double a) {
	a = 1.5*M_PI - a;
	if(cos(a) == 0) {
		printf(DIVBYZEROMSG);
		exit(1);
	}
	return 1/tan(a);
}

int main() {
	double input;
	printf("Enter alpha: ");
	if(scanf("%lf", &input) < 1) {
		printf(NONUMMSG);
		exit(1);
	}
	printf("Result: z1 = %f\n", z1(input));	
	printf("Result: z2 = %f\n", z2(input));
	return 0;
}
