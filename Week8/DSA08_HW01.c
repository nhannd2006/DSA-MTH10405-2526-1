#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 10
#define K 4
#define MAXSIZE 10

void initializeRandomArray(int arr[], int n, int min, int max) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + rand() % (max - min + 1);
    }
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int partition(int arr[], int left, int right) {
    int pivotIdx = right;
    right--;
    while(1) {
        while (arr[left] < arr[pivotIdx]) left++;
        while (arr[right] > arr[pivotIdx] && left < right) right--;
        if (left >= right) {
            break;
        } else {
            swap(&arr[left], &arr[right]);
            left++;
            right--;
        }
    }
    swap(&arr[left], &arr[pivotIdx]);
    return left;
}

void quickSort(int arr[], int n, int left, int right, int *count) {
    if (left >= right) {
        return;
    }
    else {
        (*count)++;
        int pivotIdx = partition(arr, left, right);
        quickSort(arr, n, left, pivotIdx - 1, count);
        quickSort(arr, n, pivotIdx + 1, right, count);
    }
}

float mean(int freq[], int valueCount, int totalFreq) {
    float sum = 0;
    for (int i = 0; i <= valueCount; i++) {
        sum += i*freq[i];
    }
    return sum/totalFreq;
}

void printFreqTable(int freqCount[], int valueCount, int totalFreq) {
    int len = log10(totalFreq) + 1;
    printf("Frequency Table:");
    printf("\nObsers: ");
    for (int i = 0; i <= valueCount; i++) {
        printf("%*d ", len, i);
    }
    printf("\nCount : ");
    for (int i = 0; i <= valueCount; i++) {
        printf("%*d ", len, freqCount[i]);
    }
    printf("\n");
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int n = N;
    int min = -1000, max = 1000;
    const int TIMES[K] = {10, 100, 1000, 10000};
    int arr[N];
    for (int k = 0; k < K; k++) {
        int freqCount[MAXSIZE + 1] = {0};
        for (int i = 0; i < TIMES[k]; i++) {
            int count = 0;
            initializeRandomArray(arr, n, min, max);
            quickSort(arr, n, 0, n - 1, &count);
            freqCount[count]++;
        }
        float meanComps = mean(freqCount, MAXSIZE, TIMES[k]);
        printf("With k = %d:\n", TIMES[k]);
        printf("Mean count = %f\n", meanComps);
        printFreqTable(freqCount, MAXSIZE, TIMES[k]);
        printf("\n");
    }
    return 0;
}

/*
With k = 10:
Mean count = 6.600000
Frequency Table:
Obsers:  0  1  2  3  4  5  6  7  8  9 10
Count :  0  0  0  0  0  0  4  6  0  0  0

With k = 100:
Mean count = 6.310000
Frequency Table:
Obsers:   0   1   2   3   4   5   6   7   8   9  10
Count :   0   0   0   0   0   7  59  30   4   0   0

With k = 1000:
Mean count = 6.332000
Frequency Table:
Obsers:    0    1    2    3    4    5    6    7    8    9   10
Count :    0    0    0    0    0   96  511  358   35    0    0

With k = 10000:
Mean count = 6.327300
Frequency Table:
Obsers:     0     1     2     3     4     5     6     7     8     9    10
Count :     0     0     0     0     0   977  5121  3554   348     0     0

*/