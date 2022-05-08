#include "sort.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void swap(SortType *a, SortType *b) {
    SortType temp = *a;
    *a = *b;
    *b = temp;
}

void InsertSort(SortType A[], int n, int (*compare)(SortType a, SortType b)) {
    int i, j;
    SortType temp;
    // 将各元素插入到已经排好序的序列中（指前面的所有元素）
    for (i = 1; i < n; i++) {
        // 如果当前元素关键字比前驱小，即不调换位置的话序列无序
        if (compare(A[i], A[i - 1]) == SMALL) {
            temp = A[i];
            // 数据移位
            for (j = i - 1; j >= 0 && compare(A[j], temp) == BIG; j--)
                A[j + 1] = A[j];
            A[j + 1] = temp;
        }
    }
}

void BinaryInsertSort(SortType A[], int n,
                      int (*compare)(SortType a, SortType b)) {
    int i, j, low, high, mid;
    SortType temp;
    for (i = 1; i < n; i++) {
        temp = A[i];
        while (low <= high) {
            mid = high / 2 + low / 2;
            if (compare(A[mid], temp) == BIG)
                high = mid - 1;
            else
                low = mid + 1;
        }
        for (j = i - 1; j >= low; --j) A[j + 1] = A[j];
        A[low] = temp;
    }
}

void ShellSort(SortType A[], int n, int (*compare)(SortType a, SortType b)) {
    int i, j, d;
    SortType temp;
    for (d = n / 2; d >= 1; d /= 2) {
        for (i = d; i < n; i++) {
            if (compare(A[i], A[i - d]) == SMALL) {
                temp = A[i];
                for (j = i - d; j >= 0 && compare(A[j], temp) == BIG; j -= d)
                    A[j + d] = A[j];
                A[j + d] = temp;
            }  // if
        }      // for i
    }          // for d
}

void BubbleSort(SortType A[], int n, int (*compare)(SortType a, SortType b)) {
    int i, j;
    bool flag = true;
    // 控制循环次数
    for (i = 0; i < n - 1 && flag; i++) {
        flag = false;
        // 控制对比
        for (j = n - 1; j > i; j--) {
            if (compare(A[j - 1], A[j]) == BIG) {
                swap(&A[j - 1], &A[j]);
                flag = true;
            }
        }
    }
}

int Partition(SortType A[], int low, int high,
              int (*compare)(SortType a, SortType b)) {
    SortType pivotkey = A[low];
    while (low < high) {
        while (low < high && compare(pivotkey, A[high]) != BIG) high--;
        swap(&A[low], &A[high]);
        while (low < high && compare(pivotkey, A[low]) != SMALL) low++;
        swap(&A[low], &A[high]);
    }
    return low;
}

void QSort(SortType A[], int low, int high,
           int (*compare)(SortType a, SortType b)) {
    if (low < high) {
        int pivot = Partition(A, low, high, compare);
        QSort(A, low, pivot - 1, compare);
        QSort(A, pivot + 1, high, compare);
    }
}

void QuickSort(SortType A[], int n, int (*compare)(SortType a, SortType b)) {
    QSort(A, 0, n - 1, compare);
}

void SelectSort(SortType A[], int n, int (*compare)(SortType a, SortType b)) {
    int i, j, min;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (compare(A[j], A[min]) == SMALL) min = j;
        if (min != i) swap(&A[i], &A[min]);
    }
}

void HeapAdjust(int A[], int k, int len,
                int (*compare)(SortType a, SortType b)) {
    A[0] = A[k];
    int i;
    for (i = 2 * k; i <= len; i *= 2) {
        if (i < len && compare(A[i], A[i + 1]) == SMALL) i++;
        if (A[0] >= A[i]) break;
        A[k] = A[i];
        k = i;
    }
    A[k] = A[0];
}

void BuildMaxHeap(int A[], int len, int (*compare)(SortType a, SortType b)) {
    int i;
    for (i = len / 2; i > 0; i--) HeapAdjust(A, i, len, compare);
}

void HeapSort(SortType A[], int n, int (*compare)(SortType a, SortType b)) {
    BuildMaxHeap(A, n, compare);
    int i;
    for (i = n; i > 1; i--) {
        swap(&A[1], &A[i]);
        HeapAdjust(A, 1, i - 1, compare);
    }
}

#define test

#if defined test

int compare(SortType a, SortType b) {
    if (a == b) return EQUAL;
    if (a < b) return SMALL;
    if (a > b) return BIG;
}

int main(void) {
    // int a[] = {49, 28, 65, 97, 76, 13, 27, 49};
    int a[] = {0, 49, 28, 65, 97, 76, 13, 27, 49};
    // QuickSort(a, 8, compare);
    // SelectSort(a, 8, compare);

    HeapSort(a, 8, compare);
    int i;
    // for (i = 0; i < 8; i++) {
    for (i = 1; i <= 8; i++) {
        printf("%-3d", a[i]);
    }
    putchar('\n');
}

#endif