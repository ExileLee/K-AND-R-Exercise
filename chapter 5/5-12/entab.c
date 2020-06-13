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
void entab(char *line, char *output);

int stop = 0;

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
        entab(line, result);
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

void entab(char *line, char *output)
{
    int i, j, k, col;
    i = j = 0;
    col = 1;

    while (line[i])
    {
        if (line[i] != ' ')
        {
            col++;
            output[j++] = line[i++];
            continue;
        }

        int tabc, space;

        for (tabc = 0, space = 0; line[i] == ' '; i++, col++)
        {
            if (col > stop)
                col = 1;
            if (col == stop)
            {
                tabc++;
                space = 0;
            }
            else
                space++;
        }

        for (k = 0; k < tabc; k++)
            output[j++] = '\t';

        for (k = 0; k < space; k++)
            output[j++] = ' ';
    }

    output[j] = '\0';
}
