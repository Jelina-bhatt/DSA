#include <stdio.h>

#define SIZE 10

int keys[SIZE];
int values[SIZE];

// Initialize table with -1
void init() {
    for (int i = 0; i < SIZE; i++) {
        keys[i] = -1;
    }
}

// Hash function
int hashFunction(int key) {
    return key % SIZE;
}

// Insert using linear probing
void insert(int key, int value) {
    int index = hashFunction(key);
    int originalIndex = index;

    while (keys[index] != -1 && keys[index] != key) {
        index = (index + 1) % SIZE;
        if (index == originalIndex) {
            printf("Hash table is full\n");
            return;
        }
    }

    keys[index] = key;
    values[index] = value;
}

// Display function
void display() {
    for (int i = 0; i < SIZE; i++) {
        if (keys[i] != -1)
            printf("Index %d: Key = %d, Value = %d\n", i, keys[i], values[i]);
        else
            printf("Index %d: Empty\n", i);
    }
}

// Main
int main() {
    init();

    insert(1, 100);
    insert(11, 200); // Collision with 1
    insert(21, 300); // Another collision
    insert(2, 400);

    display();
    return 0;
}
