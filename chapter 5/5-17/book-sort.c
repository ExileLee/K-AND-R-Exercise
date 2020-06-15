/*
Author: Boyi, Lee
-----------------------
K&R Exercise 5-17:
Add a field-handling capability, so sorting may be done on fields within lines,
each field sorted according to an independent set of options. 
(The index for this book was sorted with -df for the index category and -n for the page numbers.)
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 1000
#define MAXLINES 5000
#define FIELDLEN 4

char **books[MAXLINES];
char *fields[FIELDLEN] = {"Name", "Category", "Pages", "Author"};

int numeric = 0;
int fold = 0;
int directory = 0;
int desc = 1;
int sortfield = 0;

int readbooks(char **books[], int maxlines);
void displaybooks(char **books[], int maxlines);
int geLine(char *, int);

void myqsort(void **[], int left, int right, int (*cmp)(void *, void *));
int numcmp(const char *, const char *);
int mystrcmp(const char *, const char *);
int validDirectoryChar(char);

int main(int argc, char *argv[])
{
    int nlines;
    char *optionp;
    while (--argc > 0 && (*++argv)[0] == '-')
    {
        while (isdigit(*++argv[0]))
            sortfield = sortfield * 10 + (*argv[0]-'0');

        if (sortfield < 0 || sortfield >= FIELDLEN)
        {
            printf("error: valid field 0-3");
            argc = -1;
        }

        while (*argv[0])
        {
            switch (*argv[0])
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
            case 'd':
                directory = 1;
                break;
            default:
                argc = -1;
                printf("error: not valid argument");
                break;
            }
            ++argv[0];
        }
    }

    if (argc < -1)
        return 1;

    if ((nlines = readbooks(books, MAXLINES)) > 0)
    {
        myqsort((void ***)books,
                0,
                nlines - 1,
                (int (*)(void *, void *))(numeric ? numcmp : mystrcmp));
        printf("\nResult:\n\n");
        displaybooks(books, nlines);
        return 0;
    }

    return 0;
}

void myqsort(void **v[], int left, int right, int (*cmp)(void *, void *))
{
    int pivot;
    void swap(void **[], int, int);
    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    pivot = left;
    for (int i = left + 1; i <= right; i++)
    {
        if (((*cmp)(v[i][sortfield], v[left][sortfield]) * desc) < 0)
            swap(v, ++pivot, i);
    }
    swap(v, left, pivot);
    myqsort(v, left, pivot - 1, cmp);
    myqsort(v, pivot + 1, right, cmp);
}

void swap(void **v[], int left, int right)
{
    void **temp = v[left];
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

int mystrcmp(const char *s1, const char *s2)
{
    char c1, c2;
    while (*s1)
    {
        while (directory && !validDirectoryChar(*s1))
            s1++;
        while (directory && !validDirectoryChar(*s2))
            s2++;
        c1 = fold ? toupper(*s1) : *s1;
        c2 = fold ? toupper(*s2) : *s2;

        if (c1 != c2)
            break;

        s1++, s2++;
    }

    if (*s1 == '\0')
        return 0;

    return c1 - c2;
}

int validDirectoryChar(char c)
{
    return isalpha(c) || isspace(c) || isdigit(c);
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

int readbooks(char **books[], int maxlines)
{
    char **readrow();

    int len, nlines;
    char *linep, line[MAXLEN];
    char **row;
    nlines = 0;
    printf("-----enter row %i-----\n", nlines + 1);
    while ((row = readrow()) != NULL)
    {
        books[nlines++] = row;
        printf("-----enter row %i-----\n", nlines + 1);
    }

    return nlines;
}

char **readrow()
{
    int len, fieldn;
    char *valuep, input[MAXLEN];
    char **row = malloc(sizeof(char *) * FIELDLEN);
    fieldn = 0;
    while (fieldn < FIELDLEN)
    {
        printf("%s: ", fields[fieldn]);
        len = getLine(input, MAXLEN);

        if (len < 1)
            return NULL;

        if ((valuep = malloc(sizeof(char) * len)) == NULL)
            return NULL;
        else
        {
            input[len - 1] = '\0';
            strcpy(valuep, input);
            row[fieldn++] = valuep;
        }
    }

    return row;
}

void displaybooks(char **books[], int maxlines)
{
    int i, j;
    int filedlen = FIELDLEN;

    for (i = 0; i < FIELDLEN; i++)
        printf("%-28s ", fields[i]);
    printf("\n");      
    for (i = 0; i < FIELDLEN; i++)
        printf("%s ", "----------------------------");
    printf("\n");    

    for (i = 0; i < maxlines; i++)
    {
        for (j = 0; j < FIELDLEN; j++)
            printf("%-28s ", books[i][j]);
        printf("\n");    
    }
}