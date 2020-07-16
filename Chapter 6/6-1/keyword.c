#include <stdio.h>
#include <ctype.h>
#include <string.h>

enum { COMMENT, CONTROLLINE, STRINGCONST, NOPREFIX };

struct key
{
    char *word;
    int count;
} keytab[] = {
    "auto", 0,
    "b re", 0,
    "case", 0
};

#define MAXWORD 100
#define BUFSIZE 1000
#define NKEYS (sizeof keytab / sizeof(struct key))

int getword(char *, int);
int binsearch(char *, struct key *, int);
int getprefix(char);
int getch(void);
void ungetch(int);

int main()
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
    {
        if (!isalpha(word[0]))
            continue;
        if ((n = binsearch(word, keytab, NKEYS)) >= 0)
            keytab[n].count++;
    }
    for (n = 0; n < NKEYS; n++)
    {
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    }

    return 0;
}

int getword(char *word, int lim)
{
    int c;
    char *w = word;
    int prefix;
    while (isspace(c = getch()))
        ;

    prefix = getprefix(c);

    if (prefix != NOPREFIX)
    {
        c = getch();
    }

    if (c != EOF)
        *w++ = c;

    if (!isalpha(c))
    {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
    {
        *w = getch();
        if (*w == '_')
        {
            *w = ' ';
        }
        else if (*w == '"' && prefix == STRINGCONST)
        {
            break;
        }
        else if (!isalnum(*w))
        {
            if (prefix == STRINGCONST)
            {
                word[0] = '\0';
            }
            ungetch(*w);
            break;
        }
    }
    *w = '\0';

    return word[0];
}

int getprefix(char c)
{
    switch (c)
    {
    case '"':
        return STRINGCONST;
    case '/':
        if (getch() == '/')
            return COMMENT;
    case '#':
        return CONTROLLINE;
    default:
        return NOPREFIX;
    }

    return NOPREFIX;
}

int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) > 0)
            low = mid + 1;
        else if (cond < 0)
            high = mid - 1;
        else
            return mid;
    }

    return -1;
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