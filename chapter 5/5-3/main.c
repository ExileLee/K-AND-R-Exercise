#include <stdio.h>

char *strcat(char *s, char *t);

int main() {
    char s[] = "my chemical ";
    char t[] = "romance";
    char *result = strcat(s, t);
    printf("%s", result);
    return 0;
}

char *strcat(char *s, char *t)
{
    int sc, tc;
    char *tp = t;
    char *sp = s;
    sc = tc = 0;

    while (*s++)
        sc++;
    while (*t++)
        tc++;
    char alloc[tc+sc+1];
    char *cp = alloc;
    while (*sp != '\0')
        *cp++ = *sp++;
    while (*cp++ = *tp++)
        ;

    return &alloc;
}
