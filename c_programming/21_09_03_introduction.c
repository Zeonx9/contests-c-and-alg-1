#define T

#ifdef T1
//geometric progression
#include <stdio.h>
#include <math.h>

int main() {
    int b1, b3;
    scanf("%d%d", &b1, &b3);
    int b2 = (int) sqrt(b1 * b3);
    int q = b3 / b2;
    printf("%d %d\n", b2, q);
}
#endif

#ifdef T2
//task about sum of digits of 5-digit-number
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int d1 = n / 10000;
    int d2 = (n / 1000) % 10;
    int d3 = (n / 100) % 10;
    int d4 = (n / 10) % 10;
    int d5 = n % 10;
    printf("%d\n", d1 + d2 + d3 + d4 + d5);
}
#endif

#ifdef T3
//reverse 5-digit-number
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int d1 = n / 10000;
    int d2 = (n / 1000) % 10;
    int d3 = (n / 100) % 10;
    int d4 = (n / 10) % 10;
    int d5 = n % 10;
    printf("%d\n", d5 * 10000 + d4 * 1000 + d3 * 100 + d2 * 10 + d1);
}
#endif

#ifdef T4
//task time components to number
#include <stdio.h>

int main() {
    int h, m, s;
    scanf("%d%d%d", &h, &m, &s);
    int n = 3600 * h + 60 * m + s;
    printf("%d\n", n);
}
#endif

#ifdef T5
//time to format
#include <stdio.h>
int main() {
    int t;
    scanf("%d", &t);
    int h = t / 3600, m = (t % 3600) / 60, s = t % 60;
    printf("%02d:%02d:%02d\n", h, m, s);
}
#endif