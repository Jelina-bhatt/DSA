#include <stdio.h>

// Constant Time: O(1)
void constantTime(int n) {
    printf("Constant Time: Only one operation for n = %d\n", n);
}

// Linear Time: O(n)
void linearTime(int n) {
    printf("Linear Time: O(n)\n");
    for (int i = 0; i < n; i++) {
        printf("Step %d\n", i + 1);
    }
}

// Quadratic Time: O(n^2)
void quadraticTime(int n) {
    printf("Quadratic Time: O(n^2)\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("Step (%d, %d)\n", i + 1, j + 1);
        }
    }
}

// Logarithmic Time: O(log n)
void logarithmicTime(int n) {
    printf("Logarithmic Time: O(log n)\n");
    int count = 0;
    for (int i = 1; i < n; i *= 2) {
        printf("Step %d: i = %d\n", ++count, i);
    }
}

// Linearithmic Time: O(n log n)
void linearithmicTime(int n) {
    printf("Linearithmic Time: O(n log n)\n");
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j *= 2) {
            printf("Step (%d, %d)\n", i + 1, j);
        }
    }
}

int main() {
    int n;

    printf("Enter value of n: ");
    scanf("%d", &n);

    printf("\n--- Growth Function Demonstrations ---\n\n");

    constantTime(n);
    printf("\n");
    
    linearTime(n);
    printf("\n");

    logarithmicTime(n);
    printf("\n");

    linearithmicTime(n);
    printf("\n");

    quadraticTime(n);
    printf("\n");

    return 0;
}
