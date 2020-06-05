#include <stdio.h>
int bitcount(unsigned  x);


int main() {

    for (int i = 1; i <= 10; ++i) {
        printf("number:%d, 1-bit: %d\n", i, bitcount(i));
    }

    return 0;
}

int bitcount(unsigned  x) {
    int b = 0;
    for (b = 0; x != 0 ; x &= (x-1))
        b++;

    return b;
}
