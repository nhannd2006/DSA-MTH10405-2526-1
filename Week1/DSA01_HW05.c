#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertStringToString(char ***strArr, int *n, int len, char *str, int index);

int main() {
    int n, len;
    printf("Enter size of string array and size of character strings: ");
    scanf("%d%d", &n, &len);
    char **strArr = (char **)malloc(n * sizeof(char *));
    printf("Enter elements of string array:\n");
    for (int i = 0; i < n; i++) {
        strArr[i] = (char *)malloc((len + 1) * sizeof(char));
        while (getchar() != '\n');
        fgets(strArr[i], len + 1, stdin);
        strArr[i][strcspn(strArr[i], "\n")] = 0;
    }
    int idx;
    printf("Enter index to insert: ");
    scanf("%d", &idx);
    char *str = (char *) malloc((len + 1) * sizeof(char));
    printf("Enter string to insert: ");
    while (getchar() != '\n');
    fgets(str, len + 1, stdin);
    str[strcspn(str, "\n")] = 0;
    insertStringToString(&strArr, &n, len, str, idx);
    printf("String array after inserting: ");
    for (int i = 0; i < n; i++) {
        fputs(strArr[i], stdout);
        printf(" ");
    }
    free(strArr);
    free(str);
    return 0;
}

void insertStringToString(char ***strArr, int *n, int len, char *str, int index) {
    (*n)++;
    *strArr = (char **) realloc(*strArr, (*n) * sizeof(char *));
    (*strArr)[*n - 1] = (char *) malloc((len + 1) * sizeof(char));
    for (int i = *n - 1; i > index; i--) {
        strcpy((*strArr)[i], (*strArr)[i-1]);
    }
    strcpy((*strArr)[index], str);
}