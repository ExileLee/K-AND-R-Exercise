#include <stdio.h>
#include <ctype.h>

#define MAXLEN 1000

void expand(char s1[], char s2[]);
int isAlphaRange(char c1, char c2);

int main() {
    char s1[] = "-a-zA-Z-0-9--gg";
    char s2[MAXLEN];
    expand(s1, s2);
    printf("%s\n", s2);
    return 0;
}

void expand(char s1[], char s2[]) {
    int i, j, k;
    i = j = k = 0;

    while(s1[i] != '\0') {
        if (isdigit(s1[i]) || (s1[i] >= 'A' && s1[i] <= 'z')) {
            s2[j++] = s1[i];
        }

        for (k = i + 1; s1[k] == '-' ; ++k)
            ;

        if (k > (i + 1) && isAlphaRange(s1[k], s1[i])) {
            for (int l = s1[i] + 1; l <= s1[k]; ++l) {
                s2[j++] = l;
            }
            k++;
        }

        i = k;
    }

    s2[j] = '\0';
}

int isAlphaRange(char c1, char c2) {
    return (isdigit(c1) && isdigit(c2)) ||
           (c1 >= 'A' && c1 <= 'Z' && c2 >= 'A' && c2 <= 'Z') ||
           (c1 >= 'a' && c1 <= 'z' && c2 >= 'a' && c2 <= 'z');
}
