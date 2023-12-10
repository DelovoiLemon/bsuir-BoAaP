#include<stdio.h>
#include<stdlib.h>
#define NONUMMSG "Error! No number entered!\n"

void print_c(char c, int n) 
{
	for(; n > 0; n--) putc(c);
}

typedef vec struct vector { int x, y; }

int main()
{
	int h, w;
	vec offset;
	offset.x = 0;
	offset.y = 0;

	printf("Enter height, width: ");
	scanf("%d%d", &h, &w);

	for(int i = 0; i < h; i++) 
	{
		for(int j = 0; j < w; j++) {
		
		}
	}

	return 0;
}
