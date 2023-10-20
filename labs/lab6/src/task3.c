#include<stdio.h>
#include<stdlib.h>
#define NONUMMSG "Error! No number entered!\n"

void print_str(char *str) {
    int i = 0;
    while(str[i]) {
        putchar(str[i]);
        i++;
    }
}

int is_num(char c) { return c >= '0' && c <= '9'; }
int is_latin(char c) { return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'; }

void task(char *str) {
    int i = 0;
    while(str[i]) {
        if(is_latin(str[i])) str[i] = '*';
        else if(is_num(str[i])) str[i] = '#';
        i++;
    }
}

int main() {
    int size;
    char *str;
    printf("Enter str size: ");
    if(scanf("%i", &size) < 1) {
		printf(NONUMMSG);
		exit(1);
	}
	size++;
	str = malloc((size)*sizeof(char));
	printf("Enter string: ");
	for(int i = 0; i <= size; i++) {
        str[i] = getchar();
	}
    str[size+1] = '\0';
    task(str);
    printf("Result:\n");
    print_str(str);

    return 0;
}
