#include <stdio.h>

#define MAXLEN 1000
int itoa(int n, char s[]);

int main() {
    char s[MAXLEN];
    itoa(345, s);
    printf("%s\n", s);
    return 0;
}

int itoa(int n, char s[])
{
    static int negiative = 0;
    int i = 0;
    if (n < 0) {
        negiative = 1;
        n = -n;
    }

    if (n / 10) {
        i = itoa(n / 10,  s);
    }

    if (negiative && i == 0) {
        s[i++] = '-';
    }
    s[i++] = n % 10 + '0';
    s[i] = '\0';

    return i;
}
