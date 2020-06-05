#include <stdio.h>

void escape(char s[], char t[]);
void reEscape(char s[], char t[]);

int main() {
    char s[1000];
    char t[] = "Hello \t World\n";
    escape(s, t);
    reEscape(t, s);
    printf("Escape: %s\n", s);
    printf("Revert Escape: %s", t);
    return 0;
}

void escape(char s[], char t[]) {
    int ti, si;
    si = ti = 0;
    while (t[ti] != '\0') {
        switch (t[ti]) {
            case '\t':
                s[si++] = '\\';
                s[si++] = 't';
                break;
            case '\n':
                s[si++] = '\\';
                s[si++] = 'n';
                break;
            default:
                s[si++] = t[ti];
        }
        ti++;
    }

    s[si] = '\0';
}

void reEscape(char s[], char t[]) {
    int ti, si;
    si = ti = 0;
    while (t[ti] != '\0') {
        switch (t[ti]) {
            case '\\':
                switch (t[++ti]) {
                    case 't':
                        s[si] = '\t';
                        break;
                    case 'n':
                        s[si] = '\n';
                        break;
                    default:
                        s[si++] = '\\';
                        s[si] = t[ti];
                        break;
                }
                break;
            default:
                s[si] = t[ti];
        }
        si++;
        ti++;
    }
    s[si] = '\0';
}