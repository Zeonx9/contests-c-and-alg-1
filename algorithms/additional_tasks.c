#define T

#ifdef Talg
#include <stdio.h>

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    int x = 0, y = k - 1, tmp;
    for (int i = 0; i < n - 1; ++i)
        tmp = x, x = y, y = (tmp + y) * (k - 1);

    printf("%d", x + y);
}
#endif
