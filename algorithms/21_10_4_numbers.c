#define T

#ifdef TA
unsigned long long fast_pow(unsigned long long r, unsigned long long c, unsigned long long m) {
    if (c == 1) return r % m;
    unsigned long long z = fast_pow(r, c / 2, m);
    z *= z;
    if (c % 2 != 0){
        z *= r;
    }
    return z % m;
}

#include <stdio.h>

int main() {
    unsigned long long n,
            mrf = 0, mrt1 = 0, mrt2 = 0,
            ft = 0, ff = 0;
    scanf("%llu", &n);


    unsigned long long s = 0, d = n - 1;  // n - 1 = 2^s * d
    while (d % 2 == 0) { d /= 2; ++s; }

    for (unsigned long long a = 1; a < n; ++a) {

        if (fast_pow(a, n - 1, n) == 1){
            ++ft;
        }else{
            ++ff;
        }

        unsigned long long r = fast_pow(a, d, n); // r = a^d % n
        if (r == 1){
            ++mrt1;
            continue;
        }
        if (r == n - 1){
            ++mrt2;
            continue;
        }
        char f = 1;
        for (unsigned long long r = 1; r < s; ++r) {
            r = fast_pow(r, 2, n);
            if (r == n - 1){
                ++mrt2;
                f = 0;
                break;
            }
        }
        if (f){
            ++mrf;
        }
    }
    printf("Miller-Rabin test: %s %llu %llu %llu\n", mrf ? "False" : "True", mrf, mrt1, mrt2);
    printf("Fermat test: %s %llu %llu\n", ff ? "False" : "True", ff, ft);
}
#endif

#ifdef TB
#include <stdio.h>
#include <malloc.h>

int main() {
    int s, f;
    scanf("%d%d", &s, &f);
    printf("Start and finish: %d %d\n", s, f);

    char *arr = (char *) malloc(sizeof(char) * (f + 1));
    for (int i = 0; i <= f; ++i) arr[i] = 1;
    arr[0] = 0; arr[1] = 0;

    char flag1;
    for (int i = 2, k = 1; i * i <= f; ++i) {
        if (arr[i]) {
            flag1 = 0;
            for (int j = i * i; j <= f; j += i)
                if (j >= s && arr[j] == 1){
                    flag1 = 1;
                    break;
                }
            if(flag1){
                printf("Iteration : %d\n", k);
                for (int j = i * i; j <= f; j += i) {
                    if (j >= s && arr[j] == 1){
                        printf("%d ", j);
                    }
                    arr[j] = 0;
                }
                printf("\n");
            }
            ++k;
        }
    }
    char flag2 = 0;
    for (int i = s; i <= f; ++i)
        if (arr[i]) {
            flag2 = 1;
            break;
        }
    printf("Primes :\n");
    if (flag2) {
        for (int i = s; i <= f; ++i){
            if (arr[i]){
                printf( "%d ", i);
            }
        }
    } else {
        printf("No primes\n");
    }
    return 0;
}
#endif

#ifdef TC
#include <stdio.h>

#define BASE 1000000000
#define SIZE 12

typedef unsigned long long large;
typedef struct {
    large a[SIZE];
} Num;
int last(Num n){
    int i = SIZE;
    while (!n.a[--i]);
    return i;
}

Num num(large n){
    Num r;
    for (int i = 0; i < SIZE; ++i){
        r.a[i] = n % BASE;
        n /= BASE;
    }
    return r;
}
large tollu(Num n){
    large r = 0;
    for (int i = SIZE - 1; i >= 0; --i){
        r *= BASE;
        r += n.a[i];
    }
    return r;
}

int cmp(Num r, Num c){
    int lx = last(r), ly = last(c);
    if(lx > ly) return 1;
    if (lx < ly) return -1;
    for (int i = lx; i >= 0; --i){
        if(r.a[i] > c.a[i]) return 1;
        if(r.a[i] < c.a[i]) return -1;
    }
    return 0;
}
Num add(Num r, large c){
    Num r = r;
    int i = 0;
    while (c){
        large cur = r.a[i] + c;
        r.a[i] = cur % BASE;
        c = cur / BASE;
    }
    return r;
}
Num sub(Num r, Num c){
    Num r = r;
    large take = 0;
    for (int i = 0; i < SIZE; ++i){
        r.a[i] -= take;
        if (r.a[i] < c.a[i]){
            r.a[i] += BASE;
            take = 1;
        } else take = 0;
        r.a[i] -= c.a[i];
    }
    return r;
}
Num mul(Num r, Num c){
    Num r = num(0);
    for (int i = 0; i < SIZE / 2; ++i){
        large over = 0;
        for(int j = 0; j < SIZE / 2 || over; ++j){
            large cur = r.a[i] * c.a[j] + r.a[i + j] + over;
            r.a[i + j] = cur % BASE;
            over = cur / BASE;
        }
    }
    return r;
}
Num shm(Num r, large c){
    Num r = num(0);
    large over = 0;
    for (int i = 0; i < SIZE; ++i){
        large cur = r.a[i] * c + over;
        r.a[i] = cur % BASE;
        over = cur / BASE;
    }
    return r;
}
Num div(Num r, large c){
    Num r = num(0);
    large over = 0;
    for (int i = SIZE - 1; i >= 0; --i){
        large cur = r.a[i] + over * BASE;
        r.a[i] = cur / c;
        over = cur % c;
    }
    return r;
}
Num mod(Num r, Num m) {
    if (cmp(r, m) < 0)
        return r;

    Num r = shm(mod(div(r, 2), m), 2);
    if (r.a[0] % 2)
        r = add(r, 1);

    if (cmp(r, m) > 0)
        r = sub(r, m);
    return r;
}

Num fast_pow(Num r, large c, Num m) {
    if (c == 1) return mod(r, m);
    Num z = fast_pow(r, c / 2, m);
    z = mul(z, z);
    if (c % 2){
        z = mul(z, r);
    }
    return mod(z, m);
}

large gcd_extend(large a,  large b, long long *r, long long *c) {
    if (a == 0) {
        *r = 0;
        *c = 1;
        return b;
    }
    long long _x, _y;
    large g;
    g = gcd_extend(b % a, a, &_x, &_y);
    *r = _y - (long long) (b / a) * _x;
    *c = _x;
    return g;
}

int main() {
    const int MSG_LEN = 6;
    large p, q, e, d;
    char input[MSG_LEN + 1];
    for (char *c = input; c <= input + MSG_LEN; ++c) *c = 0;
    scanf("%llu%llu%llu", &p, &q, &e); // NOLINT(cert-err34-c)
    scanf("%s", input);

    long long r = 0, c = 0;
    large   n = p * q,
            phi = (p - 1) * (q - 1);
    while (gcd_extend(e, phi, &r, &c) != 1)
        ++e;
    while ((r += (long long)phi) < 0);
    d = r % phi;
    printf("Private: %llu %llu\n", d, n);
    printf("Public: %llu %llu\n", e, n);

    printf("Initial bytes: ");
    large value = 0, cypher;
    for (char *c = input; c < input + MSG_LEN; ++c)
        if (*c){
            value = (value << 8) + *c;
            printf("%d ", *c);
        }
    printf("\n");

    cypher = tollu(fast_pow(num(value), e, num(n)));
    unsigned char bytes[MSG_LEN], *c;
    for (c = bytes; cypher > 0; ++c) {
        *c = (unsigned char)(cypher % 256);
        cypher >>= 8;
    }
    printf("Encrypted bytes: ");
    for (--c; c >= bytes; --c)
        printf("%d ", *c);
    printf("\n");
}
#endif
