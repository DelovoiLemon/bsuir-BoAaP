#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define DIVBYZEROMSG "Error! Zero division!\n"
#define NONUMMSG "Error! Not all numbers entered!\n Three arguments required.\n"
#define PI 	3.1415926
#define MATH_E	2.7182818

double y(double x) {
	 return (x/2)*cos(x) - sin(x);
}

double s(double x) {
	double sum = 0;
	for(int k = 0; k < n; k++) {
		sum += (k*k + 1)
	}
}

double max2(double x, double y){
	return x > y ? x : y;
}

double min2(double x, double y) {
	return x < y ? x : y;
}

int main() {
	double a, b, h, min = INFINITY, max = 0, current;
	
	printf("Enter a, b, h: ");

	if(scanf("%lf %lf %lf", &a, &b, &h) < 3) {
		printf(NONUMMSG);
		exit(1);
	}


	for(int i = 0; a+i*h <= b; i++) {
		current = y(a+i*h);
		min = min2(current, min);
		max = max2(current, max);
		printf("%d\t%f\t%f\n", i, a+i*h, current);
		a += h;
	}
	
	printf("Minimal = %f\nMaximal = %f\n", min, max);

	return 0;
}
