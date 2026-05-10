/*
Viết hàm đệ qui để tính trung bình cộng các phần tử trong mảng có n phần tử.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5

void initializeRandomArray(float arr[], int n, float min, float max) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + (rand() / (float)RAND_MAX) * (max - min);
    }
}

void printArray(float arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");
}

float average(float arr[], int n) {
    float avg = 0;
    if (n == 0) return 0;
    if (n == 1) return arr[0]/n;
    avg = (average(arr, n - 1)*(n - 1) + arr[n - 1])/n;
    return avg;    
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int n = N;
    float arr[N];
    initializeRandomArray(arr, n, 0, 100);
    printArray(arr, n);
    printf("Average of array: %f\n", average(arr, n));
    return 0;
}

/*
91.946167 1.864681 6.857509 85.406044 25.772881 
Average of array: 42.369457
*/