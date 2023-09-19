#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define NONUMMSG "Error! No number entered!\n"

long task1(long n, char **array) {
  	long num_count = nums_count(n);
	*array = (char*) malloc(num_count*sizeof(char));
	while(n) {
		if(n % 10 % 3 == 0) {
			(*array)[valid_count] = n % 10;
			valid_count++;
		}
		n /= 10;
	}
	return num_count;
}
  
void task2(double *arr1, int arr1_len) {
	double a, tmp;
	int a_count = 0, tmp_count;
	for(int i = 0; i < arr1_len; i++) {
		tmp_count = 0;
		tmp = arr1[i];
		for(int j = i; j < arr1_len; j++) {
			if(tmp == arr1[j]) tmp_count++;
		}
		if(tmp_count > a_count) {
			a_count = tmp_count;
			a = tmp;
		}
	}
	const arr2_len = 5;
	double *arr2;
	arr2 = (double*) malloc(arr2_len*sizeof(double));
	printf
	for(int i = 1; i <= arr2_len; i++) {
		arr2[i] = pow(a, i);
		printf("%i\t", arr2[i]);
	}
	printf("\n");
}

int nums_count(int n){
	int count = 0;
	while(n) {
		n /= 10;
		count++
	}
	return count;
}

int main() {
	char *arr1; 
	long n, arr1_len;
	
	// Ввод исходных данных
	printf("Enter n: ");
	if(scanf("%d", &n) < 1) {
		printf(NONUMMSG);
		exit(1);
	}
        arr1_len = task1(n, &arr1);

	return 0;
}
