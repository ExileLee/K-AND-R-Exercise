#include <stdio.h>
#include <ctype.h>

#define MAXLEN 1000

int getLine(char s[], int maxlen);
double atof(char s[]);

int main() {
    char s[MAXLEN];

    while (getLine(s, MAXLEN) > 0) {
        double result = atof(s);
        printf("result: %f", result);
    }

    return 0;
}

int getLine(char s[], int maxLen) {
    char c;
    int i = 0;

    while (i < maxLen && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }

    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';

    return i;
}

double atof(char s[]) {
    double val, power;
    int i;

    for (i = 0; isspace(s[i]); ++i)
        ;
    int sign = s[i] == '-' ? -1 : 1;
    if (s[i] == '-' || s[i] == '+')
        i++;
    for (val = 0.0; isdigit(s[i]) ; ++i) {
        val = 10 * val + (s[i]-'0');
    }
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]) ; ++i) {
        val = 10.0 * val + (s[i]-'0');
        power *= 10.0;
    }

    if (tolower(s[i]) == 'e')
        i++;
    double expPower = s[i] == '-' ? 10.0 : 0.1;
    int exp = 0;
    if (s[i] == '-' || s[i] == '+')
        i++;
    if(isdigit(s[i]))
        exp = s[i]-'0';
    for (int j = 0; j < exp ; ++j) {
        power *= expPower;
    }

    return sign * val / power;
}
