#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define NONUMMSG "Error! No number entered!\n"

long fact(long num){
	return num > 1 ? num * fact(num - 1) : 1;
}

double S(double x, long n) {
	double sum = 0;
	for(long k = 0; k < n; k++) {
		sum += (k*k + 1)/fact(k) * pow(x/2, k);
	}
}

double Y(double x) {
	return (x*x/4 + x/2 + 1) * exp(x/2);
}

int main() {
	double x, y, a;
	printf("Enter x, y, a: ");
	if(scanf("%lf %lf %lf", &x, &y, &a) < 3) {
		printf(NONUMMSG);
		exit(1);
	}
	printf("Result: m = %f\n", m(x, y, a));
	return 0;
}