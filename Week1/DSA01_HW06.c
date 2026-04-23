#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void insertNumsToArray(float **arr, int *n, float nums[], int idxs[], int k);

int main() {
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);
    float *arr = (float *) malloc(n * sizeof(float));
    printf("Enter decimal elements of array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%f", &arr[i]);
    }
    int k;
    printf("Enter the number of numbers to insert: ");
    scanf("%d", &k);
    float *nums = (float *) malloc(k * sizeof(float));
    int *index = (int *) malloc(k * sizeof(int));
    printf("Enter numbers to insert and corresponding indexes:\n");
    for (int i = 0; i < k; i++) {
        scanf("%f%d", &nums[i], &index[i]);
    }
    insertNumsToArray(&arr, &n, nums, index, k);
    free(nums);
    free(index);
    printf("Array after inserting numbers: ");
    for (int i = 0; i < n; i++) {
        if (fabs(arr[i] - (int)arr[i]) < 1e-6) printf("%.1f ", arr[i]);
        else printf("%g ", arr[i]);
    }
    free(arr);
    return 0;
}

void insertNumsToArray(float **arr, int *n, float nums[], int index[], int k) {
    for (int i = 0; i < k; i++) {
        (*n)++;
        *arr = (float *) realloc(*arr, (*n) * sizeof(float));
        for (int j = *n - 1; j > index[i] + i; j--) {
            (*arr)[j] = (*arr)[j - 1];
        }
        (*arr)[index[i] + i] = nums[i];
    }
}