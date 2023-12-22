#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#define N 4
#define INF 100000000

struct node
{
    int cost;
    int vertex;
    int level;
    int reducedMatrix[N][N];
    int path[N][2];
};
int upper=INF;
struct node *CreateNode(int parentMatrix[N][N], int path[N][2], int level, int i, int j)
{
    struct node *node = (struct node *)malloc(sizeof(struct node));
    if (node == NULL)
    {
        printf("Memory allocation error.\n");
        exit(0);
    }
    for (int x = 0; x < N; x++)
    {
        for (int y = 0; y < N; y++)
        {
            node->reducedMatrix[x][y] = parentMatrix[x][y];
        }
    }
    for (int x = 0; x < N; x++)
    {
        node->path[x][0] = path[x][0];
        node->path[x][1] = path[x][1];
    }
    if (level != 0)
    {
        node->path[level - 1][0] = i;
        node->path[level - 1][1] = j;

        for (int m = 0; m < N; m++)
        {
            node->reducedMatrix[i][m] = INF;
            node->reducedMatrix[m][j] = INF;
        }
    }

    node->reducedMatrix[j][0] = INF;
    node->level = level;
    node->vertex = j;
    return node;
}
void printPath(int list[N][2], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d -> %d\n", list[i][0] + 1, list[i][1] + 1);
    }
}

int ReductionCost(int M[N][N])
{
    int cost = 0;
    int row[N], col[N];

    for (int i = 0; i < N; i++)
    {
        row[i] = INF;
        for (int j = 0; j < N; j++)
        {
            if (M[i][j] < row[i])
            {
                row[i] = M[i][j];
            }
        }
        for (int j = 0; j < N; j++)
        {
            if (M[i][j] != INF && row[i] != INF)
            {
                M[i][j] -= row[i];
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        col[i] = INF;
        for (int j = 0; j < N; j++)
        {
            if (M[j][i] < col[i])
            {
                col[i] = M[j][i];
            }
        }
        for (int j = 0; j < N; j++)
        {
            if (M[j][i] != INF && col[i] != INF)
            {
                M[j][i] -= col[i];
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        cost += (row[i] != INF) ? row[i] : 0;
        cost += (col[i] != INF) ? col[i] : 0;
    }
   
    return cost;
}

int branchAndBound(int Graph[N][N])
{
    struct node *listofnodes[N * N];
    int listofNodesN = 0;
    int v[N][2];
    struct node *root = CreateNode(Graph, v, 0, -1, 0);
    root->cost = ReductionCost(root->reducedMatrix);
    listofnodes[listofNodesN++] = root;
    while (listofNodesN > 0)
    {
        struct node *min = listofnodes[0];
        int index = 0;
        for (int i = 0; i < listofNodesN; i++)
        {
            if (listofnodes[i]->cost < min->cost)
            {
                min = listofnodes[i];
                index = i;
            }
        }
        listofnodes[index] = listofnodes[--listofNodesN];
        int i = min->vertex;
        
        if (min->level == N - 1)
        {
            min->path[min->level][0] = i;
            min->path[min->level][1] = 0;
            printPath(min->path,N);
            return min->cost;
        }
        for (int j = 0; j < N; j++)
        {
            if (min->reducedMatrix[i][j] != INF)
            {
                struct node *child = CreateNode(min->reducedMatrix, min->path, min->level + 1, i, j);
                child->cost = min->cost + min->reducedMatrix[i][j] + ReductionCost(child->reducedMatrix);
                 printf("%d \n",child->cost);
                listofnodes[listofNodesN++] = child;
            }
        }
    }

    return -1;
}

int main()
{
    int Graph[N][N] = {
        {INF, 20, 11, 10},
        {20, INF, 2, 5},
        {11, 2, INF, 8},
        {10, 5, 8, INF}};

    printf("\nMinimum Tour Cost is %d\n", branchAndBound(Graph));

    return 0;
}
