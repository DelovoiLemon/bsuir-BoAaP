#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define NONUMMSG "Error! No number entered!\n"
#define NULLPTRMSG "Error! Null pointer used!\n"

void draw_array(long *array, long cols, long rows) 
{
	for(int i = 0; i < cols; i++) {
		for(int j = 0; j < rows; j++) {
			printf("%i\t", array[i+cols*j]);
		}
		printf("\n");
	}
}

long nums_count(long n){
	long count = 0;
	while(n) count++, n /=10;
	return count;
}

long get_nums(long n, long **array){
	long i; *array = malloc(nums_count(n)*sizeof(char));
	if(*array == NULL) {
	    printf(NULLPTRMSG);
	    exit(1);
	}
	for(i = 0; n; i++) {
		(*array)[i] = n % 10;
		n /= 10;
	}
	return i;
}

long task(long n, long **arr) {
    long n_count = get_nums(n, arr);
    
    for(long i = 0; i < n_count; i++) {
        (*arr)[i] = (*arr)[i] * (*arr)[i];
    }
    return n_count;
}

int main() {
	char *arr1; 
	int n, arr_len;
	
	// Ввод исходных данных
	printf("Enter n: ");
	if(scanf("%d", &n) < 1) {
		printf(NONUMMSG);
		exit(1);
	}

	arr_len = task(n, &arr1);
	printf("Task 1:\n");
	draw_array(arr1, 1, arr_len);
	
	return 0;
}
