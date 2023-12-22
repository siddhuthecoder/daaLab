#include <stdio.h>
#include <stdlib.h>
#define INF 100000000
struct node {
    int vertex;
    int level;
    int cost;
    int **reducedMatrix;
    int **path;
}; 
struct node *CreateNode(int **parentMatrix, int **path, int level, int i, int j, int N) {
    struct node *node = (struct node *)malloc(sizeof(struct node));
    if (node == NULL) {
        printf("Memory allocation error.\n");
        exit(0);
    }
    node->reducedMatrix = (int **)malloc(N * sizeof(int *));
    node->path = (int **)malloc(N * sizeof(int *));
    for (int x = 0; x < N; x++) {
        node->reducedMatrix[x] = (int *)malloc(N * sizeof(int));
        node->path[x] = (int *)malloc(2 * sizeof(int));
    }
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            node->reducedMatrix[x][y] = parentMatrix[x][y];
        }
    }
    for (int x = 0; x < N; x++) {
        node->path[x][0] = path[x][0];
        node->path[x][1] = path[x][1];
    }
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
void printPath(int **list, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d -> %d\n", list[i][0] + 1, list[i][1] + 1);
    }
}
int ReductionCost(int **M, int N) {
    int cost = 0;
    int row[N], col[N];
    for (int i = 0; i < N; i++) {
        row[i] = INF;
        for (int j = 0; j < N; j++) {
            if (M[i][j] < row[i]) {
                row[i] = M[i][j];
            }
        }
        for (int j = 0; j < N; j++) {
            if (M[i][j] != INF && row[i] != INF) {
                M[i][j] -= row[i];
            }
        }
    }
    for (int i = 0; i < N; i++) {
        col[i] = INF;
        for (int j = 0; j < N; j++) {
            if (M[j][i] < col[i]) {
                col[i] = M[j][i];
            }
        }
        for (int j = 0; j < N; j++) {
            if (M[j][i] != INF && col[i] != INF) {
                M[j][i] -= col[i];
            }
        }
    }
    for (int i = 0; i < N; i++) {
        cost += (row[i] != INF) ? row[i] : 0;
        cost += (col[i] != INF) ? col[i] : 0;
    }
    
    return cost;
}
int branchAndBound(int **Graph, int N) {
    struct node *listofnodes[N * N];
    int listofNodesN = 0;
    int **v = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        v[i] = (int *)malloc(2 * sizeof(int));
    }
    struct node *root = CreateNode(Graph, v, 0, -1, 0, N);
    root->cost = ReductionCost(root->reducedMatrix, N);
    listofnodes[listofNodesN++] = root;

    while (listofNodesN > 0) {
        struct node *min = listofnodes[0];
        int index = 0;
        for (int i = 0; i < listofNodesN; i++) {
            if (listofnodes[i]->cost < min->cost) {
                min = listofnodes[i];
                index = i;
            }
        }
        listofnodes[index] = listofnodes[--listofNodesN];
        int i = min->vertex;

        if (min->level == N - 1) {
            min->path[min->level][0] = i;
            min->path[min->level][1] = 0;
            printPath(min->path, N);
            return min->cost;
        }
        for (int j = 0; j < N; j++) {
            if (min->reducedMatrix[i][j] != INF) {
                struct node *child = CreateNode(min->reducedMatrix, min->path, min->level + 1, i, j, N);
                child->cost = min->cost + min->reducedMatrix[i][j] + ReductionCost(child->reducedMatrix, N);
                listofnodes[listofNodesN++] = child;
            }
        }
    }
    return -1;
}
int main() {
    int N;
    printf("Enter the number of vertices: ");
    scanf("%d", &N);

    int **Graph = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        Graph[i] = (int *)malloc(N * sizeof(int));
    }
    printf("Enter the adjacency matrix for the graph:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &Graph[i][j]);
            if(Graph[i][j]==-1){
                Graph[i][j]=INF;
            }
        }
    }
    printf("\nMinimum Tour Cost is %d\n", branchAndBound(Graph, N));
    for (int i = 0; i < N; i++) {
        free(Graph[i]);
    }
    free(Graph);
    return 0;
}
