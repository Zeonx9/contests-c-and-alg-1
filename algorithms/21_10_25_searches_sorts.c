#define T

#ifdef T6
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 2; i <= n; i += 2)
        printf("%d ", i);
    for (int i = n % 2 ? n : n - 1; i > 0; i -= 2)
        printf("%d ", i);
}
#endif

#ifdef T5
#include <stdio.h>
void quickSort(int arr[], int start, int end, int size) {
    if (end - start < 2)
        return;

    int mid = (start + end - 1) / 2, pivot = arr[mid];
    printf("\n\nPivot index: %d , pivot element: %d\n", mid, pivot);

    for (int i = mid - 1; i >= start; --i)
        if (arr[i] > pivot) {
            int tmp = arr[i];
            for (int k = i; k < mid; ++k)
                arr[k] = arr[k + 1];
            arr[mid--] = tmp;
        }

    for (int i = mid + 1; i < end; ++i)
        if (arr[i] <= pivot) {
            int tmp = arr[i];
            for (int k = i; k > mid; --k)
                arr[k] = arr[k - 1];
            arr[mid++] = tmp;
        }

    printf("Array after partition: ");
    for (int m = 0; m < size; ++m)
        printf("%d ", arr[m]);

    quickSort(arr, start, mid, size);
    quickSort(arr, mid + 1, end, size);
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    printf("Initial array:\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d", arr + i);
        printf("%d ", arr[i]);
    }
    quickSort(arr, 0, n, n);
}
#endif

#ifdef T4
#include <stdio.h>

void copyArray(int dest[], const int src[], int size) {
    for (int i = 0; i < size; ++i)
        dest[i] = src[i];
}
void printArray(int *arr, int size){
    for (int i = 0; i < size; ++i)
        printf("%d ", arr[i]);
}

void mergeSort(int * arr, int size) {
    if (size < 2) return;
    int leftSize = size / 2, rightSize = size - leftSize;
    int left[leftSize], right[rightSize];
    copyArray(left, arr, leftSize);
    copyArray(right, arr + leftSize, rightSize);

    mergeSort(left, leftSize);
    mergeSort(right, rightSize);

    int i = 0, j = 0;
    for (int k = 0; k < size; ++k){
        arr[k] = (i < leftSize && j < rightSize && left[i] <= right[j]) || j == rightSize ?
                left[i++] :
                right[j++];
    }

    printf("\n\nLeft part: ");
    printArray(left, leftSize);
    printf("\nRight part: ");
    printArray(right, rightSize);
    printf("\nMerged parts: ");
    printArray(arr, size);
}


int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    printf("Initial array:\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d", arr + i);
        printf("%d ", arr[i]);
    }
    mergeSort(arr, n);
}
#endif

#ifdef T3
#include <stdio.h>
int main() {
    int n, target;
    scanf("%d%d", &n, &target);
    int arr[n];
    printf("Initial array:\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d", arr + i);
        printf("%d ", arr[i]);
    }
    printf("\nTarget element: %d\n", target);
    printf("Bounds history: %d(0) ", arr[0]);

    if (arr[0] == target){
        printf("\nTarget is found at: 0\n");
        return 0;
    } else if (arr[0] > target) {
        printf("\nNo targets\n");
        return 0;
    }

    int k = 1;
    while (k < n) {
        printf("%d(%d) ", arr[k], k);
        if (arr[k] == target){
            printf("\nTarget is found at: %d\n", k);
            return 0;
        }
        if (arr[k] > target)
            break;
        k *= 2;
    }
    if (k == 1) {
        printf("\nNo targets\n");
        return 0;
    }

    int start = k / 2 + 1, end = k < n ? k - 1 : n - 1;
    if (start <= end)
        printf("\nSearch history: ");

    while (start <= end){
        int mid = (start + end) / 2;
        printf("%d(%d) ", arr[mid], mid);
        if (arr[mid] == target){
            printf("\nTarget is found at: %d\n", mid);
            return 0;
        } else if (arr[mid] < target)
            start = mid + 1;
        else
            end = mid - 1;
    }
    printf("\nNo targets\n");
}
#endif

#ifdef T2
#include <stdio.h>
int main() {
    int n, target;
    scanf("%d%d", &n, &target);
    int arr[n];
    printf("Initial array:\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d", arr + i);
        printf("%d ", arr[i]);
    }
    printf("\nTarget element: %d\n", target);

    int start = 0, end = n - 1;
    printf("Search history: ");
    while (start <= end){
        int mid = (start + end) / 2;
        printf("%d(%d) ", arr[mid], mid);
        if (arr[mid] == target){
            printf("\nTarget is found at: %d\n", mid);
            return 0;
        } else if (arr[mid] < target)
            start = mid + 1;
        else
            end = mid - 1;
    }
    printf("\nNo targets\n");
}
#endif

#ifdef T1
#include <stdio.h>
int main() {
    int n, target;
    scanf("%d%d", &n, &target);
    int arr[n];
    printf("Initial array:\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d", arr + i);
        printf("%d ", arr[i]);
    }
    printf("\nTarget element: %d\n", target);
    int count = 0;
    for (int i = 0; i < n; ++i)
        if (arr[i] == target) {
            if (!count++)
                printf("Target is found at:");
            printf(" %d", i);
        }
    printf("%s", count ? "\n" : "No targets\n");

}
#endif