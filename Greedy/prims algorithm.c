#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_VERTICES 100
#define INF 999999
int graph[MAX_VERTICES][MAX_VERTICES];
int numVertices;
void primMST() {
    int parent[numVertices];
    int key[numVertices];
    bool inMST[numVertices];
    for (int i = 0; i < numVertices; i++) {
        key[i] = INF;
        inMST[i] = false;
    }
    key[0] = 0;
    parent[0] = -1;
    for (int count = 0; count < numVertices - 1; count++) {
        int minKey = INF, minIndex;
        for (int v = 0; v < numVertices; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }
        inMST[minIndex] = true;
        for (int v = 0; v < numVertices; v++) {
            if (graph[minIndex][v] && ! inMST[v] && graph[minIndex][v] < key[v]) {
                parent[v] = minIndex;
                key[v] = graph[minIndex][v];
            }
        }
    }
    printf("Edges in the Minimum Spanning Tree:\n");
    for (int i = 1; i < numVertices; i++) {
        printf("Edge: %d - %d, Weight: %d\n", i, parent[i], graph[i][parent[i]]);
    }
}
int main() {
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    printf("Enter the adjacency matrix for the graph:\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    primMST();
    return 0;
}