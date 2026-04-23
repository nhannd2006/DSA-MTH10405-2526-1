#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 100

void initializeRandomArray(int arr[], int n, int min, int max) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + rand() % (max - min + 1);
    }
}

void copyArray(int sourceArray[], int n, int targetArray[]) {
    for (int i = 0; i < n; i++) {
        targetArray[i] = sourceArray[i];
    }
}

//Xét từng năm, nếu năm đó >= k thì xóa khỏi mảng
int caseA(int arr[], int *n, int k, int *comps, int *assigns) {
    *comps = 0;
    *assigns = 0;
    for (int i = *n - 1; i >= 0; i--) {
        (*comps)++;
        if (arr[i] >= k) {
            for (int j = i; j < *n - 1; j++) {
                (*assigns)++;
                arr[j] = arr[j + 1];
            }
            (*n)--;
        }
    }
    return (*comps + *assigns);
}

//Sắp xếp thành mảng tăng, xóa các năm >= k trở về sau
int caseB(int arr[], int *n, int k, int *compsSort, int *compsDel, int *swaps) {
    *compsSort = 0;
    *compsDel = 0;
    *swaps = 0;
    int sorted = 0;
    int unsortedEnd = *n - 1;
    while (!sorted) {
        sorted = 1;
        for (int i = 0; i < unsortedEnd; i++) {
            (*compsSort)++;
            if (arr[i] > arr[i + 1]) {
                sorted = 0;
                (*swaps)++;
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
        unsortedEnd--;
    }
    for (int i = *n - 1; i >= 0; i--) {
        (*compsDel)++;
        if (arr[i] < k) {
            *n = i + 1;
            break;
        }
    }
    return (*compsSort + *compsDel + *swaps);
}

float mean(int freq[], int valueCount, int totalFreq) {
    float sum = 0;
    for (int i = 0; i <= valueCount; i++) {
        sum += i*freq[i];
    }
    return sum/totalFreq;
}

void printFreqTable(int freq[], int valueCount, int totalFreq) {
    int len = log10(totalFreq) + 1;
    printf("Frequency Table:");
    printf("\nObsers : ");
    for (int i = 0; i <= valueCount; i++) {
        printf("%*d ", len, i);
    }
    printf("\nSteps  :");
    for (int i = 0; i <= valueCount; i++) {
        printf("%*d ", len, freq[i]);
    }
    printf("\n");
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int n = N;
    int copyn = n;
    int min = 1998, max = 2023, k = 2016;
    int arr[N];
    int times = 1000;
    int comps, assigns;
    int compsSort, compsDel, swaps;
    int freqA[N*(N + 1) / 2 + 1] = {0}, freqB[N*N + 1] = {0};
    int freqComps[N*(N + 1) / 2 + 1] = {0}, freqAssigns[N*(N + 1) / 2 + 1] = {0};
    int freqCompsSort[N*N + 1] = {0}, freqCompsDel[N*N + 1] = {0}, freqSwaps[N*N + 1] = {0};
    for (int i = 0; i < times; i++) {
        n = N; copyn = N;
        initializeRandomArray(arr, n, min, max);
        int copyArr[100];
        copyArray(arr, n, copyArr);
        int stepsA = caseA(arr, &n, k, &comps, &assigns);
        int stepsB = caseB(copyArr, &copyn, k, &compsSort, &compsDel, &swaps);
        freqA[stepsA]++;
        freqB[stepsB]++;
        freqComps[comps]++;
        freqAssigns[assigns]++;
        freqCompsSort[compsSort]++;
        freqCompsDel[compsDel]++;
        freqSwaps[swaps]++;
    }
    float meanStepsA = mean(freqA, N*(N + 1) / 2, times);
    float meanComps = mean(freqComps, N*(N + 1) / 2, times);
    float meanAssigns = mean(freqAssigns, N*(N + 1) / 2, times);
    float meanStepsB = mean(freqB, N*N, times);
    float meanCompsSort = mean(freqCompsSort, N*N, times);
    float meanCompsDel = mean(freqCompsDel, N*N, times);
    float meanSwap = mean(freqSwaps, N*N, times);
    printf("With times = %d\n", times);
    printf("Mean Comps = %f - Mean Assigns = %f\n", meanComps, meanAssigns);
    printf("Mean steps of Case A = %f\n", meanStepsA);
    printf("Mean CompsSort = %f - Mean CompsDel = %f - Mean Swap = %f\n", meanCompsSort, meanCompsDel, meanSwap);
    printf("Mean steps of Case B = %f\n", meanStepsB);
    printf("\nExample:\n");
    int a[N];
    initializeRandomArray(a, n, min, max);
    int cpyA[N];
    copyArray(a, n, cpyA);
    printf("Source:\n");
    printArray(a, n);
    int stepsA = caseA(a, &n, k, &comps, &assigns);
    int stepsB = caseB(cpyA, &copyn, k, &compsSort, &compsDel, &swaps);
    printf("Steps of Case A = %d\n", stepsA);
    printArray(a, n);
    printf("Steps of Case B = %d\n", stepsB);
    printArray(cpyA, copyn);
    return 0;
}

/*
With times = 1000
Mean Comps = 100.000000 - Mean Assigns = 1052.796021
Mean steps of Case A = 1152.796021
Mean CompsSort = 4856.225098 - Mean CompsDel = 31.402000 - Mean Swap = 2383.746094
Mean steps of Case B = 7271.373047

Example:
Source:
2021 2004 2001 2005 2000 2006 2016 1999 2009 2020 2020 2012 2007 2001 1999 2022 2018 2019 2022 2021 2012 2000 2013 2012 2000 2013 2016 2019 2023 2019 2020 1998 2020 2014 2017 2001 2004 2013 2003 2006 2002 2005 2019 2001 2011 2000 2018 2018 2006 2021 2021 2010 2013 2011 2004 2017 2019 2011 2000 2018 1999 2016 2006 2021 2009 2005 2023 2012 2012 2007 2002
Steps of Case A = 700
2004 2001 2005 2000 2006 1999 2009 2012 2007 2001 1999 2012 2000 2013 2012 2000 2013 1998 2014 2001 2004 2013 2003 2006 2002 2005 2001 2011 2000 2006 2010 2013 2011 2004 2011 2000 1999 2006 2009 2005 2012 2012 2007 2002
Steps of Case B = 3626
1998 1999 1999 1999 2000 2000 2000 2000 2000 2001 2001 2001 2001 2002 2002 2003 2004 2004 2004 2005 2005 2005 2006 2006 2006 2006 2007 2007 2009 2009 2010 2011 2011 2011 2012 2012 2012 2012 2012 2013 2013 2013 2013 2014*/