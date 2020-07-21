/******************************************************
   K&R 1-22
   ---------------------------------------------------

   Write a program to "fold" long input lines into two or
   more shorter lines after the last non-blank character
   that occurs before the n-th column of input. Make sure
   your program does something intelligent with very long
   lines, and if there are no blanks or tabs before
   the specified column.

   Author: Boyi Lee
   email: exile1030@gmail.com

******************************************************/

#include <stdio.h>

#define MAXLEN 1000
#define COLUMNLEN 10

int getLine(char s[]);

int main() {

    char line[MAXLEN];

    while (getLine(line) > 0) {
        printf("%s", line);
    }

    return 0;
}

int getLine(char s[]) {
    int i, c, columns;

    i = skipBkank = columns = 0;
    while (i < MAXLEN - 1 && (c = getchar()) != EOF && c != '\n' && columns <= COLUMNLEN) {
       if ((c != ' ' && c != '\t') || columns > 0) {
           columns++;
           s[i++] = c;
       }
    }

    if (c == '\n' || columns >= COLUMNLEN) {
        s[i] = '\n';
        i++;
    }

    s[i] = '\0';

    return i;
}