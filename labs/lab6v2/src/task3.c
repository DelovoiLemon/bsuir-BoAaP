#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define NONUMMSG "Error! No number entered!\n"
#define NULLPTRMSG "Error! Null pointer used!\n"

int main() {
	int *arr, m, n, count = 0;
	printf("Enter size(m, n): ");
	if(scanf("%d%d", &m, &n) < 2) {
		printf(NONUMMSG);
		return 1;
	}
	arr = malloc(m*n*sizeof(int));

	for(int i = 0; i < m*n; i++)
		scanf("%d", arr+i);

    if(n < 3) {
        printf("There are no elements with 2 neighbours.\n");
        return 1;
    }

	for(int i = 0; i < m; i++)
		for(int j = 1; j < n - 1; j++)
			if((arr[i*n + j] > arr[i*n + j - 1]) && (arr[i*n + j] < arr[i*n + j + 1])) count++;


	printf("Count equals %d.\n", count);
	free(arr);
	return 0;
}
