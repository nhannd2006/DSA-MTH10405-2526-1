#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100
#define EPSILON 1e-6

// ==============================

void bubbleSortFloatArray(double arr[], int n) {
    int sorted = 0;
    int unsortedEnd = n - 1;
    while (!sorted) {
        sorted = 1;
        for (int i = 0; i < unsortedEnd; i++) {
            if (arr[i] > arr[i + 1]) {
                sorted = 0;
                double temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
        unsortedEnd--;
    }
}

// ==============================

void bubbleSortStringASCII(char str[], int n) {
    int sorted = 0;
    int unsortedEnd = n - 1;
    while (!sorted) {
        sorted = 1;
        for (int i = 0; i < unsortedEnd; i++) {
            if (str[i] > str[i + 1]) {
                sorted = 0;
                char temp = str[i];
                str[i] = str[i + 1];
                str[i + 1] = temp;
            }
        }
        unsortedEnd--;
    }
}

int compareChar(char a, char b) {
    int lowerA, lowerB;
    if (a >= 'a' && a <= 'z') lowerA = 1;
    else lowerA = 0;
    if (b >= 'a' && b <= 'z') lowerB = 1;
    else lowerB = 0;
    if (a - 32*lowerA != b - 32*lowerB) return a - 32*lowerA < b - 32*lowerB;
    else {
        if (lowerA == 1 && lowerB == 0) return 0;
        if (lowerA == 0 && lowerB == 1) return 1;
        else return 1;
    }
}

void bubbleSortStringAlphabet(char str[], int n) {
    int sorted = 0;
    int unsortedEnd = n - 1;
    while (!sorted) {
        sorted = 1;
        for (int i = 0; i < unsortedEnd; i++) {
            if (!compareChar(str[i], str[i + 1])) {
                sorted = 0;
                char temp = str[i];
                str[i] = str[i + 1];
                str[i + 1] = temp;
            }
        }
        unsortedEnd--;
    }
}

// ==============================

typedef struct {
    double a, b, c;
} Triple;

double functionF(Triple x) {
    return x.a - 2*x.b + 3*x.c;
}

void bubbleSortTriple(Triple x[], int n) {
    int sorted = 0;
    int unsortedEnd = n - 1;
    while (!sorted) {
        sorted = 1;
        for (int i = 0; i < unsortedEnd; i++) {
            if (functionF(x[i]) > functionF(x[i + 1])) {
                sorted = 0;
                Triple temp = x[i];
                x[i] = x[i + 1];
                x[i + 1] = temp;
            }
        }
        unsortedEnd--;
    }
}

int main() {
    printf("1.1. To sort array of real numbers.\n");
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);
    double arr[MAX];
    printf("Enter elements of array:\n arr[] = ");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &arr[i]);
    }
    bubbleSortFloatArray(arr, n);
    printf("Array after sorting: arr[] = ");
    for (int i = 0; i < n; i++) {
        printf("%lf ", arr[i]);
    }
    printf("\n");

    printf("1.2. To sort string.\n");
    char str[MAX], newStr[MAX];
    printf("Enter string: ");
    getchar();
    fgets(str, sizeof(str), stdin);
    int len = strlen(str);
    if (len >= 1 && str[len - 1] == '\n') str[len - 1] = 0;
    strcpy(newStr, str);
    bubbleSortStringASCII(str, len);
    printf("String after sorting (ASCII): ");
    for (int i = 0; i < len; i++) {
        printf("%c", str[i]);
    }
    printf("\n");
    bubbleSortStringAlphabet(newStr, len);
    printf("String after sorting (Alphabet): ");
    for (int i = 0; i < len; i++) {
        printf("%c", newStr[i]);
    }
    printf("\n");

    printf("1.3. To sort triple array based on F(a,b,c) = a - 2b + 3c.\n");
    int k;
    printf("Enter size of triple array: ");
    scanf("%d", &k);
    Triple x[MAX];
    printf("Enter triples (a, b, c):\n");
    for (int i = 0; i < k; i++) {
        scanf("%lf%lf%lf", &x[i].a, &x[i].b, &x[i].c);
    }
    bubbleSortTriple(x, k);
    printf("Triple array after sorting: ");
    for (int i = 0; i < k; i++) {
        printf("(%lf, %lf, %lf) - F = %lf   ", x[i].a, x[i].b, x[i].c, functionF(x[i]));
    }
    printf("\n");
    return 0;
}