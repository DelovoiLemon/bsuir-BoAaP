#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define NONUMMSG "Error! No number entered!\n"

double my_abs(double n) { return n > 0 ? n : -n; }
long fact(long num){ return num > 1 ? num * fact(num - 1) : 1; }

double S(double x, long n) {
	double sum = 0;
	for(long k = 0; k <= n; k++) 
		sum += (k*k + 1.)/fact(k) * pow(x/2, k);
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
