#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define NONUMMSG "Error! No number entered!\n"

double my_abs(double n) { return n > 0 ? n : -n; }
long fact(long num){ return num > 1 ? num * fact(num - 1) : 1; }

double S(double x, long n) {
	double r = 1, sum = 1, xdiv2 = x / 2.;
	for(long k = 1; k <= n; k++) { 
		r *= xdiv2 / k;
		sum += r * (k*k + 1);
	}
	return sum;
}

double Y(double x) { return (x*x/4 + x/2 + 1) * exp(x/2); }

int main() {
	double x, e; int n;
	printf("Enter x, e: ");
	if(scanf("%lf %lf", &x, &e) < 2) {
		printf(NONUMMSG);
		exit(1);
	}
	for(n = 1; my_abs(S(x, n) - Y(x)) >= e; n++) {
		printf("%lf\t%lf\t%lf\n", S(x, n), Y(x), my_abs(S(x, n) - Y(x)));
	}
	printf("Delta = %lf\nResult n = %i\n", my_abs(S(x, n) - Y(x)), n);
	return 0;
}
