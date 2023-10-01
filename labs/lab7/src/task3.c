#include<stdio.h>
#include<stdlib.h>
#define NONUMMSG "Error! No number entered!\n"
#define LATIN_COUNT ('z' - 'a' + 1)

char is_num(char c) { return c >= '0' && c <= '9'; }
char is_lower(char c) { return c >= 'a' && c <= 'z'; }
char is_upper(char c) { return c >= 'A' && c <= 'Z'; }
char is_latin(char c) { return is_upper(c) || is_lower(c); }
char get_alpha_start(char c) {
    if(is_lower(c)) return 'a';
    if(is_upper(c)) return 'A';
}
char get_letter_num(char c) { return c - get_alpha_start(c); }
char shift_letter(char c, int count) { return (is_latin(c)) ? get_alpha_start(c) + (get_letter_num(c) + count) % LATIN_COUNT :  c; }
void encrypt(char *str) { for(int i = 0; str[i]; i++) str[i] = shift_letter(str[i], 1); }
void decrypt(char *str) { for(int i = 0; str[i]; i++) str[i] = shift_letter(str[i], -1); }

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
    puts(str);

    return 0;
}
