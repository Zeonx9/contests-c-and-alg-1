#define T

#ifdef T8
#include <stdio.h>

int main() {
    char stack[1001], c;
    int top = -1;
    while (1){
        scanf("%c", &c);
        if (c == '(' || c == '[' || c == '{')
            stack[++top] = c;
        else if (top >= 0 && (
                (c == ')' && stack[top] == '(') ||
                (c == ']' && stack[top] == '[') ||
                (c == '}' && stack[top] == '{')))
            --top;
        else
            break;
    }
    printf("%s\n", top == -1 ? "Yes" : "No");
}
#endif

#ifdef T7
#include <stdio.h>
int main() {
    int depth = 0;
    char c;
    while (1){
        scanf("%c", &c);
        if (c == '(')
            ++depth;
        else if (depth > 0 && c == ')')
            --depth;
        else
            break;
    }
    printf("%s\n", depth ? "No" : "Yes");
}
#endif

#ifdef T6
#include <stdio.h>
#include <malloc.h>

int main() {
    int size, *arr, *counter, min = -1000;
    scanf("%d", &size);
    arr = (int *) malloc(size * sizeof(int));
    counter = (int *) calloc(2001, sizeof(int));

    for (int i = 0; i < size; ++i){
        scanf("%d", arr + i);
        counter[arr[i] - min] += 1;
    }

    int popular = *arr;
    for (int *p = arr + 1; p < arr + size; ++p){
        if (counter[*p - min] > counter[popular - min])
            popular = *p;
    }
    printf("%d\n", popular);
    free(arr);
    free(counter);
    return 0;
}
#endif

#ifdef T5
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int main() {
    int size, *arr;
    scanf("%d", &size);
    arr = (int *) malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i)
        scanf("%d", arr + i);

    int i;
    scanf("%d", &i);
    while (i != -1){
        int hasEven = 0, t = abs(arr[i - 1]);
        if (!t) hasEven = 1;
        while (t > 0){
            int d = t % 10;
            hasEven = d % 2 ? hasEven : 1;
            t /= 10;
        }
        printf("%s\n",  arr[i - 1] % 3 == 0 && hasEven ? "Yes Yes" :
                        arr[i - 1] % 3 == 0 && !hasEven ? "Yes No" : "No No");
        scanf("%d", &i);
    }

    free(arr);
    return 0;
}
#endif

#ifdef T4
#include <stdio.h>
#include <malloc.h>

int main() {
    int size, *arr;
    scanf("%d", &size);
    arr = (int *) malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i)
        scanf("%d", arr + i);

    for (int *p = arr + size - 1; p >= arr; --p){
        int sum = 0, t = *p;
        while (t > 0){
            sum += t % 10;
            t /= 10;
        }
        printf("%d\n", sum);
    }
    free(arr);
    return 0;
}
#endif

#ifdef T3
#include <stdio.h>
#include <malloc.h>

int main() {
    int size, *arr;
    double mid = 0;
    scanf("%d", &size);
    arr = (int *) malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        scanf("%d", arr + i);
        mid += arr[i];
    }
    mid /= size;

    for (int *p = arr; p < arr + size; ++p)
        if (*p >= mid)
            printf("%d\n", *p);
    for (int *p = arr + size - 1; p >= arr; --p)
        if (*p < mid)
            printf("%d\n", *p);

    free(arr);
    return 0;
}
#endif

#ifdef T2
#include <stdio.h>

int main() {
    int n, min, max, cur;
    scanf("%d\n%d", &n,  &cur);
    min = max = cur;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &cur);
        min = min > cur ? cur : min;
        max = max < cur ? cur : max;
    }

    int sumMax = max / 10 + max % 10, sumMin = min / 10 + min % 10;
    printf("%d %d\n%s", sumMax, sumMin, sumMax == sumMin ? "Yes" : "No");
    return 0;
}
#endif

#ifdef T1
#include <stdio.h>
#include <malloc.h>

int main() {
    int size, *arr;
    scanf("%d", &size);
    arr = (int *) malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i)
        scanf("%d", arr + i);

    int i;
    scanf("%d", &i);
    while (i != -1){
        i -= 1;
        int l = 0, r = 0, cur = arr[i];
        for (int j = i + 1; j < size; ++j)
            if (arr[j] >= cur){
                ++r;
                cur = arr[j];
            }
        cur = arr[i];
        for (int j = i - 1; j >= 0; --j)
            if (arr[j] >= cur){
                ++l;
                cur = arr[j];
            }
        printf("%d %d\n", l, r);
        scanf("%d", &i);
    }
    free(arr);
    return 0;
}
#endif
