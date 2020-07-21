#include <stdio.h>

#define MAXLINE 1000

int getLine(char s[], int lim);
void reverse(char s[]);

int main() {
    int len, max;
    char line[MAXLINE];

    max = 0;
    while ((len = getLine(line, MAXLINE)) > 0) {
        reverse(line);
        printf("%s", line);
    }

    return 0;
}

int getLine(char s[], int lim) {
    int c, i, bankCount;
    bankCount = 0;
    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        i++;
    }

    s[i] = '\0';

    return i;
}

void reverse(char s[]) {
    int len = 0;
    while (s[len + 1] != '\n' && s[len + 1] != '\0') {
        len++;
    }

    for (int i = len; len - i < i; i--) {
        char swap = s[len-i];
        s[len-i] = s[i];
        s[i] = swap;
    }
}
