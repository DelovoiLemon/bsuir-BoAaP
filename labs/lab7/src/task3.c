#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#define BUFFSIZE 256
#define LATIN_COUNT ('z' - 'a' + 1)
enum modes { enc = '1', dec = '2', quit = '3' };

char is_num(char c) { return c >= '0' && c <= '9'; }
char is_lower(char c) { return c >= 'a' && c <= 'z'; }
char is_upper(char c) { return c >= 'A' && c <= 'Z'; }
char is_latin(char c) { return is_upper(c) || is_lower(c); }
char get_alpha_start(char c) {
       return (is_lower(c)) ? 'a' : ((is_upper(c)) ? 'A' : '\0');
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

char read_mode() {
	char mode;
	do {
        	printf("Choose program mode:\n %c - encrypt\n %c - decrypt\n %c - exit\n\n", enc, dec, quit);
        	mode = getchar();
	} while(mode < enc || mode > quit);
	return mode;
}



int main() {
	int size; char *str, mode = 0; FILE* file = NULL;
	char *filename = "text.enc";
	while(mode != quit)
	{
		mode = read_mode();
		if(mode == enc) {
			printf("Enter string (up to 256 symbols): ");
			str = malloc(BUFFSIZE * sizeof(char));
			fgets(str, BUFFSIZE, file);
			str = realloc(str, get_str_size(str));
			encrypt(str);
			printf("Encrypted str: \n%s\n", str);
			if((file = fopen(filename, "w")) == NULL) { 
				printf("Can't open file for reading\n"); exit(1);
			}
			printf("Putting str to file\n");
			fputs(str, file);
			fclose(file);
		} else if(mode == dec) {
			printf("Trying to read %s\n", filename);
			if((file = fopen(filename, "r")) == NULL) { 
				printf("Error opening file"); exit(1); 
			}
			str = malloc(BUFFSIZE*sizeof(char));
			fgets(str, BUFFSIZE, file);
			str = realloc(str, get_str_size(str));
			decrypt(str);
			printf("Decrypted str:\n%s\n", str);
			fclose(file);
		}
	}
	free(str);
	return 0;
}
