#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define NONUMMSG "Error! No number entered!\n"
double min(double x , double y) { return (x > y) ? y : x; }
double max(double x, double y) { return (x > y) ? x : y; }
double m(double x, double y, double a) {
	if(a < 0) return min(x*x, y*y)+a;
	if(a == 0) return max(max(y, x), a);
	if(a > 0) return abs(x-y)+y*(x+pow(a, 1.5));
}
int main() { double x, y, a;
	printf("Enter x, y, a: ");
	if(scanf("%lf %lf %lf", &x, &y, &a) < 3) { printf(NONUMMSG); exit(1); }
	printf("Result: m = %f\n", m(x, y, a)); return 0;
}
