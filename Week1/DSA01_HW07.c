#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LEN_CODE = 10;

void insertCodesToOrderedArray(char ***codeArr, int *n, char **newCode, int m);

int main() {
    int n;
    printf("Enter size of code array: ");
    scanf("%d", &n);
    char **codeArr = (char **) malloc(n * sizeof(char *));
    printf("Enter elements of code array:\n");
    for (int i = 0; i < n; i++) {
        codeArr[i] = (char *) malloc( (LEN_CODE + 1) * sizeof(char));
        while (getchar() != '\n');
        fgets(codeArr[i], LEN_CODE + 1, stdin);
        codeArr[i][strcspn(codeArr[i], "\n")] = 0;
    }

    int m;
    printf("Enter size of code array to insert: ");
    scanf("%d", &m);
    char **newCode = (char **) malloc(m * sizeof(char *));
    printf("Enter elements of code array to insert:\n");
    for (int i = 0; i < m; i++) {
        newCode[i] = (char *) malloc( (LEN_CODE + 1) * sizeof(char));
        while (getchar() != '\n');
        fgets(newCode[i], LEN_CODE + 1, stdin);
        newCode[i][strcspn(newCode[i], "\n")] = 0;
    }
    insertCodesToOrderedArray(&codeArr, &n, newCode, m);
    printf("Code array after inserting:\n");
    for (int i = 0; i < n; i++) {
        fputs(codeArr[i], stdout);
        printf(" ");
    }
    free(codeArr);
    free(newCode);
    return 0;
}

void insertCodesToOrderedArray(char ***codeArr, int *n, char **newCode, int m) {
    *codeArr = (char **) realloc(*codeArr, (*n + m) * sizeof(char *));
    for (int i = *n; i < *n + m; i++) {
        (*codeArr)[i] = (char *) malloc((LEN_CODE + 1) * sizeof(char));
    }
    for (int i = 0; i < m; i++) {
        (*n)++;
        int index = *n - 1;
        for (int j = 0; j < *n - 1; j++) {
            if (strcmp(newCode[i], (*codeArr)[j]) < 0) {
                index = j;
                break;
            }
        }
        for (int j = *n - 1; j > index; j--) {
            strcpy((*codeArr)[j], (*codeArr)[j-1]);
        }
        strcpy((*codeArr)[index], newCode[i]);
    }
}