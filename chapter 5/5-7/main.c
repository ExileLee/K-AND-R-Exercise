#include <stdio.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];

int getLine(char *, int);
char *alloc(int);
int strcmp2(char *, char *);
void strcpy2(char *, char *);
int readlines(char *[], int, char *);
void writelines(char *[], int);
void qsort(char *[], int, int);

int main() {
    int nlines;
    char linestore[MAXLINES*MAXLEN];
    if ((nlines = readlines(lineptr, MAXLINES, linestore)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        return 1;
    }
}

void qsort(char *v[], int left, int right)
{
    void swap(char *[], int, int);
    if (left >= right)
        return;
    swap(v, left, (left+right)/2);
    int last = left;
    for (int i = left + 1; i <= right ; ++i) {
        if (strcmp2(v[i], v[left]) < 0)
            swap(v, ++last, i);
    }
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

void swap(char *v[], int left, int right)
{
    char *temp = v[left];
    v[left] = v[right];
    v[right] = temp;
}

int readlines(char *lineptr[], int maxlines, char *linestore)
{
    int len, nlines;
    char line[MAXLEN];

    nlines = 0;
    while ((len = getLine(line, MAXLEN)) > 0)
        if (nlines >= maxlines)
            return -1;
        else {
            line[len-1] = '\0';
            strcpy2(linestore, line);
            lineptr[nlines++] = linestore;
            linestore += len;
        }

    return nlines;
}

void writelines(char *lineptr[], int lines)
{
    while (lines--)
        printf("%s\n", *lineptr++);
}

int getLine(char *s, int maxlen)
{
    char *sp = s;
    while (--maxlen > 0 && (*s = getchar()) != '\n' && *s != EOF)
        s++;
    if (*s == '\n')
        s++;
    *s = '\0';

    return s-sp;
}

int strcmp2(char *s, char *t)
{
    for (; *s == *t ; s++, t++)
        if (*s == '\0')
            return 0;

    return *s-*t;
}

void strcpy2(char *s, char *t)
{
    while ((*s++ = *t++))
        ;
}

#define ALLOCSIZE 10000
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    }
    else
        return 0;
}