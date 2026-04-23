#include <stdio.h>
#include <string.h>

char findMissChar(char str[], char start, int total);
char binarySearchMissChar(char str[], char start, int total);
void insertArray(char str[], char ch);

int main() {
    char str[26];
    printf("Enter string of 25 characters: ");
    int filled = 0;
    while (!filled) {
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = 0;
        if (strlen(str) != 25) printf("Re-enter string of 25 characters: ");
        else filled = 1;
    }
    //char missChar = findMissChar(str, 'a', 26);
    char missChar = binarySearchMissChar(str, 'a', 26);
    printf("%c at %d is missing!\n", missChar, missChar - 'a');
    insertArray(str, missChar);
    printf("String after inserting: ");
    fputs(str, stdout);
    return 0;
}

char findMissChar(char str[], char start, int total) {
    char missChar = start + total - 1;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] != start + i) {
            missChar = str[i] - 1;
            break;
        }
    }
    return missChar;
}

char binarySearchMissChar(char str[], char start, int total) {
    char missChar = start + total - 1;
    int left = 0, right = strlen(str) - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (start + mid == str[mid]) left = mid + 1;
        else {
            missChar = start + mid;
            right = mid - 1;
        }
    }
    return missChar;
}

void insertArray(char str[], char ch) {
    int len = strlen(str);
    for (int i = len; i > ch - 'a'; i--) {
        str[i] = str[i - 1];
    }
    str[ch - 'a'] = ch;
}


/*
- Hàm findMissChar: duyệt từng ký tự trong chuỗi (linear scan)
- Có thể dùng Binary Search.
*/