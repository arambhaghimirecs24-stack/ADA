#include <stdio.h>
#define MAX 100
int main() {
    int n, i, j;
    int graph[MAX][MAX];
    int indegree[MAX] = {0};
    int queue[MAX], front = 0, rear = 0;
    int count = 0;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter adjacency matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(graph[i][j] == 1) {
                indegree[j]++;
            }
        }
    }
    for(i = 0; i < n; i++) {
        if(indegree[i] == 0) {
            queue[rear++] = i;
        }
    }
    printf("Topological Order: ");
    while(front < rear) {
        int u = queue[front++];
        printf("%d ", u);
        count++;
        for(j = 0; j < n; j++) {
            if(graph[u][j] == 1) {
                indegree[j]--;
                if(indegree[j] == 0) {
                    queue[rear++] = j;
                }
            }
        }
    }
    if(count != n) {
        printf("\nGraph has a cycle! Topological sorting not possible.\n");
    }
    return 0;
}
