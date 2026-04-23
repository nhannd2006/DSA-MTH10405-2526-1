#include <stdio.h>
#include <string.h>

const int MAX = 1001;

int match(char str[], char sub[], int pos);
void findVirusSubstring(char packet[], int k, char virus[][MAX], int count[], int pos[][MAX]);

int main() {
    char packet[MAX];
    printf("Enter an information packet: ");
    fgets(packet, sizeof(packet), stdin);
    int len = strlen(packet);
    if (len > 0 && packet[len - 1] == '\n') packet[len - 1] = 0;
    int k;
    printf("Enter number of virus substring: ");
    scanf("%d", &k);
    while(getchar() != '\n');
    char virus[5][MAX];
    printf("Enter virus substrings:\n");
    for (int i = 0; i < k; i++) {
        fgets(virus[i], sizeof(virus[i]), stdin);
        int len_i = strlen(virus[i]);
        if (len_i > 0 && virus[i][len_i - 1] == '\n') virus[i][len_i - 1] = 0;
    }
    int count[5] = {0};
    int pos[5][MAX];
    findVirusSubstring(packet, k, virus, count, pos);
    printf("Result:\n");
    for (int i = 0; i < k; i++) {
        printf("%d ", count[i]);
        fputs(virus[i], stdout);
        if (count[i] >= 1) {
            printf(" %d", pos[i][0]);
            for (int j = 1; j < count[i]; j++) {
                printf(", %d", pos[i][j]);
            }
        }
        printf("\n");
    }
    return 0;
}

int match(char str[], char sub[], int pos) {
    for (int i = 0; sub[i] != 0; i++) {
        if (str[i + pos] != sub[i]) return 0;
    }
    return 1;
}

void findVirusSubstring(char packet[], int k, char virus[][MAX], int count[], int pos[][MAX]) {
    int len = strlen(packet);
    int len_i[5];
    for (int i = 0; i < k; i++) {
        count[i] = 0;
        len_i[i] = strlen(virus[i]);
    }
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < k; j++) {
            if (i + len_i[j] > len) continue;
            if (match(packet, virus[j], i)) {
                pos[j][count[j]++] = i;
            }
        }
    }
}