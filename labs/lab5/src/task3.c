#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define NONUMMSG "Error! No number entered!\n"
#define NULLPTRMSG "Error! Null pointer used!\n"

void draw_array(long *array, long cols, long rows) {
	for(int i = 0; i < cols; i++) {
		for(int j = 0; j < rows; j++)
            printf("%i\t", array[i*cols+j]);
		printf("\n");
	}
}

long get_num() {
    long n;
    if(scanf("%ld", &n) < 1) {
		printf(NONUMMSG);
		exit(1);
	}
	return n;
}

long nums_count(long n) {
	long count = 0;
	while(n) count++, n /=10;
	return count;
}

void task(long n, long *arr) {
    for(long i = 0; i < n; i++) {
        for(long j = 0; j < n; j++)
            if(i != j)
                arr[i*n+j] = (arr[i*n+j] > arr[i*n+i]);
        arr[i*n+i] = 0;
    }
}

int main() {
    long test_arr[] = {
        3, 2, 1, 5,
        1, 2, 3, 1,
        8, 5, 6, 7,
        2, 3, 7, 6
    };
	long *arr, n;
	printf("Enter n(0 to test): ");
	n = get_num();
	if(n != 0) {
        arr = malloc(n*n*sizeof(long));
        for(long i = 0; i < n; i++)
            for(long j = 0; j < n; j++)
                arr[i*n+j] = get_num();
    } else {
        n = 4;
        arr = test_arr;
        draw_array(arr, n, n);
    }
	task(n, arr);
	printf("Task:\n");
	draw_array(arr, n, n);

	return 0;
}
