#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

typedef struct {
    int arr[MAX];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmptyStack(Stack *s) {
    return s->top == -1;
}

int isFullStack(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, int value) {
    if (isFullStack(s)) printf("Stack is full.\n");
    else s->arr[++s->top] = value;
}

int pop(Stack *s) {
    if (isEmptyStack(s)) {
        printf("Stack is empty.\n");
        return INT_MIN;
    }
    else return s->arr[s->top--];
}

int peek(Stack *s) {
    if (isEmptyStack(s)) return INT_MIN;
    return s->arr[s->top];
}

void displayStack(Stack *s) {
    if (isEmptyStack(s)) {
        printf("Stack is empty.\n");
        return;
    }
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->arr[i]);
    }
    printf("\n");
}

void createBox(Stack *s);
int sumCards(Stack *s);

int main() {
    time_t t;
    srand((unsigned)time(&t));
    Stack box;
    initStack(&box);
    printf("Adding cards to the box:\n");
    createBox(&box);
    printf("Removing cards & calculating sum:\n");
    int sum = sumCards(&box);
    printf("Sum = %d", sum);
    return 0;
}

/* OUTPUT:
Adding cards to the box:
8 
8 2
8 2 7
8 2 7 2
8 2 7 2 1
Removing cards & calculating sum:
8 2 7 2
8 2 7
8 2
8
Stack is empty.
Sum = 20
*/

void createBox(Stack *s) {
    if (isFullStack(s)) return;
    int card = rand() % 10 + 1;
    push(s, card);
    displayStack(s);
    if (card == 1) return;
    createBox(s);
}

/* CREATE BOX:
1. BASE CASE: isFullStack(s) hoặc card = 1
2. RESULT OF BASE CASE: return
3. BEFORE BASE CASE: s->top = 18 hoặc (card' = 1 và s->top < 18) (thẻ bốc được ngay sau đó là 1)
Khi s->top = 18: đẩy card ngẫu nhiên vào box
    - nếu card = 1 --> return
    - ngược lại tiếp tục createBox(s) mà vì s->top = 19 nên return
Khi card' = 1: đẩy card ngẫu nhiên vào box
    - nếu card = 1 --> return
    - ngược lại tiếp tục createBox(s): đẩy card' ngẫu nhiên vào box
        + vì card' = 1 --> return
4. BEFORE BEFORE: s->top = 17 hoặc (card'' = 1 và s->top < 17)
Khi s->top = 17: đẩy card ngẫu nhiên vào box
    - nếu card = 1 --> return
    - ngược lại tiếp tục createBox(s): đẩy card ngẫu nhiên vào box
        + nếu card = 1 --> return
        + ngược lại tiếp tục createBox(s) mà vì s->top = 19 nên return
Khi card'' = 1: đẩy card ngẫu nhiên vào box
    - nếu card = 1 --> return
    - ngược lại tiếp tục createBox(s): đẩy card' ngẫu nhiên vào box
        + nếu card' = 1 --> return
        + ngược lại tiếp tục createBox(s): đẩy card'' ngẫu nhiên vào box
            vì card'' = 1 --> return
*/

int sumCards(Stack *s) {
    if (isEmptyStack(s)) return 0;
    int card = pop(s);
    displayStack(s);
    return card + sumCards(s);
}

/* SUM CARDS:
1. BASE CASE: isEmptyStack(s)
2. RESULT OF BASE CASE: 0
3. BEFORE BASE CASE: s->top = 0
lấy card đỉnh ra + sumCards(s) mà lúc này stack đã rỗng nên --> card
4. BEFORE BEFORE: s->top = 1
lấy card đỉnh ra + sumCards(s)
    lấy card' đỉnh ra + sumCards(s) mà lúc này đã rỗng nên --> card'
--> card + card'
*/