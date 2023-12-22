#include <stdio.h>
#include <limits.h>

#define N 4
#define INF INT_MAX

void printPath(int path[N], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d -> ", path[i] + 1);
    }
    printf("%d\n", path[0] + 1);
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

void tspBranchBound(int costMatrix[N][N], int path[N], int level, int* minCost) {
    if (level == N) {
        if (costMatrix[path[level - 1]][path[0]] != INF) {
            int currentCost = 0;
            for (int i = 0; i < N - 1; i++) {
                currentCost += costMatrix[path[i]][path[i + 1]];
            }
            currentCost += costMatrix[path[N - 1]][path[0]];

            if (currentCost < *minCost) {
                *minCost = currentCost;
                printPath(path, N);
            }
        }
        return;
    }

    for (int i = 0; i < N; i++) {
        if (isValid(i, costMatrix, path, level)) {
            path[level] = i;

            tspBranchBound(costMatrix, path, level + 1, minCost);

            path[level] = -1;
        }
    }
}

int solve(int costMatrix[N][N]) {
    int path[N];
    for (int i = 0; i < N; i++) {
        path[i] = -1;
    }
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
