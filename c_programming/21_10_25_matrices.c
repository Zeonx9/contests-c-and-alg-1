#define T

#ifdef T5
#include <stdio.h>
int main() {
    int n, m, count = 0;
    scanf("%d%d", &n, &m);
    int a[n][m];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%d", a[i] + j);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            int l = j ? j - 1 : m - 1, r = (j + 1) % m, u = i ? i - 1 : n - 1, d = (i + 1) % n;
            if (a[i][j] < a[u][l] && a[i][j] < a[u][j] && a[i][j] < a[u][r] && a[i][j] < a[i][l] &&
                a[i][j] < a[d][l] && a[i][j] < a[d][j] && a[i][j] < a[d][r] && a[i][j] < a[i][r]) {
                ++count;
                printf("%d %d\n", i + 1, j + 1);
            }
        }
    printf("%d\n", count);
}
#endif

#ifdef T4
#include <stdio.h>
int main() {
    int n, m, x1, y1, x2, y2, sum = 0;
    scanf("%d%d%d%d%d%d", &n, &m, &x1, &y1, &x2, &y2);
    int matix[n * m];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            scanf("%d", matix + m * i + j);
            if (x1 - 1 <= i && i < x2 && y1 - 1 <= j && j < y2)
                sum += matix[m * i + j];
        }

    printf("%d\n", sum);
}
#endif

#ifdef T3
#include <stdio.h>
void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void swapRows(int matr[], int r1, int r2, int m){
    for (int i = 0; i < m; ++i)
        swap(matr + r1 * m + i, matr + r2 * m + i);
}

int main() {
    int n;
    scanf("%d", &n);
    int matrix[n * n], rowOfZero[n], colOfZero[n];
    for (int i = 0; i < n * n; ++i) {
        scanf("%d", matrix + i);
        if (!matrix[i]) {
            rowOfZero[i % n] = i / n;
            colOfZero[i / n] = i % n;
        }
    }

    for (int i = 0; i < n; ++i){
        if (i != rowOfZero[i]) {
            swapRows(matrix, i, rowOfZero[i], n);
            int c = colOfZero[i], r = rowOfZero[i];
            rowOfZero[c] = r;
            colOfZero[r] = c;
        }
    }

    for (int i = 0; i < n * n; ++i) {
        printf("%d ", matrix[i]);
        if (!((i + 1) % n))
            printf("\n");
    }
}
#endif

#ifdef T2
#include <stdio.h>
void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void swapCols(int matr[], int c1, int c2, int n, int m){
    for (int i = 0; i < n; ++i)
        swap(matr + i * m + c1, matr + i * m + c2);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int matix[n * m], columnSum[m];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            scanf("%d", matix + m * i + j);
            if (!i)
                columnSum[j] = matix[j];
            else
                columnSum[j] += matix[m * i + j];
        }

    int minJ = 0, maxJ = 0;
    for (int j = 0; j < m; ++j){
        printf("%d ", columnSum[j]);
        minJ = columnSum[minJ] > columnSum[j] ? j : minJ;
        maxJ = columnSum[maxJ] < columnSum[j] ? j : maxJ;
    }
    printf("\n");

    swapCols(matix, minJ, maxJ, n, m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            printf("%d ", matix[m * i + j]);
        printf("\n");
    }
}
#endif

#ifdef T1
#include <stdio.h>
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int matix[n * m];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%d", matix + n * j + i);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%d ", matix[n * i + j]);
        printf("\n");
    }
}
#endif
