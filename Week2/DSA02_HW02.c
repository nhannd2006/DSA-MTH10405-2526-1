#include <stdio.h>
#include <string.h>

int isOrderedString(char str[]);
int linearSearch(char str[], char ch);
int binarySearch(char str[], char ch);

int main() {
    char str[100];
    printf("Enter string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    if (isOrderedString(str) == 0) printf("The string is not in ascending order.");
    else {
        char ch;
        printf("Enter character to search: ");
        scanf("%c", &ch);
        int linearSearchIdx = linearSearch(str, ch);
        if (linearSearchIdx != -1) printf("Linear search: found %c at %d\n", ch, linearSearchIdx);
        else printf("Linear search: not found %c\n", ch);
        int binarySearchIdx = binarySearch(str, ch);
        if (binarySearchIdx != -1) printf("Binary search: found %c at %d\n", ch, binarySearchIdx);
        else printf("Binary search: not found %c\n", ch);
        if (linearSearchIdx == binarySearchIdx) printf("Both searches give the SAME result.\n");
        else printf("Search results DIFFER.\n");
    }
    return 0;
}

int isOrderedString(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len - 1; i++) {
        if (str[i] > str[i + 1]) return 0;
    }
    return 1;
}

int linearSearch(char str[], char ch) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == ch) return i;
        else if (str[i] > ch) break;
    }
    return -1;
}

int binarySearch(char str[], char ch) {
    int left = 0, right = strlen(str) - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (str[mid] == ch) return mid;
        else if (ch < str[mid]) right = mid - 1;
        else left = mid + 1;
    }
    return -1;
}