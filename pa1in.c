#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct {
    char data[MAX_LENGTH];
    int front;
    int rear;
} Deque;

void initDeque(Deque* deque) {
    deque->front = -1;
    deque->rear = -1;
}

bool isEmpty(Deque* deque) {
    return deque->front == -1;
}

bool isFull(Deque* deque) {
    return (deque->rear + 1) % MAX_LENGTH == deque->front;
}

void insertFront(Deque* deque, char item) {
    if (isFull(deque)) {
        printf("덱이 가득 찼습니다.\n");
        return;
    }

    if (isEmpty(deque)) {
        deque->front = deque->rear = 0;
    }
    else {
        deque->front = (deque->front - 1 + MAX_LENGTH) % MAX_LENGTH;
    }

    deque->data[deque->front] = item;
}

void insertRear(Deque* deque, char item) {
    if (isFull(deque)) {
        printf("덱이 가득 찼습니다.\n");
        return;
    }

    if (isEmpty(deque)) {
        deque->front = deque->rear = 0;
    }
    else {
        deque->rear = (deque->rear + 1) % MAX_LENGTH;
    }

    deque->data[deque->rear] = item;
}

char deleteFront(Deque* deque) {
    if (isEmpty(deque)) {
        printf("덱이 비어 있습니다.\n");
        return '\0';
    }

    char item = deque->data[deque->front];

    if (deque->front == deque->rear) {
        initDeque(deque);
    }
    else {
        deque->front = (deque->front + 1) % MAX_LENGTH;
    }

    return item;
}

char deleteRear(Deque* deque) {
    if (isEmpty(deque)) {
        printf("덱이 비어 있습니다.\n");
        return '\0';
    }

    char item = deque->data[deque->rear];

    if (deque->front == deque->rear) {
        initDeque(deque);
    }
    else {
        deque->rear = (deque->rear - 1 + MAX_LENGTH) % MAX_LENGTH;
    }

    return item;
}

bool isPalindrome(char* str) {
    Deque deque;
    initDeque(&deque);
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        insertRear(&deque, str[i]);
    }

    while (!isEmpty(&deque)) {
        if (deque.front == deque.rear || deque.front == (deque.rear + 1) % MAX_LENGTH) {
            break;  // 남은 요소가 1개 또는 0개인 경우, 회문 검사 완료
        }

        char front = deleteFront(&deque);
        char rear = deleteRear(&deque);

        if (front != rear) {
            return false;
        }
    }

    return true;
}

int main() {
    char str[MAX_LENGTH];
    while (1) {
        printf("enter a string( or input exit): ");
        fgets(str, sizeof(str), stdin);

        str[strcspn(str, "\n")] = '\0';

        if (strcmp(str, "exit") == 0) {
            printf("exit the program.\n");
            break;
        }

        if (isPalindrome(str)) {
            printf("%s is palindrome\n\n", str);
        }
        else {
            printf("string is not palindrome\n\n");
        }
    }
    return 0;
}
