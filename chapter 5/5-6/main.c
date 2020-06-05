/*
 * Author: Boyi, Lee
 * K & R Exercise 5-6
 * Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing.
 * Good possibilities include getline (Chapters 1 and 4), atoi , itoa , and their variants (Chapters 2, 3, and 4),
 * reverse (Chapter 3), and strindex and getop (Chapter 4).
 */
#include <stdio.h>
#include <ctype.h>

#define MAXLEN 1000

int getLine(char *s, int maxlen);
int atoi(char *s);
void itoa(int n, char *s);
void reverse(char *s);
int strindex(char *s, char *t);

int main() {
    char s[MAXLEN];
    while (getLine(s, MAXLEN) > 0) {
        printf("Print:%s\n", s);
    }

    char a[] = "-1989";
    printf("%i\n", atoi(a));

    char itoas[MAXLEN];
    itoa(-1999, itoas);
    printf("%s\n", itoas);

    printf("%i", strindex("my chechemical romance", "chemical"));

    return 0;
}

int getLine(char *s, int maxlen)
{
    int c;
    char *sp = s;
    while (s-sp < maxlen && (c = getchar()) != '\n' && c != EOF)
        *s++ = c;
    if (*s == '\n')
        *s++ = c;

    return s-sp;
}

int atoi(char *s)
{
    int n, sign;
    n = 0;
    while (isspace(*s))
        s++;
    sign = *s == '-' ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    while (isdigit(*s))
        n = 10 * n + (*s++ -'0');

    return n * sign;
}

void itoa (int n, char *s)
{
    char *sp = s;
    int sign = n;
    n = n < 0 ? (n * -1) : n;
    do {
        *s++ = (n % 10) + '0';
        n /= 10;
    } while (n);
    if (sign < 0)
        *s++ = '-';
    *s = '\0';
    reverse(sp);
}

void reverse(char *s)
{
    char *t;
    for (t = s; *(t+1) != '\0'; t++)
        ;
    while (t > s) {
        char temp = *t;
        *t-- = *s;
        *s++ = temp;
    }
}

int strindex(char *s, char *t)
{
    char *tp = t;
    char *sp = s;
    for (int i = 0; *s; i++, s++, sp = s) {
        for (tp = t; *sp == *tp; tp++, sp++)
            ;

        if (*tp == '\0')
            return i;
    }

    return -1;
}

#define BUFSIZE 100

int buf[BUFSIZE];
int *bufp = buf;

int getch(void)
{
    return bufp != buf ? *--bufp : getchar();
}

void ungetch(int c)
{
    if (bufp > bufp + BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        *bufp++ = c;
}

#define NUMBER 0

int getop(char *s)
{
    int c;

    while ((*s = c = getch()) == ' ' || c == '\t')
        ;
    *++s = '\0';
    if (!isdigit(c) && c != '.')
        return c;
    s--;
    if (isdigit(c))
        while (isdigit(*++s = c = getch()))
            ;
    if (c == '.')
        while (isdigit(*++s = c = getch()))
            ;
    *s = '\0';
    ungetch(c);

    return NUMBER;
}