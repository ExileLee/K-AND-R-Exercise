#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000
#define MAXFILES 10
#define PATTERNARGCOUNT 1

typedef struct _input
{
    char *fileName;
    FILE *file;
} Input;

static int except = 0, number = 0;

void findAll(Input *[], int, char *);

int main(int argc, char *argv[])
{
    Input *files[MAXFILES];
    char c;
    int argIndex;
    for (argIndex = 1; argIndex < argc && argv[argIndex ][0] == '-'; argIndex ++)
    {
        while ((c = *++argv[argIndex]))
        {
            switch (c)
            {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                printf("find: illegal option %c\n", c);
                argc = 0;
                return 1;
            }
        }
    }

    int fileCount = argc - argIndex - PATTERNARGCOUNT;

    if (fileCount < 1)
    {
        printf("must have file input");
        return 1;
    }
    if (fileCount > MAXFILES)
    {
        printf("file count must lower than %i", MAXFILES);
        return 1;
    }

    for (int j = 0; argIndex  < argc - 1; argIndex ++, j++)
    {
        files[j]->file = fopen(argv[argIndex ], "r");
        files[j]->fileName = argv[argIndex];
    }

    char *pattern = argv[argc - 1];
    
    findAll(files, fileCount, pattern);

    return 0;
}

void findAll(Input *input[], int intputCount, char *pattern)
{
    void find(Input *, char *);
    for (int i = 0; i < intputCount; i++)
        find(input[i], pattern);
}

void find(Input *input, char *pattern)
{
    char line[MAXLINE];
    long lineNo = 0;
    int found = 0;
    printf("%s:\n", input->fileName);

    while (fgets(line, MAXLINE, input->file) != NULL)
    {
        lineNo++;
        if ((strstr(line, pattern) != NULL) != except)
        {
            if (number)
                printf("%ld. ", lineNo);
            printf("%s", line);    
            if (line[strlen(line) - 1] != '\n')
                printf("\n");
            found++;
        }
    }

    if (found < 1)
        printf("no match line.\n");    
}
