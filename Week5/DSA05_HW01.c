#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int bubbleSort(int arr[], int n, int *comps, int *swaps) {
    *comps = 0;
    *swaps = 0;
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
    return (*comps + *swaps);
}

int selectionSort(int arr[], int n, int *comps, int *swaps) {
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
    return (*comps + *swaps);
}

int insertionSort(int arr[], int n, int *comps, int *shifts) {
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
    return (*comps + *shifts);
}

int main() {
    int n = N;
    int arr1[N] = {3, 1, 8, 2, 6, 5, 3, 9, 1, 0};
    int arr2[N] = {3, 1, 8, 2, 6, 5, 3, 9, 1, 0};
    int arr3[N] = {3, 1, 8, 2, 6, 5, 3, 9, 1, 0};
    int bubbleComps, bubbleSwaps;
    int selectComps, selectSwaps;
    int insertComps, insertShifts;
    int bubbleSteps = bubbleSort(arr1, n, &bubbleComps, &bubbleSwaps);
    int selectSteps = selectionSort(arr2, n, &selectComps, &selectSwaps);
    int insertSteps = insertionSort(arr3, n, &insertComps, &insertShifts);
    printf("Bubble comps = %d, Bubble swaps = %d\n", bubbleComps, bubbleSwaps);
    printf("Bubble total steps = %d\n", bubbleSteps);
    printf("Selection comps = %d, Selection swaps = %d\n", selectComps, selectSwaps);
    printf("Selection total steps = %d\n", selectSteps);
    printf("Insertion comps = %d, Insertion shifts = %d\n", insertComps, insertShifts);
    printf("Insertion total steps = %d\n", insertSteps);
    return 0;
}

/*
Bubble comps = 45, Bubble swaps = 25
Bubble total steps = 70
Selection comps = 45, Selection swaps = 6
Selection total steps = 51
Insertion comps = 32, Insertion shifts = 25
Insertion total steps = 57
*/