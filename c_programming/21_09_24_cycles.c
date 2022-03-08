#define A

#ifdef A10
#include <stdio.h>

int main() {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    if ((a == b && a > 0) || (c == b && c > 0) || (a == c && a > 0)) {
        printf("Yes");
    }else {
        printf("No");
    }

}
#endif

#ifdef A9
#include <stdio.h>

int main() {
    int a, b;
    char o, o2;
    scanf("%d\n%c\n%d\n%c", &a, &o, &b, &o2);
    while(1){
        switch (o) {
            case '+': {a += b;break;}
            case '-': {a -= b;break;}
            case '*': {a *= b;break;}
            case '/': {a /= b;break;}
            case '%': {a %= b;break;}
            default:
        }
        o = o2;
        if (o == '=') break;
        scanf("%d\n%c", &b, &o2);
    }
    printf("%d", a);

}
#endif

#ifdef A8
#include <stdio.h>

int main() {
    int d, s, f = 0;
    scanf("%d", &d);
    while(d != -1) {
        s += d;
        if (d % 2 == 0) f = 1;
        if (f && s % 3 == 0) {
            printf("Stop\n");
            return 0;
        } else {
            printf("No\n");
        }
        scanf("%d", &d);
    }

}
#endif

#ifdef A7
#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int c = (int)sqrt(i*i + j*j);
            if (c*c == i*i + j*j && c <= n) {
                printf("%d %d %d\n", i, j, c);
            }
        }
    }
}
#endif

#ifdef A6
#include <stdio.h>

int main() {
    int a, b, k;
    scanf("%d%d\n%d", &a, &b, &k);
    while(k > 0) {
        if (k % b == 0 && a >= k / b)
            a -= k / b;
        else if (k % a == 0 && b >= k / a)
            b -= k / a;

        if (a == 0 || b == 0) {
            printf("Chocolate is over\n");
            return 0;
        } else printf("%d %d\n", a, b);
        scanf("%d", &k);
    }
    printf("You are full\n");
}
#endif

#ifdef A5
#include <stdio.h>
#include <math.h>

int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    int len = a > b ? (int)log10(a) : (int)log10(b);
    for (int i = len; i >= 0; --i) {
        if ((a / (int)pow(10, i)) % 10 != (b / (int)pow(10, len - i)) % 10){
            printf("No\n");
            return 0;
        }
    }
    printf("Yes\n");
}
#endif

#ifdef A4
#include <stdio.h>
#include <string.h>

int main() {
    char n[11], max = '0';
    scanf("%s", n);
    for (int i = 0; i < strlen(n) ; ++i) {
        if (n[i] > max) max = n[i];
    }
    printf("%c", max);
    return 0;
}
#endif

#ifdef A3
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i; ++j)
            printf("*");
        printf("\n");
    }

    return 0;
}
#endif

#ifdef A2
#include <stdio.h>
#include <math.h>
int is_prime(int n) {
    int root = (int)sqrt(n);
    for (int i = 2; i <= root; ++i)
        if (n % i == 0)
            return 0;
    return 1;
}

int main() {
    int n, count = 0;
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i) if (is_prime(i)) ++count;
    printf("%d\n", count);
    return 0;
}
#endif

#ifdef A1
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int a;
        scanf("%d", &a);
        printf("%s\n", a % 3 == 0 ? "Yes" : "No");
    }
    return 0;
}
#endif

