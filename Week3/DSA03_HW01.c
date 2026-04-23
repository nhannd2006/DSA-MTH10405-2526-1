#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 10
#define K 2

void initializeRandomArray(float arr[], int n, float min, float max);
int minIndex(float arr[], int n, int *assigns);
float mean(int freq[], int n, int numValue);
void printFreqTable(int n, int comps[]);

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int n = N;
    float arr[100];
    float min = -2*n;
    float max = 2*n;
    int assigns;
    const int TIMES[K] = {100, 1000};
    for (int k = 0; k < K; k++) {
        int freq[N + 1] = {0}; //because the worst case of finding min index is N assigns
        for (int i = 0; i < TIMES[k]; i++) {
            initializeRandomArray(arr, n, min, max);
            minIndex(arr, n, &assigns);
            freq[assigns]++;
        }
        printf("With k = %d:\nMean assignment: %f\n", TIMES[k], mean(freq, n, TIMES[k]));
        printFreqTable(n, freq);
        printf("\n");
    }
    return 0;
}

void initializeRandomArray(float arr[], int n, float min, float max) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + (rand() / (float)RAND_MAX) * (max - min);
    }
}

int minIndex(float arr[], int n, int *assigns) {
    *assigns = 0;
    if (n <= 0) return -1;
    int minIdx = 0;
    (*assigns)++;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[minIdx]) {
            minIdx = i;
            (*assigns)++;
        }
    }
    return minIdx;
}

float mean(int freq[], int n, int numValue) {
    float sum = 0;
    for (int i = 0; i <= n; i++) {
        sum += i*freq[i];
    }
    return sum/numValue;
}

void printFreqTable(int n, int freq[]) {
    printf("Frequency Table:");
    printf("\nObsers : ");
    for (int i = 0; i <= n; i++) {
        printf("%4d ", i);
    }
    printf("\nAssigns: ");
    for (int i = 0; i <= n; i++) {
        printf("%4d ", freq[i]);
    }
    printf("\n");
}

/*
With k = 100:
Mean assignment: 2.880000
Frequency Table:
Obsers :    0    1    2    3    4    5    6    7    8    9   10
Assigns:    0   15   21   39   16    4    5    0    0    0    0

With k = 1000:
Mean assignment: 2.858000
Frequency Table:
Obsers :    0    1    2    3    4    5    6    7    8    9   10
Assigns:    0  104  304  327  184   60   18    3    0    0    0
*/