#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define DIVBYZEROMSG "Error! Zero division!\n"
#define NONUMMSG "Error! No number entered!\n"
#define PI 	3.1415926
#define MATH_E	2.7182818

double y(double z) {
	double x;
	if(z > 0) {
		printf("z > 0. Solving with x = 1/(z^2 + 2*z)\n");
		x = (1/(z*z + 2*z));
	} else {
		printf("z <= 0. Solving with x = 1 - z^3\n");
		x = 1 - z*z*z;
	}
	if(log(abs(x)) + x == 0) {
		printf(DIVBYZEROMSG);
		exit(1);
	}
	
	return (2*pow(MATH_E, -3*x) - 4*x*x) / (log(abs(x))+x);
}


int main() {
	double z;
	
	printf("Enter z: ");

	if(scanf("%lf", &z) < 1) {
		printf(NONUMMSG);
		exit(1);
	}

	printf("Result: y = %f\n", y(z));	

	return 0;
}
