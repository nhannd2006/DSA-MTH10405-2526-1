#include <stdio.h>
#include <string.h>

char lowerChar(char ch);
int findCharInString(char *str, char ch);

int main() {
    char str[100];
    printf("Enter string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    char ch;
    printf("Enter character to search: ");
    scanf("%c", &ch);

    int index = findCharInString(str, ch);
    if (index == -1) printf("Not found!");
    else printf("Found %c at %d", ch, index);
    return 0;
}

char lowerChar(char ch) {
    if (ch >= 'A' && ch <= 'Z') ch += 32;
    return ch;
}

int findCharInString(char *str, char ch) {
    int len = strlen(str);
    ch = lowerChar(ch);
    int index = -1;
    for (int i = 0; i < len; i++) {
        if (lowerChar(str[i]) == ch) {
            index = i;
            break;
        }
    }
    return index;
}