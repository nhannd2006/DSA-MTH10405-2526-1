#include <stdio.h>
#include <string.h>

void insertCharToString(char *str, char ch, int index);

int main() {
    char str[1000];
    printf("Enter string: ");
    fgets(str, sizeof(str), stdin);
    if (strlen(str) >= 1 && str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = 0;
    char ch;
    int index;
    printf("Enter character to insert and corresponding index: ");
    scanf("%c%d", &ch, &index);

    insertCharToString(str, ch, index);
    printf("String after inserting: ");
    fputs(str, stdout);
    return 0;
}

void insertCharToString(char *str, char ch, int index) {
    int len = strlen(str);
    if (index > len || index < 0) return;
    for (int i = len; i >= index; i--) {
        str[i+1] = str[i];
    }
    str[index] = ch;
}