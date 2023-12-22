#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4
#define INF 99999

struct Node {
    int reducedMatrix[N][N];
    int cost;
    int vertex;
    int level;
    int path[N][2];
};

struct Node* newNode(int parentMatrix[N][N], int path[N][2], int level, int i, int j) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    memcpy(node->reducedMatrix, parentMatrix, sizeof(node->reducedMatrix));
    memcpy(node->path, path, sizeof(node->path));

    if (level != 0) {
        node->path[level - 1][0] = i;
        node->path[level - 1][1] = j;

        for (int m = 0; m < N; m++) {
            node->reducedMatrix[i][m] = INF;
            node->reducedMatrix[m][j] = INF;
        }
    }
    node->reducedMatrix[j][0] = INF;
    node->level = level;
    node->vertex = j;
    return node;
}


void rowReduction(int reducedMatrix[N][N], int row[N]) {
    for (int i = 0; i < N; i++) {
        row[i] = INF;
        for (int j = 0; j < N; j++) {
            if (reducedMatrix[i][j] < row[i]) {
                row[i] = reducedMatrix[i][j];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (reducedMatrix[i][j] != INF && row[i] != INF) {
                reducedMatrix[i][j] -= row[i];
            }
        }
    }
}

void columnReduction(int reducedMatrix[N][N], int col[N]) {
    for (int i = 0; i < N; i++) {
        col[i] = INF;
        for (int j = 0; j < N; j++) {
            if (reducedMatrix[i][j] < col[j]) {
                col[j] = reducedMatrix[i][j];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (reducedMatrix[i][j] != INF && col[j] != INF) {
                reducedMatrix[i][j] -= col[j];
            }
        }
    }
}

int calculateCost(int reducedMatrix[N][N]) {
    int cost = 0;
    int row[N], col[N];

    rowReduction(reducedMatrix, row);
    columnReduction(reducedMatrix, col);

    for (int i = 0; i < N; i++) {
        cost += (row[i] != INF) ? row[i] : 0;
        cost += (col[i] != INF) ? col[i] : 0;
    }
   printf("%d",cost);
    return cost;
}

void printPath(int list[N][2], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d -> %d\n", list[i][0] + 1, list[i][1] + 1);
    }
}

int solve(int costMatrix[N][N]) {
    struct Node* pq[N * N];
    int pqSize = 0;

    int v[N][2];

    struct Node* root = newNode(costMatrix, v, 0, -1, 0);
    root->cost = calculateCost(root->reducedMatrix);

    pq[pqSize++] = root;

    while (pqSize > 0) {
        struct Node* min = pq[0];
        int index = 0;

        for (int i = 1; i < pqSize; i++) {
            if (pq[i]->cost < min->cost) {
                min = pq[i];
                index = i;
            }
        }
        pq[index] = pq[pqSize - 1];
        pqSize--;

        int i = min->vertex;

        if (min->level == N - 1) {
            min->path[min->level][0] = i;
            min->path[min->level][1] = 0;
            printPath(min->path, N);
            return min->cost;
        }

        for (int j = 0; j < N; j++) {
            if (min->reducedMatrix[i][j] != INF) {
                struct Node* child = newNode(min->reducedMatrix, min->path, min->level + 1, i, j);
                child->cost = min->cost + min->reducedMatrix[i][j] + calculateCost(child->reducedMatrix);
                pq[pqSize++] = child;
            }
        }

        free(min);
    }

    return -1; // If no solution found
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
