#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10
#define MAX_EDGES 10

int rank[MAX_VERTICES];
int parent[MAX_VERTICES];
int A[MAX_VERTICES];
int listofEdges[MAX_EDGES][3];

int compareEdges(const void *a, const void *b)
{
    return ((int(*)[3])a)[0][2] - ((int(*)[3])b)[0][2];
}

int findSet(int i)
{
    if (parent[i] == i)
    {
        return i;
    }
    else
    {
        int res = findSet(parent[i]);
        parent[i] = res;
        return res;
    }
}

void makeSet(int v)
{
    for (int i = 0; i < v; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}

void Union(int v1, int v2)
{
    int r1 = rank[v1];
    int r2 = rank[v2];
    if (r1 > r2)
    {
        parent[v2] = parent[v1];
    }
    else if (r1 < r2)
    {
        parent[v1] = parent[v2];
    }
    else
    {
        parent[v2] = parent[v1];
        rank[v1] = rank[v1] + 1;
    }
}

int main()
{
    int v, e;

    printf("Enter the number of vertices: ");
    scanf("%d", &v);

    printf("Enter the number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (vertex1 vertex2 weight):\n");
    for (int i = 0; i < e; i++)
    {
        scanf("%d %d %d", &listofEdges[i][0], &listofEdges[i][1], &listofEdges[i][2]);
    }
    makeSet(v);
    qsort(listofEdges, e, sizeof(listofEdges[0]), compareEdges);

    int minCost = 0;
    int index = 0;
    for (int i = 0; i < e; i++)
    {
        int v1 = listofEdges[i][0];
        int v2 = listofEdges[i][1];
        int w = listofEdges[i][2];
        if (findSet(v1) != findSet(v2))
        {
            A[index++] = v1;
            A[index++] = v2;
            Union(v1, v2);
            minCost += w;
            printf("%d \t %d \t  ---> %d \n", v1, v2, w);
        }
    }
    printf("\n");
    printf("MST Cost: %d\n", minCost);
    return 0;
}
