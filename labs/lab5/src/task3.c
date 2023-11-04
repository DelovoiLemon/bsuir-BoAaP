#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define NONUMMSG "Error! No number entered!\n"
#define NULLPTRMSG "Error! Null pointer used!\n"

void draw_array(long **array, long cols, long rows) {
	for(int i = 0; i < cols; i++) {
		for(int j = 0; j < rows; j++)
        		printf("%i\t", array[i][j]);
		printf("\n");
	}
}

long get_num() {
    long n;
    if(scanf("%ld", &n) < 1) { printf(NONUMMSG); exit(1); }
    return n;
}

void task(long n, long **arr) {
    for(long i = 0; i < n; i++) {
        for(long j = 0; j < n; j++)
            if(i != j) arr[i][j] = (arr[i][j] > arr[i][i]);
        arr[i][i] = 0;
    }
}

int main() {
	long **arr, n;
	printf("Enter n(0 to test): ");
	n = get_num();
	if(n != 0) {
		arr = malloc(n*sizeof(long));
        	for(long i = 0; i < n; i++) {
	    		arr[i] = malloc(n*sizeof(long));
            		for(long j = 0; j < n; j++)
                		arr[i][j] = get_num();
    		}	
	}

	printf("\nReaded arr:\n");
	draw_array(arr,n,n);
	task(n, arr);
	printf("Task:\n");
	draw_array(arr, n, n);
	for(int i = 0; i < n; i++) free(arr[i]);
	free(arr);
	return 0;
}
