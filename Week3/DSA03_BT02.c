#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define K 3

void initializeOrderedRandomArray(int arr[], int n, int min, int max);
void binarySearch(int arr[], int n, int value, int *loops);
float meanLoop(int freq[], int n, int numValue);

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int n = N, min = -1000, max = 1000;
    int arr[100];
    int loops;
    const int TIMES[K] = {100, 1000, 10000};
    for (int k = 0; k < K; k++) {
        int freq[N + 1] = {0}; //because the worst case of linear search is N steps
        for (int i = 0; i < TIMES[k]; i++) {
            initializeOrderedRandomArray(arr, n, min, max);
            int value = arr[rand() % n];
            binarySearch(arr, n, value, &loops);
            freq[loops]++;
        }
        printf("With k = %d\nMean loop = %f\n", TIMES[k], meanLoop(freq, n, TIMES[k]));
        for (int i = 0; i <= n; i++) {
            printf("%d loops - %d times, ", i, freq[i]);
        }
        printf("\n");
    }
    return 0;
}

void initializeOrderedRandomArray(int arr[], int n, int min, int max) {
    if (n == 0) return;
    arr[0] = min + rand() % (max - min + 1);
    for (int i = 1; i <= n; i++) {
        arr[i] = arr[i-1] + rand() % (max - arr[i-1] + 1);
    }
}

void binarySearch(int arr[], int n, int value, int *loops) {
    int left = 0, right = n - 1;
    *loops = 0;
    while (left <= right) {
        int mid = (left + right)/2;
        (*loops)++;
        if (value == arr[mid]) break;
        else if (value < arr[mid]) right = mid - 1;
        else left = mid + 1;
    }
}

float meanLoop(int freq[], int n, int numValue) {
    float sum = 0;
    for (int i = 0; i <= n; i++) {
        sum += i*freq[i];
    }
    return sum/numValue;
}