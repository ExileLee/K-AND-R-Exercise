#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define BUFSIZE 1000
#define DEFAULTCOMPCOUNT 6

enum { COMMENT, CONTROLLINE, STRINGCONST, NOPREFIX };

int getch(void);
void ungetch(int);
int getword(char *word, int lim);
int getcompcount(char *argv);
int mystrcomp(char *, char *, int);
struct tnode *addtree(struct tnode *, char *, int compcount);
void printtree(struct tnode *);
struct tnode *talloc(void);

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

int main(int argc, char *argv[])
{
    int compcount = argc > 1 ? getcompcount(argv[1]) : DEFAULTCOMPCOUNT;
    struct tnode *root = NULL;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
    {
        if (isalpha(word[0]))
            root = addtree(root, word, compcount);
    }

    printf("result:\n");
    printtree(root);

    return 0;
}

int getcompcount(char *argv)
{
    char c;
    char *p = argv;
    while (isdigit((c = *p++)))
        ;

    return c == '\0' ? atoi(argv) : DEFAULTCOMPCOUNT;    
}

struct tnode *addtree(struct tnode *node, char *word, int compcount)
{
    int cond;

    if (node == NULL)
    {
        node = talloc();
        node->word = strdup(word);
        node->count = 1;
        node->left = node->right = NULL;
    }
    else if ((cond = mystrcomp(word, node->word, compcount)) == 0)
        node->count++;
    else if (cond < 0)
        node->left = addtree(node->left, word, compcount);
    else
        node->right = addtree(node->right, word, compcount);
    return node;
}

int mystrcomp(char *s, char *t, int compcount)
{


    for (; --compcount > 0 && *s == *t; s++, t++)
    {
        if (*s == '\0' || compcount < 1)
            return 0;
    }

    return *s - *t;
}

struct tnode *talloc()
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

void printtree(struct tnode *node)
{
    if (node == NULL) return;
    printtree(node->left);
    printf("%s\n", node->word);
    printtree(node->right);
}

int getword(char *word, int lim)
{
    int c;
    char *w = word;
    int prefix;
    int getprefix(char);

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