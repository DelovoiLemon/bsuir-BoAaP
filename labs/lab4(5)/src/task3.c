#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define NONUMMSG "Error! No number entered!\n"
#define NULLPTRMSG "Error! Null pointer used!\n"

int main() {
	long *arr, min = 0, min_count = 1, sum = 0; int size;
	printf("Enter size: ");
	if(scanf("%ld", &size) < 1) {
		printf(NONUMMSG);
		return 1;
	}

	arr = (long*)malloc(size*sizeof(long));
	for(int i = 0; i < size; i++)
		scanf("%ld", arr+i);
	if(size == 1) {
		printf("No elements after minimal\n");
		return 0;
	}
	for(int i = 1; i < size; i++) {
		if(arr[i] < arr[min]) {
			min = i;
			min_count = 1;
		}
		else min_count += (arr[min] == arr[i]);
	}
	if(min_count != 1) {
		printf("There are %i min elements.\n"
		       "No idea after which one calculate sum.\n", min_count);
		return 0;
	}
	if(size - min == 1) {
		printf("Minimal element is last. Sum does not exist\n");
		return 0;
	}
	for(int i = size - 1; i > min; i--) sum += arr[i];

	printf("Sum equals %ld\n", sum);
	return 0;
}