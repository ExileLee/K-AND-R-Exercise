#include <stdio.h>
#include <ctype.h>

int htoi(char s[]);

int main() {

    printf("%d\n", htoi("0x1F4"));
    return 0;
}

int htoi(char s[]) {
    int result = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        char c = tolower(s[i]);
        if (c == '0' || c == 'x')
            continue;
        if (isdigit(c)) {
            result = 16 * result + (c-'0');
        } else if(c >= 'a' && c <= 'f') {
            result = 16 * result + ((c-'a') + 10);
        } else {
            return 0;
        }
    }

    return result;
}