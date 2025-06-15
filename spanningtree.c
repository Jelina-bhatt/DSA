#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Edge structure
struct Edge {
    int u, v, weight;
};

// Compare function for sorting
int compare(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Find parent using path compression
int find(int parent[], int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

// Union by rank not used for simplicity
void unionSet(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

void kruskal(struct Edge edges[], int n, int e) {
    struct Edge result[MAX];
    int parent[MAX];
    int i, j = 0, count = 0;

    // Sort edges based on weight
    qsort(edges, e, sizeof(struct Edge), compare);

    // Initialize parent array
    for (i = 0; i < n; i++)
        parent[i] = i;

    for (i = 0; i < e && count < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        int set_u = find(parent, u);
        int set_v = find(parent, v);

        // If including this edge doesn’t cause a cycle
        if (set_u != set_v) {
            result[count++] = edges[i];
            unionSet(parent, set_u, set_v);
        }
    }

    printf("Edges in the Minimum Spanning Tree:\n");
    int totalCost = 0;
    for (i = 0; i < count; i++) {
        printf("%d -- %d == %d\n", result[i].u, result[i].v, result[i].weight);
        totalCost += result[i].weight;
    }
    printf("Total cost of MST: %d\n", totalCost);
}

int main() {
    int n, e;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    struct Edge edges[MAX];

    printf("Enter edges (u v weight):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
    }

    kruskal(edges, n, e);

    return 0;
}
