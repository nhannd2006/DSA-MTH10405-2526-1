#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int partition(int arr[], int left, int right) {
    int pivot = right;
    right--;
    while(left < right) {
        while (arr[left] < arr[pivot]) left++;
        while (arr[right] > arr[pivot]) right--;
        if (left < right) {
            swap(&arr[left], &arr[right]);
        }
    }
    swap(&arr[left], &arr[pivot]);
    return left;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr1[] = {1, 3, 7, 8, 5};
    int pivot1 = partition(arr1, 0, 4);
    printf("pivot1 = %d\narr1[] = ", pivot1);
    printArray(arr1, 5);
    int arr2[] = {0, 2, 3, 9, 5, 6, 8, 4};
    int pivot2 = partition(arr2, 0, 7);
    printf("pivot2 = %d\narr2[] = ", pivot2);
    printArray(arr2, 8);
    int arr3[] = {8, 7, 6, 5, 4, 3, 2, 1};
    int pivot3 = partition(arr3, 0, 7);
    printf("pivot3 = %d\narr3[] = ", pivot3);
    printArray(arr3, 8);
    return 0;
}

/*
pivot1 = 5
arr1[] = 1 3 5 8 7
pivot2 = 4
arr2[] = 0 2 3 4 5 6 8 9
pivot3 = 1
arr3[] = 1 7 6 5 4 3 2 8
*/