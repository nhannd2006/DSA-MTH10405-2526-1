#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 10
#define K 4

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

void selectionSort(int arr[], int n, int *comps, int *swaps) {
    *comps = 0;
    *swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            (*comps)++;
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            swap(&arr[i], &arr[minIdx]);
            (*swaps)++;
        }
    }
}

float mean(int freq[], int n, int numValue) {
    float sum = 0;
    for (int i = 0; i <= n; i++) {
        sum += i*freq[i];
    }
    return sum/numValue;
}

void printFreqTable(int n, int swaps[], int comps[], int max) {
    const int LEN = log10(max);
    printf("Frequency Table:");
    printf("\nObsers: ");
    for (int i = 0; i <= n; i++) {
        printf("%*d ", LEN, i);
    }
    printf("\nComps : ");
    for (int i = 0; i <= n; i++) {
        printf("%*d ", LEN, comps[i]);
    }
    printf("\nSwaps : ");
    for (int i = 0; i <= n; i++) {
        printf("%*d ", LEN, swaps[i]);
    }
    printf("\n");
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int min = -1000, max = 1000;
    int n = N;
    int arr[N];
    int comps, swaps;
    int TIMES[K] = {100, 1000, 10000, 100000};
    for (int k = 0; k < K; k++) {
        //because the worst case of Selection Sort Algorithm is N*(N-1)/2 steps
        int compFreq[N*(N - 1)/2 + 1] = {0};
        int swapFreq[N*(N - 1)/2 + 1] = {0};
        for (int i = 0; i < TIMES[k]; i++) {
            initializeRandomArray(arr, n, min, max);
            selectionSort(arr, n, &comps, &swaps);
            compFreq[comps]++;
            swapFreq[swaps]++;
        }
        printf("With k = %d:\nMean comparison = %f\nMean swap = %f\n", TIMES[k], mean(compFreq, n*(n-1)/2, TIMES[k]), mean(swapFreq, n*(n-1)/2, TIMES[k]));
        printFreqTable(n*(n - 1)/2, compFreq, swapFreq, TIMES[k]);
        printf("\n");
    }
    return 0;
}

/*
With k = 100:
Mean comparison = 45.000000
Mean swap = 7.180000
Frequency Table:
Obsers:  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45
Comps :  0  0  0  0  2  4 24 30 24 16  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
Swaps :  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 100

With k = 1000:
Mean comparison = 45.000000
Mean swap = 7.029000
Frequency Table:
Obsers:   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45
Comps :   0   0   0   5  21  70 193 344 289  78   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
Swaps :   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0 1000

With k = 10000:
Mean comparison = 45.000000
Mean swap = 7.076500
Frequency Table:
Obsers:    0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39   40   41   42   43   44   45
Comps :    0    0    5   29  156  781 1960 3214 2814 1041    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
Swaps :    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0 10000

With k = 100000:
Mean comparison = 45.000000
Mean swap = 7.070440
Frequency Table:
Obsers:     0     1     2     3     4     5     6     7     8     9    10    11    12    13    14    15    16    17    18    19    20    21    22    23    24    25    26    27    28    29    30    31    32    33    34    35    36    37    38    39    40    41    42    43    44    45
Comps :     0     2    24   266  1720  7521 19873 32242 28389  9963     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0
Swaps :     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0 100000
*/