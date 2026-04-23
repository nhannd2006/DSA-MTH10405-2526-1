#include <stdio.h>

#define N 6

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void printSubArray(int arr[], int left, int right) {
    for (int i = left; i <= right; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int partition(int arr[], int left, int right) {
    int pivotIdx = right;
    right--;
    while(1) {
        while (arr[left] < arr[pivotIdx]) left++;
        while (arr[right] > arr[pivotIdx] && left < right) right--;
        if (left >= right) {
            break;
        } else {
            swap(&arr[left], &arr[right]);
            left++;
            right--;
        }
    }
    swap(&arr[left], &arr[pivotIdx]);
    return left;
}

void quickSort(int arr[], int n, int left, int right) {
    if (left >= right) {
        printf("quickSort(arr, %d, %d): ", left, right);
        printSubArray(arr, left, right);
        return;
    }
    else {
        int pivotIdx = partition(arr, left, right);
        printf("quickSort(arr, %d, %d) with pivot index = %d: ", left, right, pivotIdx);
        printSubArray(arr, left, right);
        quickSort(arr, n, left, pivotIdx - 1);
        quickSort(arr, n, pivotIdx + 1, right);
    }
}

int main() {
    int n = N;
    int arr[N] = {6,2,6,5,1,2};
    printf("QuickSort:\n");
    quickSort(arr, n, 0, n - 1);
    printf("Array after sorting:\narr[] = ");
    printSubArray(arr, 0, n - 1);
    return 0;
}

/*
QuickSort:
quickSort(arr, 0, 10) with pivotIdx = 2: -4 -4 -2 1 5 10 6 3 11 9 2 
quickSort(arr, 0, 1) with pivotIdx = 0: -4 -4
quickSort(arr, 0, -1):
quickSort(arr, 1, 1): -4
quickSort(arr, 3, 10) with pivotIdx = 4: 1 2 10 6 3 11 9 5
quickSort(arr, 3, 3): 1
quickSort(arr, 5, 10) with pivotIdx = 6: 3 5 10 11 9 6
quickSort(arr, 5, 5): 3
quickSort(arr, 7, 10) with pivotIdx = 7: 6 11 9 10
quickSort(arr, 7, 6):
quickSort(arr, 8, 10) with pivotIdx = 9: 9 10 11
quickSort(arr, 8, 8): 9
quickSort(arr, 10, 10): 11
Array after sorting:
arr[] = -4 -4 -2 1 2 3 5 6 9 10 11
*/

/*
BASE CASE: left >= right --> tức mảng có 1 hoặc 0 phần tử
RESULT OF BASE CASE: return --> mặc định mảng có 1 hoặc 0 phần tử là đã được sắp xếp (không thay đổi mảng)
Cụ thể:
    quickSort(arr, 0, -1):
    quickSort(arr, 1, 1): -4
    quickSort(arr, 3, 3): 1
    quickSort(arr, 5, 5): 3
    quickSort(arr, 7, 6):
    quickSort(arr, 8, 8): 9
BEFORE BASE CASE: left + 1 = right, tức mảng có 2 phần tử
    - sau phân hoạch: partition(arr, left, left + 1) thì pivotIdx = left hoặc left + 1
    - sắp xếp hai mảng con: quickSort(arr, n, left, pivotIdx - 1) và quickSort(arr, n, pivotIdx + 1, left + 1)
        + Với pivotIdx = left: [left, left - 1] và [left + 1, left + 1] (mảng 0 và 1 phần tử)
        + Với pivotIdx = left + 1: [left, left] và [left + 2, left + 1] (mảng 1 và 0 phần tử)
    --> cả 2 mảng con đều rơi vào base case (left >= right)
Cụ thể:
    quickSort(arr, 0, 1) with pivotIdx = 0: -4 -4
        quickSort(arr, 0, -1):
        quickSort(arr, 1, 1): -4
BEFORE BEFORE: left + 2 = right, tức mảng có 3 phần tử
    - sau phân hoạch: partition(arr, left, left + 2) thì pivotIdx = left hoặc left + 1 hoặc left + 2
    - sắp xếp hai mảng con: quickSort(arr, n, left, pivotIdx - 1) và quickSort(arr, n, pivotIdx + 1, left + 2)
        + Với pivotIdx = left: [left, left - 1] và [left + 1, left + 2] (mảng 0 và 2 phần tử)
        + Với pivotIdx = left + 1: [left, left] và [left + 2, left + 2] (mảng 1 và 1 phần tử)
        + Với pivotIdx = left + 2: [left, left + 1] và [left + 3, left + 2] (mảng 2 và 0 phần tử)
    --> cả 2 mảng con hoặc đều rơi vào base case hoặc một mảng rơi vào base case và một mảng rơi vào before base case
Cụ thể:
    quickSort(arr, 8, 10) with pivotIdx = 9: 9 10 11
        quickSort(arr, 8, 8): 9
        quickSort(arr, 10, 10): 11
*/