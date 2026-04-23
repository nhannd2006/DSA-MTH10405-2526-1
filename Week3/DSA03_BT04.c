#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 10
#define K 3

void initializeRandomArray(int arr[], int n, int min, int max);
void deleteArray(int arr[], int *n, int index, int *assigns);
float meanAssignment(int freq[], int n, int numValue);

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int n = N, min = -1000, max = 1000;
    int arr[100];
    int assigns;
    const int TIMES[K] = {100, 1000, 10000};
    for (int k = 0; k < K; k++) {
        int freq[N] = {0}; //because the worst case of deletion is N - 1 steps
        for (int i = 0; i < TIMES[k]; i++) {
            int nTemp = n;
            initializeRandomArray(arr, nTemp, min, max);
            int index = rand() % nTemp;
            deleteArray(arr, &nTemp, index, &assigns);
            freq[assigns]++;
        }
        printf("With k = %d:\nMean assignment = %f\n", TIMES[k], meanAssignment(freq, n, TIMES[k]));
        for (int i = 0; i < n; i++) {
            printf("%d assigns - %d times, ", i, freq[i]);
        }
        printf("\n");
    }
    return 0;
}

void initializeRandomArray(int arr[], int n, int min, int max) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + rand() % (max - min + 1);
    }
}

void deleteArray(int arr[], int *n, int index, int *assigns) {
    *assigns = 0;
    if (index < 0 || index >= *n) return;
    (*n)--;
    for (int i = index; i < *n; i++) {
        arr[i] = arr[i+1];
        (*assigns)++;
    }
}

float meanAssignment(int freq[], int n, int numValue) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += i*freq[i];
    }
    return sum/numValue;
}