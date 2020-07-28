#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define UPPER "upper"
#define LOWER "lower"

void convert(int (*)(int));

int main(int argc, char *argv[])
{
    int fileNameIndex;
    char *fileName;

    for (int slashIndex = 0; (*argv)[slashIndex] != '\0'; slashIndex++)
    {
        if ((*argv)[slashIndex] == '/')
            fileNameIndex = slashIndex + 1;
    }    

    char *filename = *argv + fileNameIndex;

    if (strcmp(filename, UPPER) == 0)
         convert(&toupper);
    else if (strcmp(filename, LOWER) == 0)
        convert(&tolower);
    else
        printf("error: invalid program name");
    
    return 0;
}

void convert(int (*convertCh)(int))
{
    int c;
    while ((c = getchar()) != EOF)
        putchar((*convertCh)(c));
}
