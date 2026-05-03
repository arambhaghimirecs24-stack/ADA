#include <stdio.h>
#include <stdlib.h>
#define MAX 100
struct Edge {
    int u, v, w;
};
struct Subset {
    int parent;
    int rank;
};
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}
void Union(struct Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);
    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}
int compare(const void* a, const void* b) {
    struct Edge* e1 = (struct Edge*)a;
    struct Edge* e2 = (struct Edge*)b;
    if (e1->w > e2->w) return 1;
    if (e1->w < e2->w) return -1;
    return 0;
}
void kruskal(struct Edge edges[], int V, int E) {
    struct Edge result[MAX];
    struct Subset subsets[MAX];
    qsort(edges, E, sizeof(edges[0]), compare);
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    int e = 0;
    int i = 0;
    int totalCost = 0;
    while (e < V - 1 && i < E) {
        struct Edge next = edges[i++];
        int x = find(subsets, next.u);
        int y = find(subsets, next.v);
        if (x != y) {
            result[e++] = next;
            totalCost += next.w;
            Union(subsets, x, y);
        }
    }
    printf("\nEdges in MST:\n");
    for (i = 0; i < e; i++) {
        printf("%d - %d : %d\n", result[i].u, result[i].v, result[i].w);
    }
    printf("Total Cost of MST = %d\n", totalCost);
}
int main() {
    int V, E;
    struct Edge edges[MAX];
    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &V);
    printf("Enter number of edges (max %d): ", MAX);
    scanf("%d", &E);
    if (V > MAX || E > MAX) {
        printf("Error: Exceeds maximum limit!\n");
        return 1;
    }
    printf("Enter edges (u v weight) [0-based indexing]:\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        if (edges[i].u >= V || edges[i].v >= V) {
            printf("Invalid vertex! Use values between 0 and %d\n", V - 1);
            return 1;
        }
    }
    kruskal(edges, V, E);
    return 0;
}
