#define T

#ifdef T10
#include <stdio.h>

int main() {
    double n, m;
    char op;
    scanf("%lf%c%lf", &n, &op, &m);
    if (op == '-') m = -m;
    printf("%.2f", n + m);
    return 0;
}
#endif

#ifdef T9
#include <stdio.h>

int main() {
    double h, d, n;
    scanf("%lf%lf", &h, &d);
    n = h * 100 - d * 100;
    if (n < 10) printf("0");
    else printf("%.2lf", n / 100);
    return 0;
}
#endif

#ifdef T8
#include <stdio.h>

int main() {
    int n;
    double t, p, c;
    scanf("%lf%lf%d", &t, &p, &n);
    c = t * p;
    if ((n == 6 || n == 7) && t >= 10) c *= 0.8;
    printf("%.2lf", c);
    return 0;
}
#endif

#ifdef T7
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    switch (n) {
        case 1:
            printf("Monday");
            break;
        case 2:
            printf("Tuesday");
            break;
        case 3:
            printf("Wednesday");
            break;
        case 4:
            printf("Thursday");
            break;
        case 5:
            printf("Friday");
            break;
        case 6:
            printf("Saturday");
            break;
        case 7:
            printf("Sunday");
            break;
        default:
            printf("Wrong day number");
    }
    return 0;
}
#endif

#ifdef T6
#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;
    double s, p;
    scanf("%lf%lf%lf", &a, &b, &c);
    if ((a < b + c) && (b < a + c) && (c < a + b)) {
        p = (a + b + c) / 2.;
        s = sqrt(p * (p - a) * (p - b) * (p - c));
        printf("%.2lf", s);
    } else printf("0");

}
#endif

#ifdef T5
#include <stdio.h>
#include <math.h>

int main() {
    int s, r;
    scanf("%d%d", &s, &r);
    double  ca = (int)(3.14 * r * r * 100) / 100.,
            sa = (int)(s * s * 100) / 100.,
            sd = (int)(s * sqrt(2.) * 100) / 100.;
    printf("%.2lf %.2lf\n", sa, ca);
    printf("%s\n", sa > ca ? "Square is bigger" : sa == ca ? "Equal" : "Circle is bigger");
    printf("%s\n", sd <= 2 * r ? "Square in circle" : 2 * r <= s ? "Circle in square" : "Impossible");
    return 0;
}
#endif

#ifdef T4
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, k = 0;
    scanf("%d", &n);
    n = abs(n);
    for (int i = 100000; i > 0; i /= 10)
        if (((n / i) % 10) % 2 != 0) k++;
    printf("%d", k);
    return 0;
}
#endif

#ifdef T3
#include <stdio.h>

int main() {
    int n, f;
    scanf("%d", &n);
    f = (n / 100000 == n % 10 && (n / 10000) % 10 == (n / 10) % 10 && (n / 1000) % 10 == (n / 100) % 10) ? 1 : 0;
    printf("%s", f? "Palindrom" : "Non palindrom");
    return 0;
}
#endif

#ifdef T2
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int ls = n / 100000 + (n / 10000) % 10 + (n / 1000) % 10,
            rs = (n / 100) % 10 + (n / 10) % 10 + n % 10;
    printf("%s", ls == rs ? "Happy" : "Unhappy");
    return 0;
}
#endif

#ifdef T1
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    printf("%s\n", (n % 4 == 0 && n % 100 != 0) || (n % 400 == 0) ? "Yes" : "No");
    return 0;
}
#endif

