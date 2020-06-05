#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define MAXVAL 100
#define BUFSIZE 100

#define NUMBER '0'
#define PRINT '?'
#define DUPLICATE '!'
#define SWAP '~'
#define CLEAR '<'

int getch(void);
void ungetch(int);
int getop(char s[]);
void push(double f);
double pop(void);
void showtop();
void duplicate();
void swap();
void clear();

int main(void)
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '*':
                push(pop() * pop());
                break;
            case '/':
                op2 = pop();
                push(pop() / op2);
                break;
            case '%':
                op2 = pop();
                push(fmod(pop(), op2));
                break;
            case PRINT:
                showtop();
                break;
            case DUPLICATE:
                duplicate();
                break;
            case SWAP:
                swap();
                break;
            case CLEAR:
                clear();
                break;
            case '\n':
                printf("%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %c", type);
                break;
        }
    }
}

int sp = 0;
double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return  0.0;
    }
}

void showtop() {
   if (sp > 0)
       printf("top element: %g\n", val[sp-1]);
   else
       printf("empty stack, nothing to print");
}

void duplicate() {
    int copy = pop();
    push(copy);
    push(copy);
}

void swap() {
    int first = pop();
    int second = pop();
    push(first);
    push(second);
}

void clear() {
    sp = 0;
}


int getLine(char s[], int maxlen) {
    int i, c;
    i = 0;

    while(--maxlen > 0 && (c = s[i]) != EOF && c != '\n') {
        s[i++] = c;
    }
    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';

    return i;
}

int getop(char s[])
{
    int i, c, next;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-')
        return c;
    i = 0;

    if (c == '-') {
        next = s[++i] = getch();
        if (!isdigit(next) && next != '.') {
            ungetch(next);
            return c;
        } else
            c = next;
    }
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
     s[i] = '\0';
     ungetch(c);
     return NUMBER;
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