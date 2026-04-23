#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

int caculateNegativeSum(int arr[], int n, int *assigns) {
    *assigns = 0;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            sum += arr[i];
            (*assigns)++;
        }
    }
    return sum;
}

void initializeArray(int arr[], int n, int min, int max) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + rand() % (max - min + 1);
    }
}

float mean(int freq[], int n, int numValue) {
    float sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i*freq[i];
    }
    return sum/numValue;
}

void printFreqTable(int n, int assigns[]) {
    printf("Frequency Table:");
    printf("\nObsers:  ");
    for (int i = 0; i <= n; i++) {
        printf("%4d ", i);
    }
    printf("\nAssigns: ");
    for (int i = 0; i <= n; i++) {
        printf("%4d ", assigns[i]);
    }
    printf("\n");
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int n = N, min = -100, max = 100;
    int arr[100];
    int assigns;
    const int K = 1000;
    //because the worst case of Negative Sums algorithm is N steps
    int freq[N + 1] = {0};
    for (int i = 0; i < K; i++) {
        initializeArray(arr, n, min, max);
        caculateNegativeSum(arr, n, &assigns);
        freq[assigns]++;
    }
    printf("With k = %d:\nMean assignment = %f\n", K, mean(freq, n, K));
    printFreqTable(n, freq);
    printf("\n");
    return 0;
}


/*
With k = 1000:
Mean assignment = 4.880000
Frequency Table:
Obsers:     0    1    2    3    4    5    6    7    8    9   10
Assigns:    2   10   52  139  205  226  215  111   29   10    1
*/
