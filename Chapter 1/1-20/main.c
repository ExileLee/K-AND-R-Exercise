#include <stdio.h>

#define MAXLEN 1000
#define TAB 1

int getLine(char s[]);

int main() {

    char line[MAXLEN];

    while (getLine(line) > 0) {
        printf("%s", line);
    }

    return 0;
}

int getLine(char s[]) {
    int i, c;

    i = 0;
    while (i < MAXLEN - 1 && (c = getchar()) != EOF && c != '\n') {
        if (c == '\t') {
            for (int j = 0; j < TAB; ++j) {
                s[i++] = ' ';
            }
        }else {
            s[i++] = c;
        }
    }

    if (c == '\n') {
        s[i] = c;
        i++;
    }

    s[i] = '\0';

    return i;
}