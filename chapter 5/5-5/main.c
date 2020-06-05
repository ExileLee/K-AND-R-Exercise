#include <stdio.h>

void strncpy(char *s, char *t, int n);
void strncat(char *s, char *t, int n);
int strncmp(char *s, char *t, int n);
int strlen(char *s);

int main() {
    char s[100] = "boyi love ";
    char t[] = "hihi";

    printf("%s\n", s);
    printf("%i\n", strncmp(s, t, 3));
    strncpy(s, t, 4);
    printf("%s", s);
    return 0;
}

int strnlen(char *s)
{
    int i = 0;
    for (; *s != '\0'; s++, i++)
        ;

    return i;
}

void strncpy(char *s, char *t, int n)
{
    int i = 0;
    while (i++ < n && (*s++ = *t++))
        ;
}

int strncmp(char *s, char *t, int n)
{
    for (int i = 0; *s == *t; i++, s++, t++)
        if (i == n || !*s)
            return 0;

    return s-t;
}

void strncat(char *s, char *t, int n)
{
    while (*s)
        s++;

    for (int i = 0; i < n && (*s = *t) ; s++, t++, i++)
        ;
}