#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double EPSILON = 1e-6;

int orderedLinearSearch(double arr[], int n, double value);

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
    int index = orderedLinearSearch(arr, n, value);
    if (index == -1) printf("Not found!");
    else printf("%d", index);
    free(arr);
    return 0;
}

int orderedLinearSearch(double arr[], int n, double value) {
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (fabs(arr[i] - value) < EPSILON) return i;
        else if (arr[i] > value) break;
    }
    return index;
}