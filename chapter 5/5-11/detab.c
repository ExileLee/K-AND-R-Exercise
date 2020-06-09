/*
Author: Boyi, Lee
-----------------------
K&R Exercise 5-11:
Modify the programs entab and detab (written as exercises in Chapter 1) to
accept a list of tab stops as arguments. Use the default tab settings 
if there are no arguments.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEFAULTSTOP 4
#define MAXSTOP 100
#define MAXLENGTH 1000

void input_to_tabs(char *[], int);
int getLine(char *s, int maxlen);
void detab(char *line, char *output);

int stops[MAXSTOP], stopcount;

int main(int argc, char *argv[])
{
    input_to_tabs(argv, argc);
    char line[MAXLENGTH];
    char result[MAXLENGTH];

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

    return s - sp;
}

void input_to_tabs(char *input[], int inputc)
{
    stopcount = 0;
    while (--inputc > 0)
    {
        ++input;
        int i;
        for (i = 0; isdigit((*input)[i]) && (*input)[i] != '\0'; i++)
            ;

        if ((*input)[i] == '\0')
        {
            stops[stopcount++] = atoi(input[0]);
        }
    }

    if (stopcount == 0)
    {
        stops[stopcount++] = DEFAULTSTOP;
    }
}

void detab(char *line, char *output)
{
    int i, j, col, stopi;
    i = j = stopi = 0;
    col = 1;
    int stop = stops[stopi];

    while (line[i])
    {
        if (line[i] != '\t')
        {
            col++;
            output[j++] = line[i++];
            continue;
        }

        if (col > stop)
        {
            if (stopi == stopcount - 1)
            {
                stop = DEFAULTSTOP;
                col = 1;
            }
            else
            {
                stop = stops[++stopi];
            }
        }

        while (line[++i] == '\t')
            ;
        int banks = stop - col;

        for (int b = 0; b < banks; b++, col++)
            output[j++] = ' ';
    }

    output[j] = '\0';
}
