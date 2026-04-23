#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int searchStringInArray(char **strArr, int n, char *str);

int main() {
    int n, k;
    printf("Enter size of string array: ");
    scanf("%d", &n);
    printf("Enter length of strings: ");
    scanf("%d", &k);
    char **strArr = (char **) malloc(n*sizeof(char *));
    printf("Enter strings of array:\n");
    for (int i = 0; i < n; i++) {
        while (getchar() != '\n');
        strArr[i] = (char *) malloc((k+1)*sizeof(char));
        fgets(strArr[i], k + 1, stdin);
        strArr[i][strcspn(strArr[i], "\n")] = 0;
    }

    printf("Enter string to search: ");
    char *str = (char *) malloc((k + 1)*sizeof(char));
    while (getchar() != '\n');
    fgets(str, k + 1, stdin);
    str[strcspn(str, "\n")] = 0;

    int index = searchStringInArray(strArr, n, str);
    if (index == -1) printf("Not found!");
    else printf("Found %s at %d", str, index);
    free(strArr);
    free(str);
    return 0;
}

int searchStringInArray(char **strArr, int n, char *str) {
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(strArr[i], str) == 0) {
            index = i;
            break;
        }
    }
    return index;
}