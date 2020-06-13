/*
Author: Boyi, Lee
-----------------------
K&R Exercise 5-15:
Add the option -f to fold upper and lower case together, 
so that case distinctions are not made during sorting; 
for example, a and A compare equal.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 1000
#define MAXLINES 5000

char *lineptr[MAXLINES];
int reverse = 1;

int readlines(char *[], int);
void writelines(char *[], int);
int geLine(char *, int);

void myqsort(void *[], int left, int right, int (*cmp)(void *, void *), int desc);
int numcmp(const char *, const char *);
int strcmpf(const char *, const char *);

int main(int argc, char *argv[])
{
    int nlines;
    int numeric = 0;
    int fold = 0;
    int desc = 1;

    while (--argc > 0 && (*++argv)[0] == '-')
    {
        switch (*++argv[0])
        {
        case 'n':
            numeric = 1;
            break;
        case 'r':
            desc = -1;
            break;
        case 'f':
            fold = 1;
            break;
        default:
            argc = -1;
            break;
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) > 0)
    {
        myqsort((void *)lineptr,
                0,
                nlines - 1,
                (int (*)(void *, void *))(numeric ? numcmp : (fold ? strcmpf : strcmp)),
                desc);
        writelines(lineptr, nlines);
        return 0;
    }

    return 0;
}

void myqsort(void *v[], int left, int right, int (*cmp)(void *, void *), int desc)
{
    int pivot;
    void swap(void *[], int, int);
    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    pivot = left;
    for (int i = left + 1; i <= right; i++)
    {
        if (((*cmp)(v[i], v[left]) * desc) < 0)
            swap(v, ++pivot, i);
    }
    swap(v, left, pivot);
    myqsort(v, left, pivot - 1, cmp, desc);
    myqsort(v, pivot + 1, right, cmp, desc);
}

void swap(void *v[], int left, int right)
{
    void *temp = v[left];
    v[left] = v[right];
    v[right] = temp;
}

int numcmp(const char *s1, const char *s2)
{
    double v1, v2;
    v1 = strtod(s1, NULL);
    v2 = strtod(s2, NULL);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int strcmpf(const char *s1, const char *s2)
{
    while(toupper(*s1++) == toupper(*s2++))
        if (*s1 == '\0' && *s2 == '\0')
            return 0;
    return toupper(*s1)-toupper(*s2);            
}

#define ALLOCSIZE 1000

char allocbuffer[ALLOCSIZE];
char *allocp = allocbuffer;

char *alloc(int n)
{
    if (allocbuffer + ALLOCSIZE - allocp >= n)
    {
        allocp += n;
        return allocp - n;
    }
    else
        return NULL;
}

int getLine(char *s, int maxlen)
{
    int c, i;
    i = 0;
    while (maxlen-- > 0 && (c = getchar()) != '\n' && c != EOF)
        s[i++] = c;
    if (c == '\n')
        s[i++] = '\n';
    s[i] = '\0';

    return i;
}

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getLine(line, MAXLEN)) > 0)
    {
        if (nlines > MAXLINES || (p = alloc(len)) == NULL)
            return -1;
        else
        {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }

    return nlines;
}

void writelines(char *lineptr[], int maxlines)
{
    while (maxlines-- > 0)
        printf("%s\n", *lineptr++);
}