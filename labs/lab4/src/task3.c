#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define NONUMMSG "Error! No number entered!\n"

typedef double (*TFunc)(double);
typedef double (*TFunc2)(double, int);

double my_abs(double n) { return n > 0 ? n : -n; }

void out_table(TFunc f1, TFunc2 f2, double a, double b, double h, int n) {
	double s, y;
	for(; a < b + h/2; a += h) {
		y = f1(a);
		s = f2(a, n);
		printf("x = %5.2lf, y = %8.4lf, s = %8.4lf, delta = %2.6lf\n", a, y, s, my_abs(y - s));
	}	
}

double S(double x, int n) {
	double r = 1, sum = 1, xdiv2 = x / 2.;
	for(long k = 1; k <= n; k++) { 
		r *= xdiv2 / k;
		sum += r * (k*k + 1);
	}
	return sum;
}

double Y(double x) { return (x*x/4 + x/2 + 1) * exp(x/2); }

int main() {
	double a, b, h; int n;
	printf("Enter a, b, h, n: ");
	if(scanf("%lf%lf%lf%d", &a, &b, &h, &n) < 4) {
		printf(NONUMMSG);
		exit(1);
	}	
	out_table(Y, S, a, b, h, n);

	return 0;
}
