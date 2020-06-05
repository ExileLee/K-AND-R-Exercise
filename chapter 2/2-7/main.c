#include <stdio.h>

unsigned invert(unsigned x, int p, int n);
unsigned mask(unsigned x, int p, int n);

int main(void)
{
    unsigned x;
    int p, n;

    for(x = 0; x < 700; x += 49)
        for(n = 0; n < 8; n++)
            for(p = 0; p < 8; p++)
                printf("%x, %d, %d: %x\n", x, p, n, invert(x, p, n));
    return 0;
}
unsigned invert(unsigned x, int p, int n) {
    return (~(~0 << n) & (~x >> (p+1-n))) << p+1-n | mask(x, p, n);
}

unsigned mask(unsigned x, int p, int n)  {
    return (x & (~0 << p + 1)) | (x & ~(~0 << (p+1-n)));
}
