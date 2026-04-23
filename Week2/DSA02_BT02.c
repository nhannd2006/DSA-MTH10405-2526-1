#include <stdio.h>
#include <stdlib.h>

int orderedLinearSearch(int arr[], int n, int value);

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
    int index = orderedLinearSearch(arr, n, value);
    if (index == -1) printf("Not found!");
    else printf("%d", index);
    free(arr);
    return 0;
}

int orderedLinearSearch(int arr[], int n, int value) {
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] == value) {
            index = i;
            break;
        } else if (arr[i] > value) break;
    }
    return index;
}