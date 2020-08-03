#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define MAXVAL 100
#define BUFSIZE 100
#define MAXLEN 100

#define NUMBER '0'
#define INVALID '!'

int getch(void);
void ungetch(int);
int getop(double *number);
void push(double f);
double pop(void);

int main(void)
{
    int type;
    double op2;
    double tmpOp;

    while ((type = getop(&tmpOp)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(tmpOp);
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
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void showtop()
{
    if (sp > 0)
        printf("top element: %g\n", val[sp - 1]);
    else
        printf("empty stack, nothing to print");
}

char line[MAXLEN];

int getop(double *number)
{
    int i;
    char c;
    i = 0;

    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '\n')
        return c;
    for (; !isspace(c); c = getch())
        line[i++] = c;
    line[i] = '\0';    
    ungetch(c);
    if (sscanf(line, "%lf", number) == 1)
        return NUMBER;
    else if (sscanf(line, "%c", &c) == 1)
        return c;    
    else
        return INVALID;
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