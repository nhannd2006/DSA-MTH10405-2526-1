#include <stdio.h>
#include <stdlib.h>

int binarySearch(int arr[], int n, int value, int *steps);
int orderedLinearSearch(int arr[], int n, int value, int *steps);

int main() {
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);
    int *arr = (int *) malloc(n * sizeof(int));
    printf("Enter elements of ordered array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int value;
    printf("Enter value to search: ");
    scanf("%d", &value);
    int compsLinear = 0;
    orderedLinearSearch(arr, n, value, &compsLinear);
    printf("stepLinear = %d\n", compsLinear);
    int compsBinary = 0;
    binarySearch(arr, n, value, &compsBinary);
    printf("stepBinary = %d\n", compsBinary);
    free(arr);
    return 0;
}

int orderedLinearSearch(int arr[], int n, int value, int *steps) {
    int index = -1;
    for (int i = 0; i < n; i++) {
        (*steps)++;
        if (arr[i] == value) return i;
        else if (arr[i] > value) break;
    }
    return index;
}

int binarySearch(int arr[], int n, int value, int *steps) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        (*steps)++;
       int mid = (left + right) / 2;
        if (arr[mid] == value) return mid;
        else if (arr[mid] > value) right = mid - 1;
        else left = mid + 1;
    }
    return -1;
}