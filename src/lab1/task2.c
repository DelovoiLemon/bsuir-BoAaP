#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define DIVBYZEROMSG "Error! Zero division!\n"
#define NONUMMSG "Error! No number entered!\n"
#define PI 3.1415926

double z1(double b) {
	return pow(cos(3.0*PI/8 - b/4), 2) - pow(cos(11.0*PI/8 + b/4), 2);
}

double z2(double b) {
	return (sqrt(2)/2) * sin(b/2);
}

int main() {
	double input = 1.5;
	int test;
	printf("Enter alpha: ");

	if(scanf("%lf", &input) < 1) {
		printf(NONUMMSG);
		exit(1);
	}

	printf("Result: z1 = %f\n", z1(input));
	printf("Result: z2 = %f\n", z2(input));

	return 0;
}