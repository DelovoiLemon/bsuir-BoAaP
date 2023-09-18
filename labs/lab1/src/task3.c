#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define DIVBYZEROMSG "Error! Zero division!\n"
#define NEGATIVEINSQRTMSG "Error! Negative number in parameter of sqrt!"
#define NONUMMSG "Error! No all numbers entered!\nPlease enter 3 parameters."

double b(double x, double y, double z) {
	if(x + y < 0) {
		printf(NEGATIVEINSQRTMSG);
		exit(1);
	}
	if(pow(MATH_E, abs(x-y) + x/2) == 0){
		printf(DIVBYZEROMSG);
		exit(1);
	}
	return 	pow(y, pow(abs(x), 1.0/3)) + pow(cos(y), 3) *
		(abs(x-y)*(1+pow(sin(z), 2)) / sqrt(x+y)) / (exp(abs(x - y))+ x/2);
}

int main() {
	double x, y, z;	
	printf("Enter x, y, z: ");
	if(scanf("%lf %lf %lf", &x, &y, &z) < 3) {
		printf(NONUMMSG);
		exit(1);
	}
	printf("Result: b = %f\n", b(x, y, z));	
	return 0;
}
