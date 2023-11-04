#include<stdio.h>
#include<stdlib.h>
#define NONUMMSG "Error! No number entered!\n"
#define BUFFERSIZE 256
int print_str(char *str) {
    int i = 0; 
    while(str[i]) putchar(str[i++]);
    return i;
}
int is_num(char c) { return c >= '0' && c <= '9'; }
int is_latin(char c) { return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'; }
void task(char *str) {
	for(int i = 0;str[i]; i++) {
        	if(is_latin(str[i])) str[i] = '*';
        	else if(is_num(str[i])) str[i] = '#';
	}
}
int main() {
	int size; char *str = malloc(BUFFERSIZE*sizeof(char));
	printf("Enter string: "); scanf("%[^\n]s", str);
	printf("Readed string: ");
	str = realloc(str, print_str(str)*sizeof(char));
	task(str);
	printf("\nResult:\n"); print_str(str);
	free(str);
	putchar('\n');
	return 0;
}
