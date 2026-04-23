#include <stdio.h>
#define MAX 100

void printArray(int arr[], int n) {
    if (n == 0) return;
    printArray(arr, n - 1);
    printf("%d ", arr[n - 1]);
}

int linearSearch(int arr[], int n, int value) {
    if (n == 0) return -1;
    if (arr[n - 1] == value) return n - 1;
    return linearSearch(arr, n - 1, value);
}

int main() {
    int n = 9, arr[MAX] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    printf("arr[] = ");
    printArray(arr, n);
    printf("\n");
    int value;
    printf("value = ");
    scanf("%d", &value);
    printf("Found at %d", linearSearch(arr, n, value));
    return 0;
}

/* OUTPUT:
arr[] = 1 2 3 4 5 6 7 8 9 
value = 5
Found at 4
*/

/* printArray:
1. BASE CASE: n = 0 (mảng rỗng)
2. RESULT OF BASE CASE: return
3. BEFORE BASE CASE: n = 1
    printArray(arr, 1):
        printArray(arr, 0) --> return (BASE CASE)
    in ra phần tử arr[0]
4. BEFORE BEFORE: n = 2
    printArray(arr, 2):
        printArray(arr, 1):
            printArray(arr, 0) --> return (BASE CASE)
        in ra phần tử arr[0]
    in ra phần tử arr[1]
*/

/* linearSearch:
1. BASE CASE: n = 0 (mảng rỗng) hoặc arr[n - 1] = value (tại vị trí đang xét là giá trị cần tìm)
2. RESULT OF BASE CASE:
n = 0: 
    --> -1 (mảng rỗng nên trả về -1, tức không tìm thấy trong mảng)
arr[n - 1] = value:
    linearSearch(arr, n) --> n - 1 (trả về vị trí tìm thấy)
3. BEFORE BASE CASE: (n = 1) hoặc (n > 1 và arr[n - 2] = value)
Nếu n = 1: linearSearch(arr, 1) 
    - nếu arr[0] = value (BASE CASE) --> 0
    - ngược lại: linearSearch(arr, 0) (BASE CASE) --> -1
Nếu n > 1 và arr[n - 2] = value: linearSearch(arr, n) 
    - nếu arr[n - 1] = value (BASE CASE) --> n - 1
    - ngược lại: linearSearch(arr, n - 1) 
        vì arr[n - 2] = value --> n - 2
4. BEFORE BEFORE: (n = 2) hoặc (n > 2 và arr[n - 3] = value)
Nếu n = 2 và arr[n - 1] != value và arr[n - 2] != value: linearSearch(arr, 2)
    - nếu arr[1] = value (BASE CASE) --> 1
    - ngược lại: linearSearch(arr, 1) (BEFORE BASE CASE)
        + nếu arr[0] = value (BASE CASE) --> 0
        + ngược lại: linearSearch(arr, 0) (BASE CASE) --> -1
Nếu n > 2 và arr[n - 3] = value:
    - nếu arr[n - 1] = value (BASE CASE) --> n - 1
    - ngược lại: linearSearch(arr, n - 1) (BEFORE BASE CASE)
        + nếu arr[n - 2] = value (BASE CASE) --> n - 2
        + ngược lại: linearSearch(arr, n - 2) 
            do arr[n - 3] = value --> n - 3
*/