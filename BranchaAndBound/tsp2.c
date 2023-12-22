#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4
#define INF 99999

void printPath(int list[N], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d -> ", list[i] + 1);
    }
    printf("%d\n", list[0] + 1);
}

int isValid(int vertex, int costMatrix[N][N], int path[N], int pos) {
    if (costMatrix[path[pos - 1]][vertex] == INF) {
        return 0;
    }

    for (int i = 0; i < pos; i++) {
        if (path[i] == vertex) {
            return 0;
        }
    }

    return 1;
}

int calculateCost(int costMatrix[N][N], int path[N], int level) {
    int cost = 0;
    int visited[N];
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < level; i++) {
        visited[path[i]] = 1;
    }

    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            int min = INF;
            for (int j = 0; j < N; j++) {
                if (i != j && costMatrix[i][j] < min) {
                    min = costMatrix[i][j];
                }
            }
            cost += min;
        }
    }

    return cost;
}

void tspBranchBound(int costMatrix[N][N], int path[N], int level, int* minCost) {
    if (level == N) {
        if (costMatrix[path[level - 1]][path[0]] != INF) {
            int currentCost = *minCost;
            currentCost += costMatrix[path[level - 1]][path[0]];

            if (currentCost < *minCost) {
                *minCost = currentCost;
                printPath(path, level);
            }
        }
        return;
    }

    for (int i = 0; i < N; i++) {
        if (isValid(i, costMatrix, path, level)) {
            path[level] = i;

            int currentCost = calculateCost(costMatrix, path, level + 1);

            if (currentCost < *minCost) {
                tspBranchBound(costMatrix, path, level + 1, minCost);
            }
            path[level] = -1;
        }
    }
}

int solve(int costMatrix[N][N]) {
    int path[N];
    memset(path, -1, sizeof(path));
    int minCost = INF;

    path[0] = 0;
    tspBranchBound(costMatrix, path, 1, &minCost);

    return minCost;
}

int main() {
    int costMatrix[N][N] = {
        {INF, 2, 1, INF},
        {2, INF, 4, 3},
        {1, 4, INF, 2},
        {INF, 3, 2, INF}
    };

    printf("\n\nTotal cost is %d\n", solve(costMatrix));

    return 0;
}
