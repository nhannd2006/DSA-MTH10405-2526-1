#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int findNearestValue(float arr[], int n, int value);

int main() {
    int n;
    printf("Enter size of array: ");
    scanf("%d",&n);

    float *arr = (float *) malloc(n*sizeof(float));
    printf("Enter elements of array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%f",&arr[i]);
    }

    int value;
    printf("Enter value: ");
    scanf("%d",&value);

    int index = findNearestValue(arr, n, value);
    printf("%g at index %d nearest to %d", arr[index], index, value);
    free(arr);
    return 0;
}

int findNearestValue(float arr[], int n, int value) {
    int index = -1;
    if (n != 0) {
        float minDistance = fabs(arr[0] - value);
        index = 0;
        for (int i = 1; i < n; i++) {
            if (minDistance > fabs(arr[i] - value)) {
                minDistance = fabs(arr[i] - value);
                index = i;
            }
        }
    }
    return index;
}