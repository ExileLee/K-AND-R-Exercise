#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 200

int main(int argc, char *argv[])
{
    if (argc < 3)
        fprintf(stderr, "invalid input: must have two file, %s", *argv);

    void printYellow(), printBlue();
    char *fname1;
    char *fname2;

    FILE *f1 = fopen((fname1 = *++argv), "r");
    FILE *f2 = fopen((fname2 = *++argv), "r");

    char *line1 = (char *)malloc(sizeof(char) * MAXLEN);
    char *line2 = (char *)malloc(sizeof(char) * MAXLEN);

    do
    {
        line1 = fgets(line1, MAXLEN, f1);
        line2 = fgets(line2, MAXLEN, f2);
    } while ((line1 != NULL || line2 != NULL) && strcmp(line1, line2) == 0);

    if (line1 != NULL && line2 != NULL)
    {
        printYellow();
        printf("%s: %s%s: %s", fname1, line1, fname2, line2);
    }
    else
    {
        printBlue();
        printf("no diffrent!\n");
    }
    

    return 0;
}

void printYellow() 
{
  printf("\033[1;33m");
}

void printBlue()
{
    printf("[0;34m");
}