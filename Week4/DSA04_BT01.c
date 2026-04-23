#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubbleSort(int arr[], int n) {
    int sorted = 0;
    int unsortedEnd = n - 1;
    while (!sorted) {
        sorted = 1;
        for (int i = 0; i < unsortedEnd; i++) {
            if (arr[i] > arr[i + 1]) {
                sorted = 0;
                swap(&arr[i], &arr[i + 1]);
            }
        }
        unsortedEnd--;
    }
}

void initializeArray(int arr[], int n, int min, int max) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + rand() % (max - min + 1);
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
    int n;
    int min = -10000, max = 10000;
    printf("Enter size of array: ");
    scanf("%d", &n);
    int arr[100];
    initializeArray(arr, n, min, max);
    printf("Unsorted: arr = ");
    printArray(arr, n);
    bubbleSort(arr, n);
    printf("Sorted: arr = ");
    printArray(arr, n);
    return 0;
}