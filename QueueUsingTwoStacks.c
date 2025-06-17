#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int stack1[MAX], stack2[MAX];
int top1 = -1, top2 = -1;

// Stack operations
void push1(int x) {
    if (top1 == MAX - 1) {
        printf("Stack1 Overflow\n");
        return;
    }
    stack1[++top1] = x;
}

int pop1() {
    if (top1 == -1) {
        printf("Stack1 Underflow\n");
        exit(1);
    }
    return stack1[top1--];
}

void push2(int x) {
    if (top2 == MAX - 1) {
        printf("Stack2 Overflow\n");
        return;
    }
    stack2[++top2] = x;
}

int pop2() {
    if (top2 == -1) {
        printf("Stack2 Underflow\n");
        exit(1);
    }
    return stack2[top2--];
}

// Queue operations using two stacks
void enqueue(int x) {
    push1(x);
    printf("%d enqueued\n", x);
}

int dequeue() {
    if (top2 == -1) {
        if (top1 == -1) {
            printf("Queue is empty\n");
            exit(1);
        }
        while (top1 != -1)
            push2(pop1());
    }
    return pop2();
}

// Main function
int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    printf("Dequeued: %d\n", dequeue());
    enqueue(40);
    printf("Dequeued: %d\n", dequeue());
    return 0;
}
