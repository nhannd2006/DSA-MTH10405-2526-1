#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define K 1
#define MAX 3

int isAscendingInteger(int n, int *comps) {
    *comps = 0;
    int temp = n % 10;
    n /= 10;
    while (n > 0) {
        (*comps)++;
        if (temp < n % 10) return 0;
        temp = n % 10;
        n /= 10;
    }
    return 1;
}

float mean(int freq[], int valueCount, int totalFreq) {
    float sum = 0;
    for (int i = 0; i <= valueCount; i++) {
        sum += i*freq[i];
    }
    return sum/totalFreq;
}

void printFreqTable(int freqComps[], int valueCount, int totalFreq) {
    int len = log10(totalFreq) + 1;
    printf("Frequency Table:");
    printf("\nObsers: ");
    for (int i = 0; i <= valueCount; i++) {
        printf("%*d ", len, i);
    }
    printf("\nComps : ");
    for (int i = 0; i <= valueCount; i++) {
        printf("%*d ", len, freqComps[i]);
    }
    printf("\n");
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int min = 1000, max = 9999;
    int comps = 0;
    // because the worst-case of this Algorithm is 4 steps
    int freqComps[MAX + 1] = {0};
    for (int n = min; n <= max; n++) {
        isAscendingInteger(n, &comps);
        freqComps[comps]++;
    }
    float meanComps = mean(freqComps, MAX, max - min + 1);
    printf("With k = %d:\n", max - min + 1);
    printf("Mean comps = %f\n", meanComps);
    printFreqTable(freqComps, MAX, max - min + 1);
    printf("\n");
    return 0;
}

/*
With k = 9000:
Mean comps = 1.770000
Frequency Table:
Obsers:    0    1    2    3
Comps :    0 4050 2970 1980
*/