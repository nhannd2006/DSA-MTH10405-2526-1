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

void bubbleSort(int arr[], int n) {
    int sorted = 0;
    int unsortedEnd = n - 1;
    while (!sorted) {
        sorted = 1;
        for (int i = 0; i < unsortedEnd; i++) {
            if (arr[i] < arr[i + 1]) {
                sorted = 0;
                swap(&arr[i], &arr[i + 1]);
            }
        }
        unsortedEnd--;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] > arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            swap(&arr[i], &arr[minIdx]);
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int pos = i - 1;
        while (pos >= 0) {
            if (arr[pos] >= key) break;
            arr[pos + 1] = arr[pos];
            pos--;
        }
        arr[pos + 1] = key;
    }
}

void copyArray(int arr[], int n, int nArr[]) {
    for (int i = 0; i < n; i++) {
        nArr[i] = arr[i];
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
    int arr1[N], arr2[N], arr3[N];

    initializeRandomArray(arr1, n, min, max);
    copyArray(arr1, n, arr2);
    copyArray(arr1, n, arr3);
    printf("arr[] = ");
    printArray(arr1, n);

    bubbleSort(arr1, n);
    selectionSort(arr2, n);
    insertionSort(arr3, n);
    printf("Bubble Sort: ");
    printArray(arr1, n);
    printf("Selection Sort: ");
    printArray(arr1, n);
    printf("Insertion Sort: ");
    printArray(arr1, n);
    return 0;
}

/*
arr[] = 833 -808 108 -612 301 -572 963 969 135 -363 
Bubble Sort: 969 963 833 301 135 108 -363 -572 -612 -808
Selection Sort: 969 963 833 301 135 108 -363 -572 -612 -808
Insertion Sort: 969 963 833 301 135 108 -363 -572 -612 -808
*/

/*
Bubble Sort: Duyệt qua mảng và so sánh từng cặp phần tử liền kề, nếu phần tử trước "nhỏ hơn" phần tử sau thì hoán đổi cho nhau. Lặp lại cho tới khi mảng được sắp xếp giảm dần.
Selection Sort: Tìm phần tử lớn nhất trong phần chưa sắp xếp của mảng và hoán đổi nó vào vị trí đầu của phần chưa sắp xếp ấy.
Insertion Sort: Chèn từng phần tử vào phần mảng đã sắp xếp ở bên trái theo đúng thú tự sắp xếp.
*/