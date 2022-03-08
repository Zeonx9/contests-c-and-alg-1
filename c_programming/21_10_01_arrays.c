#define T

#ifdef T7
#include <stdio.h>
#define SIZE 100000

int main() {
    int stack[SIZE];
    int maxim[SIZE];
    int minim[SIZE];
    int top = -1;
    int cmd, val;
    scanf("%d", &cmd);
    while (cmd != 5){
        switch (cmd) {
            case 0: {
                scanf("%d", &val);
                if (top == SIZE - 1)
                    printf("Overflow\n");
                else {
                    stack[++top] = val;
                    if (top == 0) {
                        maxim[top] = val;
                        minim[top] = val;
                    }else {
                        maxim[top] = val > maxim[top - 1] ? val : maxim[top - 1];
                        minim[top] = val < minim[top - 1] ? val : minim[top - 1];
                    }
                }
                break;
            }
            case 1: {
                if (top < 0)
                    printf("Underflow\n");
                else {
                    maxim[top] = 0;
                    minim[top] = 0;
                    stack[top--] = 0;
                }
                break;
            }
            case 2: {
                if (top < 0)
                    printf("Stack is empty\n");
                else
                    printf("%d\n", stack[top]);
                break;
            }
            case 3: {
                if (top < 0)
                    printf("Stack is empty\n");
                else
                    printf("%d\n", maxim[top]);
                break;
            }
            case 4: {
                if (top < 0)
                    printf("Stack is empty\n");
                else
                    printf("%d\n", minim[top]);
                break;
            }
            default: return -3;
        }
        scanf("%d", &cmd);
    }
}
#endif

#ifdef T6
#include <stdio.h>
int main() {
    int n, s;
    scanf("%d\n%d", &n, &s);
    double arr[n];
    for (int i = 0; i < n; ++i)
        scanf("%lf", arr + i);

    for (int i = n - (s % n); i < 2*n - (s % n); ++i)
        printf("%.2lf\n", arr[i % n]);
    return 0;
}
#endif

#ifdef T5
#include <stdio.h>
int main() {
    int n, sum = 0;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; ++i){
        scanf("%d", arr + i);
        sum += arr[i];
    }
    double mid = (double)sum / n;

    for (int *p = arr; p - arr < n; ++p)
        printf("%.2lf\n", *p - mid);
    return 0;
}
#endif

#ifdef T4
#include <stdio.h>
int main() {
    int n, count = 0;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; ++i)
        scanf("%d", arr + i);

    for (int i = 1; i < n - 1; ++i)
        if (arr[i] < arr[i - 1] && arr[i] < arr[i + 1])
            ++count;
    if (arr[0] < arr[1] && arr[0] < arr[n - 1]) ++count;
    if (arr[n - 1] < arr[n - 2] && arr[n - 1] < arr[0]) ++count;
    printf("%d\n", count);
    return 0;
}
#endif

#ifdef T3
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, k;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; ++i)
        scanf("%d", arr + i);
    scanf("%d", &k);
    if (k < 0) k *= -1;

    int r = 0;
    for (int *p = arr + 1; p - arr < n; ++p)
        if (abs(k - abs(*p)) < abs(k - abs(arr[r]))) {
            r = (int)(p - arr);
        }
    printf("%d\n", r + 1);
    return 0;
}
#endif

#ifdef T2
#include <stdio.h>
int find(int * arr, const int * end, int val){
    for (int *p = arr; p < end; ++p)
        if (*p == val)
            return (int)(p - arr);
    return -1;
}

int main() {
    int n, m, k = 0, count = 0;
    scanf("%d", &n);
    int arr1[n];
    for (int i = 0; i < n; ++i)
        scanf("%d", arr1 + i);

    scanf("%d", &m);
    int arr2[m];
    for (int i = 0; i < m; ++i)
        scanf("%d", arr2 + i);

    for (int *p1 = arr1; p1 - arr1 < n; ++p1)
        if (find(arr2, arr2 + m, *p1) >= 0)
            ++k;

    int intersect[k];
    for (int *p1 = arr1, *i = intersect; p1 - arr1 < n; ++p1)
        if (find(arr2, arr2 + m, *p1) >= 0 && find(intersect, i + 1, *p1) < 0){
            *i++ = *p1;
            ++count;
        }


    printf("%d\n", count);
    for (int *p = intersect; p - intersect < count; ++p)
        printf("%d\n", *p);
    return 0;
}
#endif

#ifdef T1
#include <stdio.h>
int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; ++i)
        scanf("%d", arr + i);

    for (int *p = arr + n - 1; p >= arr; --p)
        printf("%d\n", *p * *p);
    return 0;
}
#endif

