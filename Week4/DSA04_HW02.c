#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 10
#define K 1
#define MAXSIZE (N*(N - 1)/2 + (N - 1))

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

void copyArray(int arr[], int n, int newArr[]) {
    for (int i = 0; i < n; i++) {
        newArr[i] = arr[i];
    }
}

void deleteArray(int arr[], int *n, int index, int *assigns) {
    for (int i = index; i < *n - 1; i++) {
        arr[i] = arr[i + 1];
        (*assigns)++;
    }
    (*n)--;
}

int removeDuplicates_1(int arr[], int *n, int *comps, int *assigns) {
    *comps = 0; *assigns = 0;
    for (int i = *n - 1; i > 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            (*comps)++;
            if (arr[i] == arr[j]) {
                deleteArray(arr, n, i, assigns);
                break;
            }
        }
    }
    return (*comps + *assigns);
}

int removeDuplicate_2(int arr[], int *n, int *comps, int *swaps, int *assigns) {
    *comps = 0; *swaps = 0; *assigns = 0;
    int sorted = 0;
    int unsortedEnd = *n - 1;
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
    for (int i = *n - 1; i > 0; i--) {
        (*comps)++;
        if (arr[i] == arr[i - 1]) {
            deleteArray(arr, n, i - 1, assigns);
        }
    }
    return (*comps + *swaps + *assigns);
}

float mean(int freq[], int valueCount, int totalFreq) {
    float sum = 0;
    for (int i = 0; i <= valueCount; i++) {
        sum += i*freq[i];
    }
    return sum/totalFreq;
}

void printFreqTable_1(int freqComps_1[], int freqAssigns_1[], int valueCount, int totalFreq) {
    int len = log10(totalFreq) + 1;
    printf("Frequency Table:");
    printf("\nObsers: ");
    for (int i = 0; i <= valueCount; i++) {
        printf("%*d ", len, i);
    }
    printf("\nComps : ");
    for (int i = 0; i <= valueCount; i++) {
        printf("%*d ", len, freqComps_1[i]);
    }
    printf("\nAssign: ");
    for (int i = 0; i <= valueCount; i++) {
        printf("%*d ", len, freqAssigns_1[i]);
    }
    printf("\n");
}

void printFreqTable_2(int freqComps_2[], int freqSwaps_2[], int freqAssigns_2[], int valueCount, int totalFreq) {
    int len = log10(totalFreq) + 1;
    printf("Frequency Table:");
    printf("\nObsers: ");
    for (int i = 0; i <= valueCount; i++) {
        printf("%*d ", len, i);
    }
    printf("\nComps : ");
    for (int i = 0; i <= valueCount; i++) {
        printf("%*d ", len, freqComps_2[i]);
    }
    printf("\nSwaps : ");
    for (int i = 0; i <= valueCount; i++) {
        printf("%*d ", len, freqSwaps_2[i]);
    }
    printf("\nAssign: ");
    for (int i = 0; i <= valueCount; i++) {
        printf("%*d ", len, freqAssigns_2[i]);
    }
    printf("\n");
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int comps_1 = 0, assigns_1 = 0;
    int comps_2 = 0, swaps_2 = 0, assigns_2 = 0;
    int n = N, newN = N;
    int min = 1, max = N - 1; // dùng nguyên lý Dirichlet để ép cho mảng luôn tồn tại ít nhất 2 phần tử trùng nhau
    const int TIMES[K] = {100};
    int arr[N], newArr[N];
    for (int k = 0; k < K; k++) {
        int freqComps_1[MAXSIZE + 1] = {0};
        int freqAssigns_1[MAXSIZE + 1] = {0};
        int freqComps_2[MAXSIZE + 1] = {0};
        int freqSwaps_2[MAXSIZE + 1] = {0};
        int freqAssigns_2[MAXSIZE + 1] = {0};
        int freq1[2*MAXSIZE + 1] = {0};
        int freq2[2*MAXSIZE + 1] = {0};        
        for (int i = 0; i < TIMES[k]; i++) {
            initializeRandomArray(arr, n, min, max);
            copyArray(arr, n, newArr);
            int steps1 = removeDuplicates_1(arr, &n, &comps_1, &assigns_1);
            freqComps_1[comps_1]++;
            freqAssigns_1[assigns_1]++;
            int steps2 = removeDuplicate_2(newArr, &newN, &comps_2, &swaps_2, &assigns_2);
            freqComps_2[comps_2]++;
            freqSwaps_2[swaps_2]++;
            freqAssigns_2[assigns_2]++;
            freq1[steps1]++;
            freq2[steps2]++;
            n = N; newN = N;
        }
        float meanSteps1 = mean(freq1, 2*MAXSIZE, TIMES[k]);
        float meanSteps2 = mean(freq2, 2*MAXSIZE, TIMES[k]);        
        float meanComps_1 = mean(freqComps_1, MAXSIZE, TIMES[k]);
        float meanAssigns_1 = mean(freqAssigns_1, MAXSIZE, TIMES[k]);
        float meanComps_2 = mean(freqComps_2, MAXSIZE, TIMES[k]);
        float meanSwaps_2 = mean(freqSwaps_2, MAXSIZE, TIMES[k]);
        float meanAssigns_2 = mean(freqAssigns_2, MAXSIZE, TIMES[k]);
        printf("With k = %d:\n", TIMES[k]);
        printf("1:\nMean comps = %f, Mean assigns = %f\n", meanComps_1, meanAssigns_1);
        printf("Mean steps of Case 1 = %f\n", meanSteps1);
        printFreqTable_1(freqComps_1, freqAssigns_1, MAXSIZE, TIMES[k]);
        printf("2:\nMean comps = %f, Mean swaps = %f, Mean assigns = %f\n", meanComps_2, meanSwaps_2, meanAssigns_2);
        printf("Mean steps of Case 2 = %f\n", meanSteps2);
        printFreqTable_2(freqComps_2, freqSwaps_2, freqAssigns_2, MAXSIZE, TIMES[k]);
        printf("\n");
    }
    return 0;
}

/*OUTPUT:
With k = 100:
1:
Mean comps = 33.580002, Mean assigns = 4.740000
Mean steps of Case 1 = 38.320000
Frequency Table:
Obsers:   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  48  49  50  51  52  53  54
Comps :   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   1   1   1   0   1   0   7   2   6   7   6   9   8   5   9   8  10   4   7   3   1   2   1   1   0   0   0   0   0   0   0   0   0   0
Assign:  11   4   8  13  13  11  11  13   7   5   0   2   1   0   0   0   1   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
2:
Mean comps = 49.619999, Mean swaps = 19.959999, Mean assigns = 13.040000
Mean steps of Case 2 = 82.620003
Frequency Table:
Obsers:   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  48  49  50  51  52  53  54
Comps :   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   1   0   0   0   0   0   5   0   0   0   0  12   0   0   0  23   0   0  21   0  21  17
Swaps :   0   0   0   1   0   0   0   1   1   0   3   0   3   4   3   5  10   3   3  10   7   9   4   3   7   6   3   2   6   1   3   1   0   0   1   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
Assign:   0   0   1   0   1   3   3   3   5   3   5   9   7  13  10   7   9   8   4   4   3   2   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
*/