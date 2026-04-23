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

void copyArray(int arr[], int n, int nArr[]) {
    for (int i = 0; i < n; i++) {
        nArr[i] = arr[i];
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
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
void insertionSort(int arr[], int n, int *comps, int *shifts) {
    *comps = 0;
    *shifts = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int pos = i - 1;
        while (pos >= 0) {
            (*comps)++;
            if (arr[pos] <= key) break;
            arr[pos + 1] = arr[pos];
            pos--;
            (*shifts)++;
        }
        arr[pos + 1] = key;
    }
}

float mean(int freq[], int n, int numValue) {
    float sum = 0;
    for (int i = 0; i <= n; i++) {
        sum += i*freq[i];
    }
    return sum/numValue;
}

void printFreqTable1(int n, int comps[], int swaps[], int max) {
    const int LEN = log10(max) + 1;
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

void printFreqTable2(int n, int comps[], int shifts[], int max) {
    const int LEN = log10(max) + 1;
    printf("Frequency Table:");
    printf("\nObsers: ");
    for (int i = 0; i <= n; i++) {
        printf("%*d ", LEN, i);
    }
    printf("\nComps : ");
    for (int i = 0; i <= n; i++) {
        printf("%*d ", LEN, comps[i]);
    }
    printf("\nShifts: ");
    for (int i = 0; i <= n; i++) {
        printf("%*d ", LEN, shifts[i]);
    }
    printf("\n");
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int min = -1000, max = 1000;
    int n = N;
    int arr[N], nArr[N];
    int selectComps, selectSwaps;
    int insertComps, insertShifts;
    int TIMES[K] = {100, 1000, 10000, 100000};
    for (int k = 0; k < K; k++) {
        //because the worst case of Selection & Insertion Sort Algorithm is N*(N-1)/2 steps
        int selectCompFreq[N*(N - 1)/2 + 1] = {0};
        int selectSwapFreq[N*(N - 1)/2 + 1] = {0};
        int insertCompFreq[N*(N - 1)/2 + 1] = {0};
        int insertShiftFreq[N*(N - 1)/2 + 1] = {0};
        for (int i = 0; i < TIMES[k]; i++) {
            initializeRandomArray(arr, n, min, max);
            copyArray(arr, n, nArr);
            selectionSort(arr, n, &selectComps, &selectSwaps);
            selectCompFreq[selectComps]++;
            selectSwapFreq[selectSwaps]++;
            insertionSort(nArr, n, &insertComps, &insertShifts);
            insertCompFreq[insertComps]++;
            insertShiftFreq[insertShifts]++;
        }
        float meanSelectComps = mean(selectCompFreq, n*(n-1)/2, TIMES[k]);
        float meanSelectSwaps = mean(selectSwapFreq, n*(n-1)/2, TIMES[k]);
        float meanInsertComps = mean(insertCompFreq, n*(n-1)/2, TIMES[k]);
        float meanInsertShifts = mean(insertShiftFreq, n*(n-1)/2, TIMES[k]);
        printf("With k = %d:\n", TIMES[k]);
        printf("Mean selection comps = %f, Mean selection swaps = %f\n", meanSelectComps, meanSelectSwaps);
        printf("Mean insertion comps = %f, Mean insertion shifts = %f\n", meanInsertComps, meanInsertShifts);
        printf("Mean selection total steps = %f\n", meanSelectComps + meanSelectSwaps);
        printf("Mean insertion total steps = %f\n", meanInsertComps + meanInsertShifts);
        printFreqTable1(n*(n - 1)/2, selectCompFreq, selectSwapFreq, TIMES[k]);
        printFreqTable2(n*(n - 1)/2, insertCompFreq, insertShiftFreq, TIMES[k]);        
        printf("\n");
    }
    return 0;
}

/*
With k = 100:
Mean selection comps = 45.000000, Mean selection swaps = 6.920000
Mean insertion comps = 29.180000, Mean insertion shifts = 21.969999
Mean selection total steps = 51.919998
Mean insertion total steps = 51.150002
Frequency Table:
Obsers:   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45
Comps :   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0 100
Swaps :   0   0   0   0   1   7  31  31  20  10   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
Frequency Table:
Obsers:   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45
Comps :   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   1   0   0   0   1   3   5   5   3   2   5   4   8   7   4   4  11   9   7   4   4   4   7   2   0   0   0   0   0   0   0
Shifts:   0   0   0   0   0   0   0   1   0   0   0   1   6   3   2   2   4   4   5   4   7   5   3   6  10   8   9   3   3   5   2   5   2   0   0   0   0   0   0   0   0   0   0   0   0   0

With k = 1000:
Mean selection comps = 45.000000, Mean selection swaps = 7.027000
Mean insertion comps = 29.427999, Mean insertion shifts = 22.323999
Mean selection total steps = 52.027000
Mean insertion total steps = 51.751999
Frequency Table:
Obsers:    0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39   40   41   42   43   44   45
Comps :    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0 1000
Swaps :    0    0    0    2   19   75  207  345  255   97    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0
Frequency Table:
Obsers:    0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39   40   41   42   43   44   45
Comps :    0    0    0    0    0    0    0    0    0    0    0    0    0    0    2    0    3    1    4    4   17   22   41   44   42   45   77   62   59   98   62   63   76   53   47   50   39   29   28   16    4    6    4    1    1    0
Shifts:    0    0    0    0    0    0    2    0    0    7    2    6    9   28   30   38   31   47   55   70   69   62   71   63   49   64   52   46   50   46   32   22   18   11    8    4    3    3    1    1    0    0    0    0    0    0

With k = 10000:
Mean selection comps = 45.000000, Mean selection swaps = 7.061600
Mean insertion comps = 29.526899, Mean insertion shifts = 22.438700
Mean selection total steps = 52.061600
Mean insertion total steps = 51.965599
Frequency Table:
Obsers:     0     1     2     3     4     5     6     7     8     9    10    11    12    13    14    15    16    17    18    19    20    21    22    23    24    25    26    27    28    29    30    31    32    33    34    35    36    37    38    39    40    41    42    43    44    45
Comps :     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0 10000
Swaps :     0     0     0    19   179   715  2067  3259  2796   965     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0     0
Frequency Table:
Obsers:     0     1     2     3     4     5     6     7     8     9    10    11    12    13    14    15    16    17    18    19    20    21    22    23    24    25    26    27    28    29    30    31    32    33    34    35    36    37    38    39    40    41    42    43    44    45
Comps :     0     0     0     0     0     0     0     0     0     0     0     0     1     1     3    12    20    40    61    83   140   207   294   378   441   522   579   673   749   716   761   747   700   665   556   435   357   304   189   145   106    52    44    14     2     3
Shifts:     0     0     0     0     2     1     8    11    19    31    67    79   126   182   240   323   427   466   500   543   702   652   613   695   716   643   580   519   455   363   302   220   154   122    81    74    30    29    10     9     5     1     0     0     0     0 

With k = 100000:
Mean selection comps = 45.000000, Mean selection swaps = 7.071780
Mean insertion comps = 29.572990, Mean insertion shifts = 22.504419
Mean selection total steps = 52.071781
Mean insertion total steps = 52.077408
Frequency Table:
Obsers:      0      1      2      3      4      5      6      7      8      9     10     11     12     13     14     15     16     17     18     19     20     21     22     23     24     25     26     27     28     29     30     31     32     33     34     35     36     37     38     39     40     41     42     43     44     45
Comps :      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0 100000
Swaps :      0      1     30    295   1771   7403  19803  32262  28434  10001      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0
Frequency Table:
Obsers:      0      1      2      3      4      5      6      7      8      9     10     11     12     13     14     15     16     17     18     19     20     21     22     23     24     25     26     27     28     29     30     31     32     33     34     35     36     37     38     39     40     41     42     43     44     45
Comps :      0      0      0      0      0      0      0      0      0      0      0      3      7     29     44    106    230    360    639    930   1437   2048   2653   3442   4407   5167   6102   6612   7198   7551   7582   7364   7053   6428   5562   4612   3753   2948   2201   1453    959    581    324    139     62     14
Shifts:      0      0      0      7     12     24     59    116    242    357    601    899   1324   1786   2329   2982   3813   4541   5182   5807   6284   6622   6929   6977   6653   6361   5910   5141   4423   3806   3020   2345   1792   1333    919    559    392    217    117     65     36     10      6      1      1      0
*/