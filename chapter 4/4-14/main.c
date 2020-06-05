#include <stdio.h>

#ifndef HDR
#define HDR "hihihi"
#endif

#define swap(t,x,y) do {t temp = x;x = y;y=temp;}while(0);

int main() {
    int x,y;
    x = 10, y = 20;
    swap(int, x, y);
    printf("x=%i,y=%i", x, y);
    printf("%s", HDR);
    return 0;
}
