#include <stdio.h>
#include <string.h>

const int MAX = 2003;

int match(char str[], char sub[], int pos);
void deformSubstring(char str[], char newStr[]);
void replaceSubstring(char str[], int oldLen, char newSub[], int index);
void interfereVirusSubstring(char packet[], int k, char virus[][MAX]);

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
    interfereVirusSubstring(packet, k, virus);
    printf("Packet after replacing virus substring:\n");
    fputs(packet, stdout);
    return 0;
}

int match(char str[], char sub[], int pos) {
    for (int i = 0; sub[i] != 0; i++) {
        if (str[i + pos] != sub[i]) return 0;
    }
    return 1;
}

void deformSubstring(char str[], char newStr[]) {
    int len = strlen(str);
    for (int i = len*2 - 2; i >= 0; i-=2) {
        newStr[i] = str[i/2];
        newStr[i + 1] = str[i/2] + 1;
    }
    newStr[len*2] = 0;
}

void replaceSubstring(char str[], int oldLen, char newSub[], int index) {
    int newLen = strlen(newSub);
    int len = strlen(str);
    for (int i = len + newLen - oldLen; i >= index + newLen; i--) {
        str[i] = str[i - newLen + oldLen];
    }
    for (int i = 0; i < newLen; i++) {
        str[i + index] = newSub[i];
    }
}

void interfereVirusSubstring(char packet[], int k, char virus[][MAX]) {
    int len = strlen(packet);
    int len_i[5];
    for (int i = 0; i < k; i++) {
        len_i[i] = strlen(virus[i]);
    }
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < k; j++) {
            if (i + len_i[j] > len) continue;
            if (match(packet, virus[j], i)) {
                char newStr[MAX];
                deformSubstring(virus[j], newStr);
                replaceSubstring(packet, len_i[j], newStr, i);
                len = strlen(packet);
                i--;
                break;
            }
        }
    }
}