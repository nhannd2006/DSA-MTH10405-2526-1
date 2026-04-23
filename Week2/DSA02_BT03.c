#include <stdio.h>
#include <stdlib.h>

int binarySearch(int arr[], int n, int value);

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
    int index = binarySearch(arr, n, value);
    if (index == -1) printf("Not found!");
    else printf("%d", index);
    free(arr);
    return 0;
}

int binarySearch(int arr[], int n, int value) {
    int left = 0;
    int right = n - 1;
    int index = -1;
    while (left <= right) {
        int mid = (left + right)/2;
        if (arr[mid] == value) {
            index = mid;
            break;
        } else if (value < arr[mid]) right = mid - 1;
        else left = mid + 1;
    }
    return index;
}