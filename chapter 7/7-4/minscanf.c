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
    float f;
    char month[10];
    int result = minscanf("%d %s %d %f", &day, month, &year, &f);

    printf("result(%d): %d %s %d %.1f\n", result, day, month, year, f);

    return 0;
}

int minscanf(char *fmt, ...)
{
    int *dval, c, fieldLen, argCount;
    float *fval;
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
            case 'f':
                while (isnumber((c = getch())))
                    line[fieldLen++] = c;
                if (c == '.')
                {
                    line[fieldLen++] = c;
                    while (isnumber((c = getch())))
                        line[fieldLen++] = c;
                    ungetch(c);
                    line[fieldLen] = '\0';
                    fval = va_arg(ap, float *);
                    *fval = strtof(line, NULL);    
                }
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