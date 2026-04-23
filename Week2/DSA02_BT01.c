#include <stdio.h>
#include <stdlib.h>

void insertOrderedArray(int arr[], int *n, int value);
void insertArray(int arr[], int *n, int value, int index);

int main() {
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);
    int *arr = (int *) malloc((n+1)*sizeof(int));
    printf("Enter elements of ordered array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int value;
    printf("Enter value to insert: ");
    scanf("%d", &value);
    insertOrderedArray(arr, &n, value);
    printf("Array after inserting:\narr[] = ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    free(arr);
    return 0;
}

void insertArray(int arr[], int *n, int value, int index) {
    (*n)++;
    for (int i = *n - 1; i > index; i--) {
        arr[i] = arr[i-1];
    }
    arr[index] = value;
}

void insertOrderedArray(int arr[], int *n, int value) {
    int index = -1;
    for (int i = 0; i < *n; i++) {
        if (arr[i] > value) {
            index = i;
            break;
        }
    }
    if (index == -1) index = *n;
    insertArray(arr, n, value, index);
}