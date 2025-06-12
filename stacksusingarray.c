#include <stdio.h>
#define MAX 100  // Maximum size of stack

int stack[MAX];
int top = -1;

// Function to add an element to the stack
void push(int value) {
    if (top == MAX - 1) {
        printf("Stack Overflow! Cannot push %d\n", value);
    } else {
        top++;
        stack[top] = value;
        printf("%d pushed to stack\n", value);
    }
}

// Function to remove and return the top element
int pop() {
    if (top == -1) {
        printf("Stack Underflow! Stack is empty\n");
        return -1;
    } else {
        int popped = stack[top];
        top--;
        return popped;
    }
}

// Function to view the top element
int peek() {
    if (top == -1) {
        printf("Stack is empty\n");
        return -1;
    } else {
        return stack[top];
    }
}

// Function to display all elements
void display() {
    if (top == -1) {
        printf("Stack is empty\n");
    } else {
        printf("Stack (top to bottom):\n");
        for (int i = top; i >= 0; i--) {
            printf("%d\n", stack[i]);
        }
    }
}

// Main function to demonstrate stack operations
int main() {
    push(10);
    push(20);
    push(30);
    
    display();

    printf("Top element is: %d\n", peek());

    printf("Popped element: %d\n", pop());
    
    display();

    return 0;
}
