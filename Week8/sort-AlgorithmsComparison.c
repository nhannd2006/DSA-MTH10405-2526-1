#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubbleSort(int arr[], int n, int *comps, int *swaps) {
    *comps = 0; *swaps = 0;
    int sorted = 0;
    int unsortedEnd = n - 1;
    while (!sorted) {
        sorted = 1;
        for (int i = 0; i < unsortedEnd; i++) {
            (*comps)++;
            if (arr[i] > arr[i + 1]) {
                sorted = 0;
                (*swaps)++;
                swap(&arr[i], &arr[i + 1]);
            }
        }
        unsortedEnd--;
    }
}

void selectionSort(int arr[], int n, int *comps, int *swaps) {
    *comps = 0;
    *swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            (*comps)++;
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            swap(&arr[i], &arr[minIdx]);
            (*swaps)++;
        }
    }
}

void insertionSort(int arr[], int n, int *comps, int *shifts) {
    *comps = 0;
    *shifts = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int pos = i - 1;
        while (pos >= 0) {
            (*comps)++;
            if (arr[pos] <= key) break;
            arr[pos + 1] = arr[pos];
            pos--;
            (*shifts)++;
        }
        arr[pos + 1] = key;
    }
}

int partition(int arr[], int left, int right, int *comps, int *swaps) {
    int pivotIdx = right;
    right--;
    while(1) {
        while (1) {
            (*comps)++;
            if (arr[left] < arr[pivotIdx]) left++;
            else break;
        }
        while (1) {
            (*comps)++;
            if (arr[right] > arr[pivotIdx] && left < right) right--;
            else break;
        }
        if (left >= right) {
            break;
        } else {
            (*swaps)++;
            swap(&arr[left], &arr[right]);
            left++;
            right--;
        }
    }
    (*swaps)++;
    swap(&arr[left], &arr[pivotIdx]);
    return left;
}

void quickSort(int arr[], int n, int left, int right, int *comps, int *swaps) {
    if (left >= right) {
        return;
    }
    else {
        int pivotIdx = partition(arr, left, right, comps, swaps);
        quickSort(arr, n, left, pivotIdx - 1, comps, swaps);
        quickSort(arr, n, pivotIdx + 1, right, comps, swaps);
    }
}

void compareSort(int arr1[], int comps1, int swaps1,
                int arr2[], int comps2, int swaps2,
                int arr3[], int comps3, int shifts3,
                int arr4[], int comps4, int swaps4, int n) {
    bubbleSort(arr1, n, &comps1, &swaps1);
    int steps1 = comps1 + swaps1;
    printf("- Bubble Sort: steps = %d (comps = %d, swaps = %d)\n", steps1, comps1, swaps1);
    selectionSort(arr2, n, &comps2, &swaps2);
    int steps2 = comps2 + swaps2;
    printf("- Selection Sort: steps = %d (comps = %d, swaps = %d)\n", steps2, comps2, swaps2);
    insertionSort(arr3, n, &comps3, &shifts3);
    int steps3 = comps3 + shifts3;
    printf("- Insertion Sort: steps = %d (comps = %d, shifts = %d)\n", steps3, comps3, shifts3);
    quickSort(arr4, n, 0, n - 1, &comps4, &swaps4);
    int steps4 = comps4 + swaps4;
    printf("- Quick Sort: steps = %d (comps = %d, swaps = %d)\n", steps4, comps4, swaps4);
}

int main() {
    int comps1 = 0, swaps1 = 0;
    int comps2 = 0, swaps2 = 0;
    int comps3 = 0, shift3 = 0;
    int comps4 = 0, swaps4 = 0;
    int a = 5;
    int a1[5] = {3, 2, 9, 7, 5},
        a2[5] = {3, 2, 9, 7, 5},
        a3[5] = {3, 2, 9, 7, 5},
        a4[5] = {3, 2, 9, 7, 5};
    printf("With n = 5, a[] = 3 2 9 7 5:\n");
    compareSort(a1, comps1, swaps1, a2, comps2, swaps2, a3, comps3, shift3, a4, comps4, swaps4, a);
    int b = 10;
    int b1[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
        b2[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
        b3[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
        b4[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    printf("With n = 10, a[] = 10 9 8 7 6 5 4 3 2 1:\n");
    compareSort(b1, comps1, swaps1, b2, comps2, swaps2, b3, comps3, shift3, b4, comps4, swaps4, b);
    int c = 20;
    int c1[20] = {4, 3, 2, 6, 5, -3, 5, 7, -3, 1, -3, 5, 7, 9, 7, -5, 3, 2, 1, 2},
        c2[20] = {4, 3, 2, 6, 5, -3, 5, 7, -3, 1, -3, 5, 7, 9, 7, -5, 3, 2, 1, 2},
        c3[20] = {4, 3, 2, 6, 5, -3, 5, 7, -3, 1, -3, 5, 7, 9, 7, -5, 3, 2, 1, 2},
        c4[20] = {4, 3, 2, 6, 5, -3, 5, 7, -3, 1, -3, 5, 7, 9, 7, -5, 3, 2, 1, 2};
    printf("With n = 20, a[] = 4 3 2 6 5 -3 5 7 -3 1 -3 5 7 9 7 -5 3 2 1 2:\n");
    compareSort(c1, comps1, swaps1, c2, comps2, swaps2, c3, comps3, shift3, c4, comps4, swaps4, c);
    int d = 20;
    int d1[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 11, 17, 14, 15, 16, 13, 18, 19, 20},
        d2[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 11, 17, 14, 15, 16, 13, 18, 19, 20},
        d3[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 11, 17, 14, 15, 16, 13, 18, 19, 20},
        d4[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 11, 17, 14, 15, 16, 13, 18, 19, 20};
    printf("With n = 20, a[] = 1 2 3 4 5 6 7 8 9 10 12 11 17 14 15 16 13 18 19 20:\n");
    compareSort(d1, comps1, swaps1, d2, comps2, swaps2, d3, comps3, shift3, d4, comps4, swaps4, d);
    return 0;
}

/*
With n = 5, a[] = 3 2 9 7 5:
- Bubble Sort: steps = 13 (comps = 9, swaps = 4)
- Selection Sort: steps = 12 (comps = 10, swaps = 2)
- Insertion Sort: steps = 11 (comps = 7, shifts = 4)
- Quick Sort: steps = 13 (comps = 10, swaps = 3)
With n = 10, a[] = 10 9 8 7 6 5 4 3 2 1:
- Bubble Sort: steps = 90 (comps = 45, swaps = 45)
- Selection Sort: steps = 50 (comps = 45, swaps = 5)
- Insertion Sort: steps = 90 (comps = 45, shifts = 45)
- Quick Sort: steps = 67 (comps = 58, swaps = 9)
With n = 20, a[] = 4 3 2 6 5 -3 5 7 -3 1 -3 5 7 9 7 -5 3 2 1 2:
- Bubble Sort: steps = 278 (comps = 184, swaps = 94)
- Selection Sort: steps = 209 (comps = 190, swaps = 19)
- Insertion Sort: steps = 203 (comps = 109, shifts = 94)
- Quick Sort: steps = 111 (comps = 82, swaps = 29)
With n = 20, a[] = 1 2 3 4 5 6 7 8 9 10 12 11 17 14 15 16 13 18 19 20:
- Bubble Sort: steps = 93 (comps = 85, swaps = 8)
- Selection Sort: steps = 192 (comps = 190, swaps = 2)
- Insertion Sort: steps = 35 (comps = 27, shifts = 8)
- Quick Sort: steps = 181 (comps = 164, swaps = 17)
*/