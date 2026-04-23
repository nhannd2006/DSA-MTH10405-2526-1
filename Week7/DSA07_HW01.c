#include <stdio.h>
#define MAX 100

int f(int n) {
    if (n == 1)
        return 1;
    return f(n - 1) * 2;
}

int f0(int n) {
    return 1 << (n - 1);
}

float g(int n) {
    if (n == 1)
        return 1.0;
    return n * n + g(n - 1);
}

float g0(int n) {
    float res = 1.0;
    for (int i = 2; i <= n; i++) {
        res += i*i;
    }
    return res;
}

int F(int n) {
    if (n == 1) return 1;
    if (n == 2) return 1;
    return F(n - 1) + F(n - 2);
}

int F0(int n) {
    int arr[MAX] = {};
    arr[0] = 1; arr[1] = 1;
    for (int i = 2; i < n; i++) {
        arr[i] = arr[i - 1] + arr[i - 2];
    }
    return arr[n - 1];
}

int P(int n) {
    if (n == 0) return 1;
    if (n == 1) return 2;
	if (n == 2) return 3;
    return P(n - 1) * P(n - 3);
}

int P0(int n) {
    int arr[MAX] = {};
    arr[0] = 1; arr[1] = 2; arr[2] = 3;
    for (int i = 3; i <= n; i++) {
        arr[i] = arr[i - 1] * arr[i - 3];
    }
    return arr[n];
}

int main() {
    int n;
    printf("n = ");
    scanf("%d", &n);
    printf("By recursion: f(%d) = %d | Non-recursion: f(%d) = %d\n", n, f(n), n, f0(n));
    printf("By recursion: g(%d) = %f | Non-recursion: g(%d) = %f\n", n, g(n), n, g0(n));
    printf("By recursion: F(%d) = %d | Non-recursion: F(%d) = %d\n", n, F(n), n, F0(n));
    printf("By recursion: P(%d) = %d | Non-recursion: P(%d) = %d\n", n, P(n), n, P0(n));
    return 0;
}

/* OUTPUT:
n = 5
By recursion: f(5) = 16 | Non-recursion: f(5) = 16
By recursion: g(5) = 55.000000 | Non-recursion: g(5) = 55.000000
By recursion: F(5) = 5 | Non-recursion: F(5) = 5
By recursion: P(5) = 18 | Non-recursion: P(5) = 18
*/

/* f(n) = 2 * f(n - 1)
1. BASE CASE: n = 1
2. RESULT OF BASE CASE: f(1) = 1
3. BEFORE BASE CASE: n = 2
    f(2) = 2 * f(1) = 2 * 1 = 2
4. BEFORE BEFORE: n = 3
    f(3) = 2 * f(2) = 2 * 2 * f(1) = 2 * 2 * 1 = 4
*/

/* g(n) = n*n + g(n - 1)
1. BASE CASE: n = 1
2. RESULT OF BASE CASE: g(1) = 1.0
3. BEFORE BASE CASE: n = 2
    g(2) = 2*2 + g(1) = 4 + 1.0 = 5.0
4. BEFORE BEFORE: n = 3
    g(3) = 3*3 + g(2) = 9 + 2*2 + g(1) = 9 + 4 + 1.0 = 14.0
*/

/* F(n) = F(n - 1) + F(n - 2); F(1) = 1; F(2) = 1
1. BASE CASE: n = 1 và n = 2
2. RESULT OF BASE CASE: F(1) = 1 và F(2) = 1
3. BEFORE BASE CASE: n = 3
    F(3) = F(2) + F(1) = 1 + 1 = 2
4. BEFORE BEFORE: n = 4
    F(4) = F(3) + F(2) = F(2) + F(1) + F(2) = 1 + 1 + 1 = 3
*/

/* P(n) = P(n - 1) * P(n - 3); P(0) = 1; P(1) = 2; P(2) = 3
1. BASE CASE: n = 0, n = 1 và n = 2
2. RESULT OF BASE CASE: P(0) = 1, P(1) = 2 và P(2) = 3
3. BEFORE BASE CASE: n = 3
    P(3) = P(2) * P(0) = 3 * 1 = 3
4. BEFORE BEFORE: 
    P(4) = P(3) * P(1) = P(2) * P(0) * P(1) = 3 * 1 * 2 = 6
*/