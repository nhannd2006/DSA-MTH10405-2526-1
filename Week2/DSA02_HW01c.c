#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double EPSILON = 1e-6;

int binarySearch(double arr[], int n, double value);

int main() {
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);
    double *arr = (double *) malloc(n * sizeof(double));
    printf("Enter elements of ordered array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &arr[i]);
    }
    double value;
    printf("Enter value to search: ");
    scanf("%lf", &value);
    int index = binarySearch(arr, n, value);
    if (index == -1) printf("Not found!");
    else printf("%d", index);
    free(arr);
    return 0;
}

int binarySearch(double arr[], int n, double value) {
    int left = 0;
    int right = n - 1;
    int index = -1;
    while (left <= right) {
        int mid = (left + right)/2;
        if (fabs(arr[mid] - value) < EPSILON) return mid;
        else if (arr[mid] - value > EPSILON) right = mid - 1;
        else left = mid + 1;
    }
    return index;
}