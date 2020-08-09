#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000
#define MAXFILES 10

typedef struct _input
{
    char *fileName;
    FILE *file;
} Input;

static int except = 0, number = 0;

void find(Input *, char *);

int main(int argc, char *argv[])
{
    Input file[MAXFILES];
    char c;
    int i;
    for (i = 1; i < argc && argv[i][0] == '-'; i++)
    {
        while ((c = *++argv[i]))
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

    int fileCount = argc - i - 1;

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

    for (int j = 0; i < argc - 1; i++, j++)
    {
        file[j].file = fopen(argv[i], "r");
        file[j].fileName = argv[i];
    }

    char *pattern = argv[argc - 1];

    for (i = 0; i < fileCount; i++)
    {
        find(&file[i], pattern);
    }

    return 0;
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
