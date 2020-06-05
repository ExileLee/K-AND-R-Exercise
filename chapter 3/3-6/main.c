#include <stdio.h>
#include <string.h>
#include <limits.h>

void itoa(int n, char s[], int pad);
void reverse(char s[]);

int main() {
    for (int i = 10; i < 50000000; i = i * 20) {
        char s[1000];
        itoa(i, s, 50);
        printf("%s\n", s);
    }

    return 0;
}

void itoa(int n, char s[], int pad) {
    int i, sign;
    i = 0;
    if ((sign = n) > 0)
        n = -n;

    do {
        s[i++] = -(n % 10) + '0';
    } while((n /= 10) < 0);
    if (sign < 0)
        s[i++] = '-';

    while (i < pad) {
        s[i++] = ' ';
    }
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[]) {
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
