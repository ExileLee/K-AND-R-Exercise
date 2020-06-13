/*
Author: Boyi, Lee
-----------------------
K&R Exercise 5-13:
Write the program tail, which prints the last n lines of its input. By default, 
n is 10, say, but it can be changed by an optional argument, so that

  tail -n

prints the last n lines. The program should behave rationally no matter
how unreasonable the input or the value of n. Write the program so it makes
the best use of available storage; lines should be stored as in the sorting
program of Section 5.6, not in a two-dimensional array of fixed size.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLENGTH 1000
#define MAXLINE 1000

int getLine(char *[], int);
char *alloc(int);

int lastn = 2;

int main(int argc, char *argv[])
{
    char *lines[MAXLINE];
    int count = 0;

    while (--argc > 0)
    {
        char prefix = (*++argv)[0];
        
        if (prefix == '-' && isdigit((*argv)[1]))
            lastn = atoi(++*argv);
        else
           argc = -1;
    }

    for (count = 0; getLine(lines, count) > 0; count++)
        ;

    for (int i = count-lastn; i < count; i++)
        printf("no %i. %s", i+1, lines[i]);
        
    return 0;
}

int getLine(char *lines[], int line)
{
    int i = 0;
    char *p;
    char buffer[MAXLENGTH];
    int maxlen = MAXLENGTH;

    while (--maxlen > 0 && (buffer[i] = getchar()) != '\n' && buffer[i] != EOF)
        i++;
    if (buffer[i] == '\n')
        buffer[i++] = '\n';

    buffer[i] = '\0';
    p = alloc(i+1);
    strcpy(p, buffer);
    lines[line] = p;

    return i;
}


#define ALLOCSIZE 1000

char allocbuffer[ALLOCSIZE];
char *allocp = allocbuffer;

char *alloc(int n)
{
    if (allocbuffer + ALLOCSIZE - allocp >=n)
    {
        allocp += n;
        return allocp - n;
    }
    else
        return NULL;
}