#include <stdio.h>

int any(char s1[], char s2[]);

int main() {
    printf("%d", any("nirvana", "va"));
    return 0;
}

int any(char s1[], char s2[]) {
    int i;

    for (i = 0; s1[i] != '\0' ; ++i) {
        int k = 0;
        while (s1[i] != s2[k] && s2[k] != '\0')
            k++;

        if (s2[k] != '\0') {
            return i;
        }
    }

    return -1;
}