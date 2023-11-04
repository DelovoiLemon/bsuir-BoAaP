#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define NONUMMSG "Error! No number entered!\n"
#define NULLPTRMSG "Error! Null pointer used!\n"

int min(int x, int y) { return x > y ? y : x; }
int get_words_count(char *s)
{
    int count = 0, flag = 1;
    for(int i = 0; s[i]; i++)
    {
        if(s[i] == ' ') {
            flag = 1;
        }
        else if(flag){
            flag = 0;
            count++;
        }
    }
    return count;
}
// return true if first is erlier
int lex_comp(char *s, int n1, int n2)
{
    for(int i = 0; s[i+n1] != EOF && s[i+n2] != EOF && s[i+n1] != ' ' && s[i+n2] != ' '; i++)
    {
        if(s[i+n1] != s[i+n2]) return (s[i+n1] > s[i+n2]);
    }
    return 0;
}


int main() {
    char *str = "    pls dow ban qbt";
    int *w_start, w_count, flag = 1, tmp;

    w_count = get_words_count(str);
    w_start = malloc(w_count*sizeof(char));

    for(int i = 0, j = 0; str[i]; i++)
    {
        if(str[i] == ' ') {
            flag = 1;
        }
        else if(flag){
            flag = 0;
            w_start[j] = i;
            j++;
        }
    }

    flag = (w_count > 1);
    while(flag)
    {
        flag = 0;
        for(int i = 1; i < w_count; i++)
        {
            if(lex_comp(str, w_start[i-1], w_start[i]))
            {
                tmp = w_start[i - 1];
                w_start[i - 1] = w_start[i];
                w_start[i] = tmp;
                flag = 1;
            }
        }
    }

    for(int i = 0; i < w_count; i++)
    {
        for(int j = w_start[i]; str[j] != ' ' && str[j]; j++)
            putc(str[j], stdout);
        putc('\n', stdout);
    }

	free(str);
    free(w_start);
	return 0;
}
