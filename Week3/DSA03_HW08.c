#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 20
#define K 3

void initializeRandomArray(int arr[], int n, int min, int max) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + rand() % (max - min + 1);
    }
}

void printArray(int arr[], int n) {
    printf("arr[] = ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void shellSort(int arr[], int n, int *assigns, int *shifts) {
    *assigns = 0; *shifts = 0;
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            (*assigns)++;
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                (*shifts)++;
                arr[j] = arr[j - gap];
                j -= gap;
            }
            (*assigns)++;
            arr[j] = temp;
            printArray(arr, n);
            printf("Assigns = %d - Shifts = %d\n", *assigns, *shifts);
        }
    }
}

int main() {
    int n = N;
    int arr[N] = {34, 29, 10, 3, 2, 44, 88, 1, 21, 12, 3, 18, 21, 23, 37, 17, 8, 9, 4, 0};
    int assigns = 0, shifts = 0;
    printf("With arr[] = 34, 29, 10, 3, 2, 44, 88, 1, 21, 12, 3, 18, 21, 23, 37, 17, 8, 9, 4, 0\n");
    shellSort(arr, n, &assigns, &shifts);
    return 0;
}

/*OUTPUT:
With arr[] = 34, 29, 10, 3, 2, 44, 88, 1, 21, 12, 3, 18, 21, 23, 37, 17, 8, 9, 4, 0
arr[] = 3 29 10 3 2 44 88 1 21 12 34 18 21 23 37 17 8 9 4 0 
Assigns = 2 - Shifts = 1
arr[] = 3 18 10 3 2 44 88 1 21 12 34 29 21 23 37 17 8 9 4 0
Assigns = 4 - Shifts = 2
arr[] = 3 18 10 3 2 44 88 1 21 12 34 29 21 23 37 17 8 9 4 0
Assigns = 6 - Shifts = 2
arr[] = 3 18 10 3 2 44 88 1 21 12 34 29 21 23 37 17 8 9 4 0
Assigns = 8 - Shifts = 2
arr[] = 3 18 10 3 2 44 88 1 21 12 34 29 21 23 37 17 8 9 4 0
Assigns = 10 - Shifts = 2
arr[] = 3 18 10 3 2 17 88 1 21 12 34 29 21 23 37 44 8 9 4 0
Assigns = 12 - Shifts = 3
arr[] = 3 18 10 3 2 17 8 1 21 12 34 29 21 23 37 44 88 9 4 0
Assigns = 14 - Shifts = 4
arr[] = 3 18 10 3 2 17 8 1 21 12 34 29 21 23 37 44 88 9 4 0
Assigns = 16 - Shifts = 4
arr[] = 3 18 10 3 2 17 8 1 4 12 34 29 21 23 37 44 88 9 21 0
Assigns = 18 - Shifts = 5
arr[] = 3 18 10 3 2 17 8 1 4 0 34 29 21 23 37 44 88 9 21 12
Assigns = 20 - Shifts = 6
arr[] = 3 18 10 3 2 17 8 1 4 0 34 29 21 23 37 44 88 9 21 12
Assigns = 22 - Shifts = 6
arr[] = 3 8 10 3 2 17 18 1 4 0 34 29 21 23 37 44 88 9 21 12
Assigns = 24 - Shifts = 7
arr[] = 3 8 1 3 2 17 18 10 4 0 34 29 21 23 37 44 88 9 21 12
Assigns = 26 - Shifts = 8
arr[] = 3 8 1 3 2 17 18 10 4 0 34 29 21 23 37 44 88 9 21 12
Assigns = 28 - Shifts = 8
arr[] = 3 8 1 3 0 17 18 10 4 2 34 29 21 23 37 44 88 9 21 12 
Assigns = 30 - Shifts = 9
arr[] = 3 8 1 3 0 17 18 10 4 2 34 29 21 23 37 44 88 9 21 12
Assigns = 32 - Shifts = 9
arr[] = 3 8 1 3 0 17 18 10 4 2 34 29 21 23 37 44 88 9 21 12
Assigns = 34 - Shifts = 9
arr[] = 3 8 1 3 0 17 18 10 4 2 34 29 21 23 37 44 88 9 21 12
Assigns = 36 - Shifts = 9
arr[] = 3 8 1 3 0 17 18 10 4 2 34 29 21 23 37 44 88 9 21 12
Assigns = 38 - Shifts = 9
arr[] = 3 8 1 3 0 17 18 10 4 2 34 29 21 23 37 44 88 9 21 12
Assigns = 40 - Shifts = 9
arr[] = 3 8 1 3 0 17 18 10 4 2 34 29 21 23 37 44 88 9 21 12
Assigns = 42 - Shifts = 9
arr[] = 3 8 1 3 0 17 18 10 4 2 34 29 21 23 37 44 88 9 21 12
Assigns = 44 - Shifts = 9
arr[] = 3 8 1 3 0 17 18 9 4 2 34 29 10 23 37 44 88 21 21 12
Assigns = 46 - Shifts = 11
arr[] = 3 8 1 3 0 17 18 9 4 2 34 29 10 21 37 44 88 21 23 12
Assigns = 48 - Shifts = 12
arr[] = 3 8 1 3 0 17 18 9 4 2 34 29 10 21 12 44 88 21 23 37
Assigns = 50 - Shifts = 13
arr[] = 1 8 3 3 0 17 18 9 4 2 34 29 10 21 12 44 88 21 23 37
Assigns = 52 - Shifts = 14
arr[] = 1 3 3 8 0 17 18 9 4 2 34 29 10 21 12 44 88 21 23 37
Assigns = 54 - Shifts = 15
arr[] = 0 3 1 8 3 17 18 9 4 2 34 29 10 21 12 44 88 21 23 37
Assigns = 56 - Shifts = 17
arr[] = 0 3 1 8 3 17 18 9 4 2 34 29 10 21 12 44 88 21 23 37
Assigns = 58 - Shifts = 17
arr[] = 0 3 1 8 3 17 18 9 4 2 34 29 10 21 12 44 88 21 23 37
Assigns = 60 - Shifts = 17
arr[] = 0 3 1 8 3 9 18 17 4 2 34 29 10 21 12 44 88 21 23 37
Assigns = 62 - Shifts = 18
arr[] = 0 3 1 8 3 9 4 17 18 2 34 29 10 21 12 44 88 21 23 37 
Assigns = 64 - Shifts = 19
arr[] = 0 2 1 3 3 8 4 9 18 17 34 29 10 21 12 44 88 21 23 37
Assigns = 66 - Shifts = 23
arr[] = 0 2 1 3 3 8 4 9 18 17 34 29 10 21 12 44 88 21 23 37
Assigns = 68 - Shifts = 23
arr[] = 0 2 1 3 3 8 4 9 18 17 34 29 10 21 12 44 88 21 23 37
Assigns = 70 - Shifts = 23
arr[] = 0 2 1 3 3 8 4 9 10 17 18 29 34 21 12 44 88 21 23 37
Assigns = 72 - Shifts = 25
arr[] = 0 2 1 3 3 8 4 9 10 17 18 21 34 29 12 44 88 21 23 37
Assigns = 74 - Shifts = 26
arr[] = 0 2 1 3 3 8 4 9 10 17 12 21 18 29 34 44 88 21 23 37
Assigns = 76 - Shifts = 28
arr[] = 0 2 1 3 3 8 4 9 10 17 12 21 18 29 34 44 88 21 23 37
Assigns = 78 - Shifts = 28
arr[] = 0 2 1 3 3 8 4 9 10 17 12 21 18 29 34 44 88 21 23 37
Assigns = 80 - Shifts = 28
arr[] = 0 2 1 3 3 8 4 9 10 17 12 21 18 21 34 29 88 44 23 37
Assigns = 82 - Shifts = 30
arr[] = 0 2 1 3 3 8 4 9 10 17 12 21 18 21 23 29 34 44 88 37
Assigns = 84 - Shifts = 32
arr[] = 0 2 1 3 3 8 4 9 10 17 12 21 18 21 23 29 34 37 88 44
Assigns = 86 - Shifts = 33
arr[] = 0 2 1 3 3 8 4 9 10 17 12 21 18 21 23 29 34 37 88 44
Assigns = 88 - Shifts = 33
arr[] = 0 1 2 3 3 8 4 9 10 17 12 21 18 21 23 29 34 37 88 44
Assigns = 90 - Shifts = 34
arr[] = 0 1 2 3 3 8 4 9 10 17 12 21 18 21 23 29 34 37 88 44
Assigns = 92 - Shifts = 34
arr[] = 0 1 2 3 3 8 4 9 10 17 12 21 18 21 23 29 34 37 88 44 
Assigns = 94 - Shifts = 34
arr[] = 0 1 2 3 3 8 4 9 10 17 12 21 18 21 23 29 34 37 88 44
Assigns = 96 - Shifts = 34
arr[] = 0 1 2 3 3 4 8 9 10 17 12 21 18 21 23 29 34 37 88 44
Assigns = 98 - Shifts = 35
arr[] = 0 1 2 3 3 4 8 9 10 17 12 21 18 21 23 29 34 37 88 44
Assigns = 100 - Shifts = 35
arr[] = 0 1 2 3 3 4 8 9 10 17 12 21 18 21 23 29 34 37 88 44
Assigns = 102 - Shifts = 35
arr[] = 0 1 2 3 3 4 8 9 10 17 12 21 18 21 23 29 34 37 88 44
Assigns = 104 - Shifts = 35
arr[] = 0 1 2 3 3 4 8 9 10 12 17 21 18 21 23 29 34 37 88 44
Assigns = 106 - Shifts = 36
arr[] = 0 1 2 3 3 4 8 9 10 12 17 21 18 21 23 29 34 37 88 44
Assigns = 108 - Shifts = 36
arr[] = 0 1 2 3 3 4 8 9 10 12 17 18 21 21 23 29 34 37 88 44
Assigns = 110 - Shifts = 37
arr[] = 0 1 2 3 3 4 8 9 10 12 17 18 21 21 23 29 34 37 88 44
Assigns = 112 - Shifts = 37
arr[] = 0 1 2 3 3 4 8 9 10 12 17 18 21 21 23 29 34 37 88 44
Assigns = 114 - Shifts = 37
arr[] = 0 1 2 3 3 4 8 9 10 12 17 18 21 21 23 29 34 37 88 44
Assigns = 116 - Shifts = 37
arr[] = 0 1 2 3 3 4 8 9 10 12 17 18 21 21 23 29 34 37 88 44
Assigns = 118 - Shifts = 37
arr[] = 0 1 2 3 3 4 8 9 10 12 17 18 21 21 23 29 34 37 88 44
Assigns = 120 - Shifts = 37
arr[] = 0 1 2 3 3 4 8 9 10 12 17 18 21 21 23 29 34 37 88 44
Assigns = 122 - Shifts = 37
arr[] = 0 1 2 3 3 4 8 9 10 12 17 18 21 21 23 29 34 37 44 88
Assigns = 124 - Shifts = 38
*/
