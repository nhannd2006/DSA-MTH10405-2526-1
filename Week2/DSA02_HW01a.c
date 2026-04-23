#include <stdio.h>
#include <stdlib.h>

const double EPSILON = 1e-6;

void insertOrderedArray(double arr[], int *n, double value);
void insertArray(double arr[], int *n, double value, int index);

int main() {
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);
    double *arr = (double *) malloc((n+1)*sizeof(double));
    printf("Enter elements of ordered array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &arr[i]);
    }
    double value;
    printf("Enter value to insert: ");
    scanf("%lf", &value);
    insertOrderedArray(arr, &n, value);
    printf("Array after inserting:\narr[] = ");
    for (int i = 0; i < n; i++) {
        printf("%lf ", arr[i]);
    }
    free(arr);
    return 0;
}

void insertArray(double arr[], int *n, double value, int index) {
    (*n)++;
    for (int i = *n - 1; i > index; i--) {
        arr[i] = arr[i-1];
    }
    arr[index] = value;
}

void insertOrderedArray(double arr[], int *n, double value) {
    int index = -1;
    for (int i = 0; i < *n; i++) {
        if (arr[i] - value > EPSILON) {
            index = i;
            break;
        }
    }
    if (index == -1) index = *n;
    insertArray(arr, n, value, index);
}