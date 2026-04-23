#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 4
#define K 10000

void initializeRandomArray(int arr[], int n, int min, int max) {
    for (int i = 0; i < n; i++) arr[i] = min + rand() % (max - min + 1);
}

int findMaxProduct(int arr[], int n, int *steps, int *assigns) {
    (*steps) = 0, (*assigns) = 0;
    if (n < 2) return 0;
    int max = arr[0]*arr[1];
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            (*steps)++;
            if (arr[i]*arr[j] > max) {
                max = arr[i]*arr[j];
                (*assigns)++;
            }
        }
    }
    return max;
}

float mean(int freq[], int valueCount, int totalFreq) {
    float sum = 0;
    for (int i = 0; i <= valueCount; i++) {
        sum += i*freq[i];
    }
    return sum/totalFreq;
}

void printFreqTable(int steps[], int assigns[], int valueCount, int totalFreq) {
    int len = log10(totalFreq) + 1;
    printf("Frequency Table:");
    printf("\nObsers : ");
    for (int i = 0; i <= valueCount; i++) {
        printf("%*d ", len, i);
    }
    printf("\nSteps  : ");
    for (int i = 0; i <= valueCount; i++) {
        printf("%*d ", len, steps[i]);
    }    
    printf("\nAssigns: ");
    for (int i = 0; i <= valueCount; i++) {
        printf("%*d ", len, assigns[i]);
    }    
    printf("\n");
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int min = 1, max = 100;
    int n = N;
    int arr[N];
    int steps = 0, assigns = 0;
    int freqSteps[N*(N - 1)/2 + 1] = {0}; //because the worst case of finding max product between 2 elements is N * (N - 1)/2 steps.
    int freqAssigns[N*(N - 1)/2 + 1] = {0};
    for (int k = 0; k < K; k++) {
        initializeRandomArray(arr, n, min, max);
        findMaxProduct(arr, n, &steps, &assigns);
        freqSteps[steps]++;
        freqAssigns[assigns]++;
    }
    float meanSteps = mean(freqSteps, N*(N - 1)/2, K);
    float meanAssigns = mean(freqAssigns, N*(N - 1)/2, K);
    printf("With k = %d\nMean steps = %g\nMean assigns = %g\n", K, meanSteps, meanAssigns);
    printFreqTable(freqSteps, freqAssigns, N*(N - 1)/2, K);
    return 0;
}

/* OUTPUT:
With k = 10000
Mean steps = 6
Mean assigns = 1.5061
Frequency Table:
Obsers :     0     1     2     3     4     5     6 
Assigns:  1699  3828  2960  1066   120   327     0
*/

/*
Số steps bằng số lần chạy vòng lặp for trong findMaxProduct:
- Ở vòng lặp for với biến j: có n - i - 1 lần lặp
- Ở vòng lặp for với biến i: tổng các số (n - i - 1) với i = 0 -> n - 1 = tổng các số từ 0 đến n - 1 = n*(n - 1)/2
Do đó: steps = n*(n - 1)/2
Thực tế, với N = 4, từ OUTPUT trên ta có: steps = 6 = 4*(4 - 3)/2
vì steps = n*(n - 1)/2 là hàm bậc 2 nên BigO = O(n^2)
*/