#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define K 3
#define N 10

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubbleSort(int arr[], int n, int *comps, int *swaps) {
    *comps = 0; *swaps = 0;
    int sorted = 0;
    int unsortedEnd = n - 1;
    while (!sorted) {
        sorted = 1;
        for (int i = 0; i < unsortedEnd; i++) {
            (*comps)++;
            if (arr[i] > arr[i + 1]) {
                sorted = 0;
                (*swaps)++;
                swap(&arr[i], &arr[i + 1]);
            }
        }
        unsortedEnd--;
    }
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

void printFreqTable(int n, int comps[], int swaps[]) {
    printf("Frequency Table:");
    printf("\nObser: ");
    for (int i = 1; i < n; i++) {
        printf("%4d ", i);
    }
    printf("\ncomps: ");
    for (int i = 1; i < n; i++) {
        printf("%4d ", comps[i]);
    }
    printf("\nswaps: ");
    for (int i = 1; i < n; i++) {
        printf("%4d ", swaps[i]);
    }
    printf("\n");
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int n = N, min = -1000, max = 1000;
    int arr[100];
    int comps, swaps;
    const int TIMES[K] = {100, 1000, 10000};
    for (int k = 0; k < K; k++) {
        //because the worst case of Bubble Sort algorithm is N(N - 1)/2 steps
        int compsFreqTable[N*(N-1)/2 + 1] = {0};
        int swapsFreqTable[N*(N-1)/2 + 1] = {0};
        for (int i = 0; i < TIMES[k]; i++) {
            initializeArray(arr, n, min, max);
            bubbleSort(arr, n, &comps, &swaps);
            compsFreqTable[comps]++;
            swapsFreqTable[swaps]++;
        }
        printf("With k = %d:\nMean comparison = %f\nMean swap = %f\n", TIMES[k], mean(compsFreqTable, n*(n-1)/2, TIMES[k]), mean(swapsFreqTable, n*(n-1)/2, TIMES[k]));
        printFreqTable(n*(n - 1)/2 + 1, compsFreqTable, swapsFreqTable);
        printf("\n");
    }
    return 0;
}

/*
With k = 100:
Mean comparison = 42.049999
Mean swap = 21.959999
Frequency Table:
Obser:    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39   40   41   42   43   44   45
comps:    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    1    0    0    0    0    0    2    0    0    0    0    6    0    0    0   14    0    0   26    0   22   29
swaps:    0    0    0    0    0    0    0    2    1    0    2    0    2    2    3    5    3    3    6    6    5    8    5    9   11    7    9    5    3    2    0    1    0    0    0    0    0    0    0    0    0    0    0    0    0

With k = 1000:
Mean comparison = 42.105000
Mean swap = 22.468000
Frequency Table:
Obser:    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39   40   41   42   43   44   45
comps:    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    5    0    0    0    0    0   20    0    0    0    0   75    0    0    0  144    0    0  208    0  252  296
swaps:    0    0    0    1    0    1    2    1    1    7   11   12   27   16   30   38   48   62   54   60   50   70   75   74   58   57   51   40   45   34   23   20   11   11    4    2    2    0    1    0    1    0    0    0    0

With k = 10000:
Mean comparison = 41.925098
Mean swap = 22.368601
Frequency Table:
Obser:    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39   40   41   42   43   44   45
comps:    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    1    0    0    0    0    0    0   39    0    0    0    0    0  257    0    0    0    0  789    0    0    0 1535    0    0 2193    0 2368 2818
swaps:    0    0    1    1    3    4   24   19   43   61   97  113  201  281  311  397  439  507  587  619  652  676  704  710  611  586  516  436  359  316  226  164  118   80   56   32   20   22    4    1    2    1    0    0    0
*/