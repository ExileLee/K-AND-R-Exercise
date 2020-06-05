#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main() {
    char s1[] = "my chemical romance";
    squeeze(s1, "abc");
    printf("%s", s1);
    return 0;
}


void squeeze(char s1[], char s2[]) {
    int i,j;

    for (i = j = 0; s1[i] != '\0'; ++i) {
        int k = 0;
        while (s1[i] != s2[k] && s2[k] != '\0')
            k++;

        if (s2[k] == '\0') {
            s1[j++] = s1[i];
        }
    }

    s1[j] = '\0';
}
