/*
Cho một số nguyên dương. Viết hàm tính tổng các chữ số lẻ của số nguyên dương đó. Ví dụ: Số 123456 có 3 chữ số lẻ là 1, 3, 5 nên tổng các chữ số lẻ là 9.
- Hãy chèn code để đếm số lần (steps) để tính tổng dồn ở hàm trên. Trong ví dụ trên, số lần tính tổng dồn là 3 do có 3 số lẻ. Hãy cho biết số steps chính xác theo tham số N (số chữ số của số nguyên trên) trong trường hợp tốt nhất và xấu nhất; và theo Big O.
- Viết chương trình chính chạy thực nghiệm lần lượt 10.000 và 100.000 lần, với mỗi lần tạo một số nguyên dương ngẫu nhiên có 6 chữ số. Hãy thống kê số steps trung bình là bao nhiêu, và tần suất xuất hiện của nó.
Ghi kết quả xuất ra của chương trình vào cuối bài làm.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define K 2
#define LEN 6

void initializeRandomArray(int arr[], int n, int min, int max) {
    for (int i = 0; i < n; i++) {
        arr[i] = min + rand() % (max - min + 1);
    }
}

int sumOdd(int num, int *steps) {
    (*steps) = 0;
    int sum = 0;
    while (num > 0) {
        int key = num % 10;
        if (key % 2 != 0) {
            (*steps)++;
            sum += key;
        }
        num /= 10;
    }
    return sum;
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
    printf("\nSteps : ");
    for (int i = 0; i <= valueCount; i++) {
        printf("%*d ", len, freq[i]);
    }

    printf("\n");
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int n;
    int min = 100000, max = 999999;
    const int TIMES[K] = {10000, 100000};
    int steps = 0;
    // Ví dụ:
    n = 123456;
    int sum = sumOdd(n, &steps);
    printf("Example: n = %d\nOdd Sum = %d - Total steps = %d\n", n, sum, steps);
    for (int k = 0; k < K; k++) {
        // Trường hợp xấu nhất là LEN steps
        int freqSteps[LEN + 1] = {0};
        for (int i = 0; i < TIMES[k]; i++) {
            n = min + rand() % (max - min + 1);
            sumOdd(n, &steps);
            freqSteps[steps]++;
        }
        float meanSteps = mean(freqSteps, LEN, TIMES[k]);
        printf("With k = %d:\n", TIMES[k]);
        printf("Mean steps = %f\n", meanSteps);
        printFreqTable(freqSteps, LEN, TIMES[k]);
        printf("\n");
    }
    printf("Randmax = %d", RAND_MAX);
    return 0;
}

/*OUTPUT: 
Example: n = 123456
Odd Sum = 9 - Total steps = 3
With k = 10000:
Mean steps = 3.380300
Frequency Table:
Obsers:     0     1     2     3     4     5     6
Steps :     0   383  1830  3265  2870  1427   225

With k = 100000:
Mean steps = 3.373710
Frequency Table:
Obsers:      0      1      2      3      4      5      6
Steps :      0   3749  17989  33060  29843  13062   2297
*/

/*Nhận xét: với n là số chữ số của số nguyên
+ Trong trường hợp tốt nhất: steps = 0 (khi số nguyên đó có các chữ số đều là số chẵn)
+ Trong trường hợp xấu nhất: steps = n (khi số nguyên đó có các chữ số đều là số lẻ)
--> BigO = O(n) với n là số chữ số của số nguyên
*/