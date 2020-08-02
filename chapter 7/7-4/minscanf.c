#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>

#define BUFSIZE 1000
#define MAXLEN 100

int minscanf(char *fmt, ...);
int getLine(char *, int);
int getch(void);
void ungetch(int);

int main(int argc, char *argv[])
{
    int day, year;
    char month[10];
    int result = minscanf("%d %s %d", &day, month, &year);

    printf("result(%d): %d %s %d\n", result, day, month, year);

    return 0;
}

int minscanf(char *fmt, ...)
{
    int *dval, c, fieldLen, argCount;
    argCount = 0;
    char *sval, line[MAXLEN];
    va_list ap;

    va_start(ap, fmt);

    for (; *fmt; fmt++)
    {
        fieldLen = 0;
        for (; isspace(*fmt); fmt++)
            ;
        while (isspace((c = getch())))
            ;
        ungetch(c);
        if (*fmt == '%')
        {
            switch (*++fmt)
            {
            case 'd':
                while (isnumber((c = getch())))
                    line[fieldLen++] = c;
                ungetch(c);
                line[fieldLen] = '\0';
                dval = va_arg(ap, int *);
                *dval = atoi(line);
                break;
            case 's':
                sval = va_arg(ap, char *);
                while (!isspace((c = getch())))
                {
                    *sval++ = c;
                    fieldLen++;
                }
                ungetch(c);
                *sval = '\0';
                break;
            default:
                break;
            }
        }
        else if ((c = getch()) != *fmt)
            break;

        if (fieldLen > 0)
            argCount++;
    }
    
    va_end(ap);

    return argCount;
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