#include <stdio.h>
#include <limits.h>

int getMaxUintBits();
unsigned int rightrot(unsigned int x, int n);

int main()
{
    printf("%d\n", rightrot(213, 2));
    return 0;
}

int getMaxUintBits() {
    unsigned int max = UINT_MAX;
    int bits = 0;
    while (max > 0) {
        max = max/2;
        bits++;
    }

    return bits;
}

unsigned int rightrot(unsigned int x, int n) {
    return 0U | (x << (getMaxUintBits()-n)) | (x >> n);
}

