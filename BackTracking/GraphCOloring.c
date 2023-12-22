#include <stdbool.h>
#include <stdio.h>

#define V 4

void printSolution(int color[]);
bool isSafe(int v, bool graph[V][V], int color[], int c);
bool graphColoringUtil(bool graph[V][V], int m, int color[], int v, int *solutionCount);
bool graphColoring(bool graph[V][V], int m);
void printAllGraphColorings(bool graph[V][V], int m);

bool isSafe(int v, bool graph[V][V], int color[], int c) {
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return false;
    return true;
}

bool graphColoringUtil(bool graph[V][V], int m, int color[], int v, int *solutionCount) {
    if (v == V) {
        (*solutionCount)++;
        printSolution(color);
        return true;
    }

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, color, c)) {
            color[v] = c;

            if (graphColoringUtil(graph, m, color, v + 1, solutionCount))
                continue;

            color[v] = 0;
        }
    }
    return false;
}

bool graphColoring(bool graph[V][V], int m) {
    int color[V];
    for (int i = 0; i < V; i++)
        color[i] = 0;

    int solutionCount = 0;
    graphColoringUtil(graph, m, color, 0, &solutionCount);

    if (solutionCount == 0) {
        printf("Solution does not exist");
        return false;
    }
    return true;
}

void printSolution(int color[]) {
    printf("Solution: ");
    for (int i = 0; i < V; i++)
        printf("%d ", color[i]);
    printf("\n");
}

void printAllGraphColorings(bool graph[V][V], int m) {
    if (!graphColoring(graph, m))
        return;
}

int main() {
    bool graph[V][V] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0},
    };
    int m = 3;

    printAllGraphColorings(graph, m);

    return 0;
}
