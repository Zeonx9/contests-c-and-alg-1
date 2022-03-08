#define T

#ifdef TC
#include <stdio.h>
void insertSort(double arr[], int size) {
    for (int i = 1; i < size; i++) {
        int j = i - 1, k = i;
        while (j >= 0 && arr[k] < arr[j]) {
            double tmp = arr[k];
            arr[k] = arr[j];
            arr[j] = tmp;
            k = j--;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    double arr[n];
    for (int i = 0; i < n; i++) scanf("%lf", arr + i);
    printf("Initial array:\n");
    for (int i = 0; i < n; i++) printf("%.2lf ", arr[i]);

    double minv = arr[0], maxv = arr[0];
    int k = n * 2;
    for (int i = 0; i < n; i++){
        if (arr[i] < minv) minv = arr[i];
        if (arr[i] > maxv) maxv = arr[i];
    }

    double buckets[k][10];
    int bs[k];
    for(int i = 0; i < k; i++) bs[i] = 0;
    for (int i = 0; i < n; i++) {
        int ind = arr[i] == maxv ? k - 1 : (int)(k * (arr[i] - minv) / (maxv - minv));
        buckets[ind][bs[ind]] = arr[i];
        bs[ind]++;
    }

    int ii = 0;
    for (int i = 0; i < k; i++) {
        double cur[bs[i]];
        for (int j = 0; j < bs[i]; j++) cur[j] = buckets[i][j];
        if (bs[i] > 0) {
            printf("\n\nBucket:\n");
            for (int j = 0; j < bs[i]; j++) printf("%.2lf ", cur[j]);
            insertSort(cur, bs[i]);
            printf("\nSorted bucket:\n");
            for (int j = 0; j < bs[i]; j++) {
                printf("%.2lf ", cur[j]);
                arr[ii] = cur[j];
                ii++;
            }
        }
    }
    printf("\n\nFinal array:\n");
    for (int i = 0; i < n; i++) printf("%.2lf ", arr[i]);
    return 0;
}
#endif

#ifdef TB
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    int n;
    scanf("%d", &n);
    char arr[n][41];
    for (int i = 0; i < n; i++) scanf("%s", arr[i]);

    int digits = 0;
    for (int i = 0; i < n; i++) {
        if (strlen(arr[i]) > digits)
            digits = (int) strlen(arr[i]);
    }
    for (int i = 0; i < digits; i++) {
        int bs[16] = {0};
        char buff[16][n][101];
        printf("Sorting by %d digit:\n", digits - (i + 1));
        for(int j = 0; j < n; j++){
            int group = 0;
            if (strlen(arr[j]) > i) {
                char cd = arr[j][strlen(arr[j]) - (i + 1)];
                group = isdigit(cd) ? cd - '0' : cd - 'A' + 10;
            }
            for (int p = 0; p < strlen(arr[j]); p++){
                buff[group][bs[group]][p] = arr[j][p];
            }
            buff[group][bs[group]][strlen(arr[j])] = '\0';
            bs[group]++;
        }
        int k = 0;
        for (int j = 0; j < 16; j++) {
            for (int bj = 0; bj < bs[j]; bj++){
                for (int p = 0; p < strlen(buff[j][bj]); p++)
                    arr[k][p] = buff[j][bj][p];
                arr[k][strlen(buff[j][bj])] = '\0';
                k++;
            }
        }
        for (int p = 0; p < n; p++) printf("%s\n", arr[p]);
        printf("\n");
    }
    return 0;
}
#endif

#ifdef TA
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) scanf("%d", arr + i);
    printf("Initial array:\n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);

    for (int i = 1; i < n; i++) {
        int j = i - 1;
        while (j >= 0 && arr[j + 1] < arr[j]) {
            int temp = arr[j + 1];
            arr[j + 1] = arr[j];
            arr[j] = temp;
            --j;
        }
        printf("\nInsertion - Element #%d\n", i);
        for (int p = 0; p < n; p++) printf("%d ", arr[p]);
    }
    return 0;
}
#endif

