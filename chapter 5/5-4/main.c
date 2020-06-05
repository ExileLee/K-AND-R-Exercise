#include <stdio.h>

int strend(char *s, char *t);
int strcmp(char *s, char *t);
int strlen(char *s);

int main() {
    printf("%i\n", strend("world world hello world1world", "world"));

    return 0;
}

int strlen(char *s)
{
    int len = 0;
    while (*s++ != '\0')
        len++;

    return len;
}

int strcmp(char *s, char *t)
{
    for (; *s++ == *t++; t++, s++)
        if (*s == '\0')
            return 0;

    return s - t;
}

int strend(char *s, char *t)
{
    int slen = strlen(s);
    int tlen = strlen(t);

    s += slen - tlen;

    if (slen < tlen)
        return 0;

    return strcmp(s, t) == 0;
}