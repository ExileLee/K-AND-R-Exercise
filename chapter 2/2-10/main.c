#include <stdio.h>

void lower(char s[]);

int main() {
    char message[] = "Hello, World\n";
    lower(message);
    printf(message);
    return 0;
}

void lower(char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        s[i] = s[i] >= 'A' && s[i] <= 'Z' ? s[i] + 'a' - 'A' : s[i];
        i++;
    }
}