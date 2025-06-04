#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

// Node structure
struct Node {
    int key;
    int value;
    struct Node* next;
};

// Hash table
struct Node* hashTable[SIZE];

// Hash function
int hashFunction(int key) {
    return key % SIZE;
}

// Insert function
void insert(int key, int value) {
    int index = hashFunction(key);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// Display function
void display() {
    for (int i = 0; i < SIZE; i++) {
        struct Node* temp = hashTable[i];
        printf("Index %d: ", i);
        while (temp != NULL) {
            printf("(%d, %d) -> ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Main
int main() {
    insert(1, 100);
    insert(11, 200); // Collision with 1
    insert(21, 300); // Another collision
    insert(2, 400);

    display();
    return 0;
}
