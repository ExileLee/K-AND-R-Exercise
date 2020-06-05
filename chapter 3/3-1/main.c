#include <stdio.h>

int binsearch(int x, int v[], int n);

int main() {
    int array[] = {1,2,3,4,5,6,7,8,9,10};

    printf("found at %d", binsearch(5, array, 10));

    return 0;
}

int binsearch(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    mid = (low + high) / 2;

    while (low <= high && x != v[mid]) {
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;

        mid = (low + high) / 2;
    }

    return low > high ? -1 : mid;
}
