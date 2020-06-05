#include <stdio.h>

#define MAXLEN 1000
#define TAB 4

int getLine(char s[]);

int main() {

    char line[MAXLEN];

    while (getLine(line) > 0) {
        printf("%s", line);
    }

    return 0;
}

int getLine(char s[]) {
    int i, c, spaceC;

    i = spaceC = 0;
    while (i < MAXLEN - 1 && (c = getchar()) != EOF && c != '\n') {
        if (c == ' ') {
            spaceC++;
            if (spaceC >= TAB) {
                s[i++] = '\t';
                spaceC = 0;
            }
        } else {
            for (int j = 0; j < spaceC; ++j)
                s[i++] = ' ';
            spaceC = 0;
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