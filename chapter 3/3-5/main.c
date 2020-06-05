#include <stdio.h>
#include <string.h>
#include <limits.h>

void itoa(int n, char s[], int base);
void reverse(char s[]);

int main() {
    int base[] = {2, 8, 10, 16, 32};
    char s[1000];
    for (int i = 0; i < 5; ++i) {
        itoa(1356, s, base[i]);
        printf("base %-4d: %s\n", base[i], s);
    }
    return 0;
}

void itoa(int n, char s[], int base) {
    int i, sign;
    i = 0;
    if ((sign = n) > 0)
        n = -n;

    do {
        int decimal = -(n % base);
        if (decimal - 10 >= 0) {
            s[i++] = decimal % 10 + 'A';
        } else {
            s[i++] = decimal + '0';
        }
    } while((n /= base) < 0);
    if (sign < 0)
        s[i++] = '-';
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
