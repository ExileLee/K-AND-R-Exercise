#include <stdio.h>

void reverse(char s[]);

int main() {
    char s[] = "Hello, World!";
    reverse(s);
    printf("%s\n", s);
    return 0;
}

void reverse(char s[])
{
    int len;
    void dorev(char s[], int left, int right);

    for (len = 0; s[len] != '\0'; ++len)
        ;

    dorev(s, 0, len - 1);
}

void dorev(char s[], int left, int right)
{
    if (left >= right) return;

    char temp = s[left];
    s[left] = s[right];
    s[right] = temp;
    dorev(s, ++left, --right);
}