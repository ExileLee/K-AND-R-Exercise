/*
Author: Boyi, Lee
-----------------------
K&R Exercise 5-12:
Extend entab and detab to accept the shorthand entab -m +n 

to mean tab stops every n columns, starting at column m. 
Choose convenient (for the user) default behavior.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLENGTH 1000

int getLine(char *s, int maxlen);
void detab(char *line, char *output);
int stop = 4;

int main(int argc, char *argv[])
{
    char line[MAXLENGTH];
    char result[MAXLENGTH];

    int num, prefix, start;
    start = 0;
    while (--argc > 0)
    {
        prefix = (*++argv)[0];
        if (prefix != '-' && prefix != '+')
        {
            argc = -1;
            continue;
        }
        num = *++argv[0];
        if (isdigit(num))
        {
            switch (prefix)
            {
            case '+':
                stop = atoi(*argv);
                break;
            case '-':
                start = atoi(*argv);
                break;
            }
        }
        else
            argc = -1;

        stop += start;   
    }

    while (getLine(line, MAXLENGTH) > 0)
    {
        detab(line, result);
        printf("%s\n", result);
    }

    return 0;
}

int getLine(char *s, int maxlen)
{
    int c;
    char *sp = s;
    while (s - sp < maxlen && (c = getchar()) != '\n' && c != EOF)
        *s++ = c;
    if (*s == '\n')
        *s++ = c;
    *s = '\0';

    return s - sp;
}

void detab(char *line, char *output)
{
    int i, j, col;
    i = j = 0;
    col = 1;

    while (line[i])
    {
        if (line[i] != '\t')
        {
            col++;
            output[j++] = line[i++];
            continue;
        }

        if (col > stop)
            col = 1;

        while (line[++i] == '\t')
            ;
        int banks = stop - col;

        for (int b = 0; b <= banks; b++, col++)
            output[j++] = ' ';
    }

    output[j] = '\0';
}
