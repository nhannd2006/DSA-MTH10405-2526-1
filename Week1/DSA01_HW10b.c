#include <stdio.h>
#include <string.h>

const int MAX = 1001;

int match(char str[], char sub[], int pos);
void deleteSubstring(char str[], int index, int len);
void deleteVirusSubstring(char packet[], int k, char virus[][MAX]);

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
    deleteVirusSubstring(packet, k, virus);
    printf("Packet after deleting virus substring:\n");
    fputs(packet, stdout);
    return 0;
}

int match(char str[], char sub[], int pos) {
    for (int i = 0; sub[i] != 0; i++) {
        if (str[i + pos] != sub[i]) return 0;
    }
    return 1;
}

void deleteSubstring(char str[], int index, int subLen) {
    int len = strlen(str);
    for (int i = index; i <= len - subLen; i++) {
        str[i] = str[i + subLen];
    }
}

void deleteVirusSubstring(char packet[], int k, char virus[][MAX]) {
    int len = strlen(packet);
    int len_i[5];
    for (int i = 0; i < k; i++) {
        len_i[i] = strlen(virus[i]);
    }
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < k; j++) {
            if (i + len_i[j] > len) continue;
            if (match(packet, virus[j], i)) {
                deleteSubstring(packet, i, len_i[j]);
                i--;
                break;
            }
        }
    }
}