#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int c);
int getfloat(double *pn);

int main() {
    double array[10];

    for (int n = 0; n < 10 && getfloat(&array[n]) != EOF; ++n)
        ;

    for (int i = 0; i < 10; ++i) {
        printf("%f\n", array[i]);
    }

    return 0;
}

int getfloat(double *pn)
{
    int c, sign;

    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-' ? -1 : 1);
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) {
            ungetch(sign < 0 ? '-' : '+');
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c=getch()) {
        *pn = 10 * *pn + (c - '0');
    }
    if (c == '.') {
        c = getch();
    }
    double power;
    for (power = 1; isdigit(c) ; c=getch()) {
        *pn = 10 * *pn + (c - '0');
        power *= 10;
    }
    *pn = *pn * sign / power;
    ungetch(c);

    return c;
}


int buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many chars");
    else
        buf[bufp++] = c;
}