/*
Phân tích hàm đệ qui min() cho mảng a có các phần tử từ vị trí left sang right theo qui trình 4 bước.
int min(int a[], int left, int right) {
    if (left == right)
        return a[left];
    int middle = (left + right) / 2;
    int lvalue = min(a, left, middle);
    int rvalue = min(a, middle+1, right);
    if (lvalue < rvalue)
        return lvalue;
    else
        return rvalue;
} 
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define MAX 10
#define TIMES 1000

void printSubArray(int arr[], int left, int right) {
    for (int i = left; i <= right; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int min(int a[], int left, int right, int *countBase) {
    // printf("min(a, %d, %d) : subArray[] = ", left, right);
    // printSubArray(a, left, right);
    if (left == right) {
        (*countBase)++;
        return a[left];
    }
    int middle = (left + right) / 2;
    int lvalue = min(a, left, middle, countBase);
    int rvalue = min(a, middle+1, right, countBase);
    if (lvalue < rvalue)
        return lvalue;
    else
        return rvalue;
}

/*
min(a, 0, 6) : subArray[] = 2 5 7 0 12 1 17 
min(a, 0, 3) : subArray[] = 2 5 7 0
min(a, 0, 1) : subArray[] = 2 5
min(a, 0, 0) : subArray[] = 2
min(a, 1, 1) : subArray[] = 5
min(a, 2, 3) : subArray[] = 7 0
min(a, 2, 2) : subArray[] = 7
min(a, 3, 3) : subArray[] = 0
min(a, 4, 6) : subArray[] = 12 1 17
min(a, 4, 5) : subArray[] = 12 1
min(a, 4, 4) : subArray[] = 12
min(a, 5, 5) : subArray[] = 1
min(a, 6, 6) : subArray[] = 17
*/

void initializeRandomArray(int arr[], int n, int min, int max) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + rand() % (max - min + 1);
    }
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
    printf("\nObsers: ");
    for (int i = 0; i <= valueCount; i++) {
        printf("%*d ", len, i);
    }
    printf("\nCount : ");
    for (int i = 0; i <= valueCount; i++) {
        printf("%*d ", len, freq[i]);
    }
    printf("\n");
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int countBase = 0;
    int a[] = {2, 5, 7, 0, 12, 1, 17};
    printf("a[] = {2, 5, 7, 0, 12, 1, 17} - Min = %d\n", min(a, 0, 6, &countBase));
    printf("Count = %d\n\n", countBase);
    int arr[MAX], n = MAX;
    int freq[MAX + 1 + 1] = {};
    for (int k = 0; k < TIMES; k++) {
        countBase = 0;
        initializeRandomArray(arr, n, -1000, 1000);
        min(arr, 0, n - 1, &countBase);
        freq[countBase]++;
    }
    float meanCount = mean(freq, MAX + 1, TIMES);
    printf("With k = %d.\n", TIMES);
    printf("Mean countBase = %f\n", meanCount);
    printFreqTable(freq, MAX + 1, TIMES);
    printf("\n");
    return 0;
}

/* OUTPUT:
a[] = {2, 5, 7, 0, 12, 1, 17} - Min = 0
Count = 7

With k = 1000.
Mean countBase = 10.000000
Frequency Table:
Obsers:    0    1    2    3    4    5    6    7    8    9   10   11
Count :    0    0    0    0    0    0    0    0    0    0 1000    0
*/

/*RECURSION - 4 STEPS:
1. BASE CASE: left = right (mảng đang xét có 1 phần tử)
2. RESULT OF BASE CASE: a[left] (mảng có 1 phần tử thì phần tử ấy hiển nhiên là nhỏ nhất)
Cụ thể:
    min(a, 0, 0) : subArray[] = 2
    min(a, 1, 1) : subArray[] = 5
    min(a, 2, 2) : subArray[] = 7
    min(a, 3, 3) : subArray[] = 0
    min(a, 4, 4) : subArray[] = 12
    min(a, 5, 5) : subArray[] = 1
    min(a, 6, 6) : subArray[] = 17

3. BEFORE BASE CASE: left + 1 = right (mảng đang xét có 2 phần tử)
Khi đó:
    - middle = (left + left + 1) / 2 = left
    - chia mảng đang xét thành 2 mảng con:
        + lvalue = min(a, left, left) <mảng có 1 phần tử - base case>
            --> lvalue = a[left]
        + rvalue = min(a, left + 1, left + 1) <mảng có 1 phần tử - base case>
            --> rvalue = a[left + 1]
    - cuối cùng trả về giá trị nhỏ hơn của lvalue và rvalue
    => Vậy min(a, left, left + 1) = min{a[left], a[left + 1]}
Cụ thể:
    min(a, 0, 1) : subArray[] = 2 5
        min(a, 0, 0) : subArray[] = 2
        min(a, 1, 1) : subArray[] = 5
    min(a, 2, 3) : subArray[] = 7 0
        min(a, 2, 2) : subArray[] = 7
        min(a, 3, 3) : subArray[] = 0
    min(a, 4, 5) : subArray[] = 12 1
        min(a, 4, 4) : subArray[] = 12
        min(a, 5, 5) : subArray[] = 1
4. BEFORE BEFORE: left + 2 = right (mảng đang xét có 3 phần tử)
Khi đó:
    - middle = (left + left + 2) / 2 = left + 1
    - chia mảng đang xét thành 2 mảng con:
        + lvalue = min(a, left, left + 1) <mảng có 2 phần tử - before base case>
            --> lvalue = min{a[left], a[left + 1]}
        + rvalue = min(a, left + 2, left + 2) <mảng có 1 phần tử - base case>
            --> rvalue = a[left + 2]
    - cuối cùng trả về giá trị nhỏ hơn của lvalue và rvalue
    => Vậy min(a, left, left + 2) = min{a[left], a[left + 1], a[left + 2]}
Cụ thể:
    min(a, 4, 6) : subArray[] = 12 1 17
        min(a, 4, 5) : subArray[] = 12 1
            min(a, 4, 4) : subArray[] = 12
            min(a, 5, 5) : subArray[] = 1
        min(a, 6, 6) : subArray[] = 17
*/