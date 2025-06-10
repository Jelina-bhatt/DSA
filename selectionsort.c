#include <stdio.h>

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int pos = i;
        
        // Find the index of the smallest element in the unsorted part
        for (int j = i + 1; j < n; j++) {
            if (*(arr + j) < *(arr + pos)) {
                pos = j;
            }
        }

        // Swap using arithmetic operations (without temp variable)
        if (pos != i) {
            *(arr + i) = *(arr + i) + *(arr + pos);
            *(arr + pos) = *(arr + i) - *(arr + pos);
            *(arr + i) = *(arr + i) - *(arr + pos);
        }
    }
}

int main() {
    int arr[] = {29, 10, 14, 37, 13};
    int n = sizeof(arr)/sizeof(arr[0]);

    selectionSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}
