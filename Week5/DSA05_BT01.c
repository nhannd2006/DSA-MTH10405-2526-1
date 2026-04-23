#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

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

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) swap(&arr[i], &arr[minIdx]);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int min = -1000, max = 1000;
    int n = N;
    int arr[N];
    initializeRandomArray(arr, n, min, max);
    printf("arr[] = ");
    printArray(arr, n);
    selectionSort(arr, n);
    printf("After sorting: ");
    printArray(arr, n);
    return 0;
}

/*
arr[] = -597 723 -334 374 -254 -797 -925 -39 -535 -427 
After sorting: -925 -797 -597 -535 -427 -334 -254 -39 374 723
*/