#include<stdio.h>
#include<stdlib.h>
#define NONUMMSG "Error! No number entered!\n"
#define BUFFSIZE 256
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
char shift_letter(char c, int count) { 
	return (is_latin(c)) ? get_alpha_start(c) + (get_letter_num(c) + count) % LATIN_COUNT :  c; 
}
int get_str_size(char *str) {
	int n = 0; while(str[n++]);
	return n;
}
void encrypt(char *str) { for(int i = 0; str[i]; i++) str[i] = shift_letter(str[i], -1); }
void decrypt(char *str) { for(int i = 0; str[i]; i++) str[i] = shift_letter(str[i], 1); }

int main() {
	int size; char *str; FILE* file;
	char *filename = "text.enc";
	printf("Enter e to encrypt, <anykey> to decrypt: ");
	switch(getchar()) {
		case 'e':
			printf("Enter string: ");
			str = malloc(BUFFSIZE*sizeof(char));
			scanf("\n%256[^\n]", str);
			str = realloc(str, get_str_size(str));
			encrypt(str);
			printf("Encrypted str: \n%s\n", str);
			if((file = fopen(filename, "w")) == NULL) { 
				printf("Error opening file"); exit(1);
			}
			printf("Putting str to file\n");
			fprintf(file, "%s", str);
			fclose(file);
			break;
		default:
			printf("Trying to read text.enc\n");
			if((file = fopen(filename, "r")) == NULL) { 
				printf("Error opening file"); exit(1); 
			}
			str = malloc(BUFFSIZE*sizeof(char));
			fscanf(file, "%[^\n]s", str);
			str = realloc(str, get_str_size(str));
			fclose(file);
			decrypt(str);
			printf("Decrypted str:\n%s\n", str);
			break;
	}
	free(str);
	return 0;
}
