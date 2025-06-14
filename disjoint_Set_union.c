#include <stdio.h>

#define N 100

int parent[N];
int rank[N];

// Initialize each node to be its own parent
void makeSet(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

// Find with path compression
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]); // Path compression
    return parent[x];
}

// Union by rank
void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    
    if (rootX == rootY) return;

    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

int main() {
    int n = 6;
    makeSet(n);

    unionSets(0, 1);
    unionSets(1, 2);
    unionSets(3, 4);

    printf("Are 0 and 2 connected? %s\n", find(0) == find(2) ? "Yes" : "No");
    printf("Are 0 and 4 connected? %s\n", find(0) == find(4) ? "Yes" : "No");

    unionSets(2, 4);
    printf("After union of 2 and 4:\n");
    printf("Are 0 and 4 connected? %s\n", find(0) == find(4) ? "Yes" : "No");

    return 0;
}
