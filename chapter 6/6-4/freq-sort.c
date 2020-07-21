#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define BUFSIZE 1000

int getword(char *word, int lim);
struct tnode *add_wordtree(struct tnode *, char *);
struct tnode *store_freqtree(struct tnode *node, struct tnode *freqnode);
void printtree(struct tnode *);
struct tnode *talloc(void);

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

int main(int argc, char const *argv[])
{
    struct tnode *wroot = NULL;
    struct tnode *freqroot = NULL;

    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
    {
        if (isalpha(word[0]))
            wroot = add_wordtree(wroot, word);
    }

    freqroot = store_freqtree(wroot, freqroot);
    printtree(freqroot);

    return 0;
}

struct tnode *add_wordtree(struct tnode *node, char *word)
{
    int cond;

    if (node == NULL)
    {
        node = talloc();
        node->word = strdup(word);
        node->count = 1;
        node->left = node->right = NULL;
    }
    else if ((cond = strcmp(word, node->word)) == 0)
        node->count++;
    else if (cond < 0)
        node->left = add_wordtree(node->left, word);
    else
        node->right = add_wordtree(node->right, word);
    return node;
}

struct tnode *add_freqtree(struct tnode *node, char *word, int count)
{
    if (node == NULL)
    {
        node = talloc();
        node->word = strdup(word);
        node->count = count;
        node->left = node->right = NULL;
    }
    else if (count < node->count)
        node->left = add_freqtree(node->left, word, count);
    else
        node->right = add_freqtree(node->right, word, count);

    return node;
}

struct tnode *store_freqtree(struct tnode *node, struct tnode *freqnode)
{
    if (node == NULL) return NULL;

    freqnode = add_freqtree(freqnode, node->word, node->count);
    store_freqtree(node->left, freqnode);
    store_freqtree(node->right, freqnode);

    return freqnode;
}

struct tnode *talloc()
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

void printtree(struct tnode *node)
{
    if (node == NULL) return;

    printtree(node->right);
    printf("%s: %i\n", node->word, node->count);
    printtree(node->left);
}

int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;

    if (c != EOF)
        *w++ = c;

    if (!isalpha(c))
    {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++)
    {
        if (!isalnum((*w = getch())))
        {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';

    return word[0];
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