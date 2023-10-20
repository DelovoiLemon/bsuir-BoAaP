#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define NONUMMSG "Error! No number entered!\n"
#define NULLPTRMSG "Error! Null pointer used!\n"

void draw_array(long *array, long cols, long rows) 
{
	for(int i = 0; i < cols; i++) {
		for(int j = 0; j < rows; j++) printf("%i\t", array[i+cols*j]);
		printf("\n");
	}
}

long nums_count(long n){
	long count = 0;
	while(n) count++, n /=10;
	return count;
}

long task(long n, long **arr) {
    long tmp, size = nums_count(n);
    *arr = malloc(size*sizeof(char));
    for(long i = size -1; i >= 0;i--) {
        tmp = n % 10;
        (*arr)[i] = tmp*tmp;
        n /= 10;
    }
    return size;
}

int main() {
	long *arr1; 
	long n, arr_len;
	printf("Enter n: ");
	if(scanf("%ld", &n) < 1) {
		printf(NONUMMSG);
		exit(1);
	}
	arr_len = task(n, &arr1);
	printf("Task 1:\n");
	draw_array(arr1, 1, arr_len);
	
	return 0;
}
