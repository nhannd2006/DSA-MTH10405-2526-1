#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 4

void initializeRandomArray(int arr[], int n, int min, int max) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + rand() % (max - min + 1);
    }
}

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
            if (arr[i] < arr[i + 1]) {
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
            if (arr[j] > arr[minIdx]) minIdx = j;
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
            if (arr[pos] >= key) break;
            arr[pos + 1] = arr[pos];
            pos--;
            (*shifts)++;
        }
        arr[pos + 1] = key;
    }
    return (*comps + *shifts);
}

void printArray(int arr[], int n) {
    printf("arr[] = ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void copyArray(int arr[], int n, int nArr[]) {
    for (int i = 0; i < n; i++) {
        nArr[i] = arr[i];
    }
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int min = -1000, max = 1000;
    int arr1[100], arr2[100], arr3[100];
    int bubbleComps, bubbleSwaps;
    int selectComps, selectSwaps;
    int insertComps, insertShifts;
    int NUMS[N] = {10, 20, 50, 100};
    for (int n = 0; n < N; n++) {
        initializeRandomArray(arr1, NUMS[n], min, max);
        copyArray(arr1, NUMS[n], arr2);
        copyArray(arr1, NUMS[n], arr3);
        int bubbleSteps = bubbleSort(arr1, NUMS[n], &bubbleComps, &bubbleSwaps);
        int selectSteps = selectionSort(arr2, NUMS[n], &selectComps, &selectSwaps);
        int insertSteps = insertionSort(arr3, NUMS[n], &insertComps, &insertShifts);
        printf("With n = %d:\n", NUMS[n]);
        printf("Bubble comps = %d, Bubble swaps = %d\n", bubbleComps, bubbleSwaps);
        printf("Bubble total steps = %d\n", bubbleSteps);
        printf("Selection comps = %d, Selection swaps = %d\n", selectComps, selectSwaps);
        printf("Selection total steps = %d\n", selectSteps);
        printf("Insertion comps = %d, Insertion shifts = %d\n", insertComps, insertShifts);
        printf("Insertion total steps = %d\n", insertSteps);      
        printf("\n");
    }
    return 0;
}

/*
With n = 10:
Bubble comps = 39, Bubble swaps = 22
Bubble total steps = 61
Selection comps = 45, Selection swaps = 8
Selection total steps = 53
Insertion comps = 30, Insertion shifts = 22
Insertion total steps = 52

With n = 20:
Bubble comps = 190, Bubble swaps = 101
Bubble total steps = 291
Selection comps = 190, Selection swaps = 17
Selection total steps = 207
Insertion comps = 115, Insertion shifts = 101
Insertion total steps = 216

With n = 50:
Bubble comps = 1197, Bubble swaps = 659
Bubble total steps = 1856
Selection comps = 1225, Selection swaps = 49
Selection total steps = 1274
Insertion comps = 701, Insertion shifts = 659
Insertion total steps = 1360

With n = 100:
Bubble comps = 4940, Bubble swaps = 2341
Bubble total steps = 7281
Selection comps = 4950, Selection swaps = 93
Selection total steps = 5043
Insertion comps = 2435, Insertion shifts = 2341
Insertion total steps = 4776
*/