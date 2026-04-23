#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertionSort(int arr[], int n, int *comps, int *shifts) {
    *comps = 0;
    *shifts = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int pos = i;
        while (pos > 0) {
            (*comps)++;
            if (arr[pos - 1] <= key) break;
            arr[pos] = arr[pos - 1];
            pos--;
            (*shifts)++;
        }
        arr[pos] = key;
        printf("Passthrough #%d: arr[] = ", i);
        for (int j = 0; j < n; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");
        printf("Comps = %d | Shifts = %d\n", *comps, *shifts);
    }
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int n = 5;
    int arr[10] = {12, 11, 13, 5, 6};
    printf("arr[] = ");
    printArray(arr, n);
    int comps, shifts;
    insertionSort(arr, n, &comps, &shifts);
    return 0;
}

/*
arr[] = 12 11 13 5 6 
Passthrough #1: arr[] = 11 12 13 5 6
Comps = 1 | Shifts = 1
Passthrough #2: arr[] = 11 12 13 5 6
Comps = 2 | Shifts = 1
Passthrough #3: arr[] = 5 11 12 13 6
Comps = 5 | Shifts = 4
Passthrough #4: arr[] = 5 6 11 12 13
Comps = 9 | Shifts = 7
*/