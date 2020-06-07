/*
K&R Exercise 5-10
Author: Boyi Lee
------------------------------------------------------------------------------------------
Question:
Write the program expr , which evaluates a reverse Polish expression from the command line, 
where each operator or operand is a separate argument. For example, expr 2 3 4 + *
evaluates 2 X (3 + 4).
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXSTACK 100
#define NUMBER 0

int getop(char *);
double pop();
void push(double);

int main(int argc, char *argv[])
{
    double op2;
    while (--argc > 0)
    {
        switch (getop(*++argv)){
        case NUMBER:
            push(atof(*argv));
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
            push(pop()/op2);
            break;    
        default:
            argc = -1;
            printf("Invalid operator: %s\n", *argv);
            break;
        }
    }
    
    printf("Result: %f\n", pop());

    return 1;
}

double stackstore[MAXSTACK];
double *stack = stackstore;

double pop()
{
    return *--stack;
}

void push(double item)
{
    *stack++ = item;
}

int getop(char *str)
{
    while (isspace(*str))
        str++;

    if (*str != '-' && !isdigit(*str) && *str != '.')
        return *str;
    if (*str == '-' || *str == '.')
        str++;
    while (isdigit(*str))
        str++;
    if (*str == '.')
        str++;
    while (isdigit(*str))
        str++;
    if (*str == '\0')
        return NUMBER;
    else
        return *str;                
}


