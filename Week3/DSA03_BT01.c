#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 10
#define K 3

void initializeRandomArray(int arr[], int n, int min, int max);
int linearSearch(int arr[], int n, int value, int *comps);
float meanComparison(int freq[], int n, int numValue);

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int n = N, min = -1000, max = 1000;
    int arr[100];
    int comps;
    const int TIMES[K] = {100, 1000, 10000};
    for (int k = 0; k < K; k++) {
        int freq[N + 1] = {0}; //because the worst case of linear search is N steps
        for (int i = 0; i < TIMES[k]; i++) {
            initializeRandomArray(arr, n, min, max);
            int value = arr[rand() % n];
            int index = linearSearch(arr, n, value, &comps);
            freq[comps]++;
        }
        printf("With k = %d:\nMean comparison = %f\n", TIMES[k], meanComparison(freq, n, TIMES[k]));
        for (int i = 0; i <= n; i++) {
            printf("%d comps - %d times, ", i, freq[i]);
        }
        printf("\n");
    }
    return 0;
}

void initializeRandomArray(int arr[], int n, int min, int max) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + rand() % (max - min + 1);
    }
}

int linearSearch(int arr[], int n, int value, int *comps) {
    *comps = 0;
    for (int i = 0; i < n; i++) {
        (*comps)++;
        if (arr[i] == value) return i;
    }
    return -1;
}

float meanComparison(int freq[], int n, int numValue) {
    float sum = 0;
    for (int i = 0; i <= n; i++) {
        sum += i*freq[i];
    }
    return sum/numValue;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linearSearch(int arr[], int n, int value, int* comps) {
    *comps = 0;
    for (int i = 0; i < n; i++) {
        (*comps)++;
        if (arr[i] == value) {
            return i;
        }
    }
}

void initializeArray(int arr[], int n, int min, int max) {
    for (int i = 0; i < n; i++)
        arr[i] = min + rand() % (max - min + 1);
}

int main() {
    int a[1000];
    int n = 20;
    int comps;
    int k[] = {100,1000,10000};
    //Sinh mang ngau nhien
    time_t t;
    srand((unsigned)time(&t));
    
    for (int i = 0; i < 3; i++){
        int freTable[21] = {}; //tao bang tan so voi tat ca tan so ben trong la 0.
        for (int j = 0; j < k[i]; j++){
            initializeArray(a, n, -1000, 1000);
            int value = a[rand() % (n - 1)];
            linearSearch(a, n, value, &comps);
            freTable[comps]++;
        }
        printf("k = %d; Mean = ",k[i]);
        float sum = 0;
        for (int l = 0; l < 21; l++)
            sum += l*freTable[l];
        sum /= k[i];
        printf("%f\n",sum);
    }
    return 0;
}
*/