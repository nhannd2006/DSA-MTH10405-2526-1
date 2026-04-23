#include <stdio.h>
#include <string.h>

void deleteString(char str[], int index);

int main() {
    char str[100];
    printf("Enter string: ");
    fgets(str, sizeof(str), stdin);
    if (strlen(str) >= 1 && str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = 0;
    int index;
    printf("Enter index to delete: ");
    scanf("%d", &index);
    deleteString(str, index);
    printf("String after deleting: ");
    fputs(str, stdout);
    return 0;
}

void deleteString(char str[], int index) {
    int len = strlen(str);
    if (index >= len || index < 0) return;
    for (int i = index; i < len - 1; i++) {
        str[i] = str[i+1];
    }
    str[len-1] = '\0';
}