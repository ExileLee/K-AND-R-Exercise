#include <stdio.h>

#define MAXLEN 1000

int strRightIndex(char s[], char t[]);
int getLine(char s[], int maxlen);

int main() {
    char s[MAXLEN];
    while (getLine(s, MAXLEN) > 0) {
        char pattern[] = "josie";
        int index = strRightIndex(s, pattern);
        if (index >= 0)
            printf("found at %d:%s",index ,s);

    }
    return 0;
}

int getLine(char s[], int maxlen) {
    int i, c;
    i = 0;

    while (i < maxlen - 1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = '\n';

    s[i] = '\0';

    return i;
}

int strRightIndex(char s[], char t[]) {
    int i, j, k;
    int len = 0;
    int tlen = 0;

    while (s[len] != '\0')
        len++;
    while (t[tlen] != '\0')
        tlen++;

    for (i = len-1; i >= tlen-1; --i) {
        for (j = i, k = tlen - 1; k >= 0 && s[j] == t[k]; --j, --k)
            ;
        if (tlen > 0 && k == -1)
            return i - (tlen-1);
    }

    return -1;
}