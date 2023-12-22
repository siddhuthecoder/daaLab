#include <stdio.h>

#define V 5
#define INF 10000

int d[V][V] = {
    {0, 3, 8, INF, -4},
    {INF, 0, INF, 1, 7},
    {INF, 4, 0, INF, INF},
    {2, INF, -5, 0, INF},
    {INF, INF,  INF,6, 0},
};

int p[V][V] = {
    {0, 1, 1, INF, 1},
    {INF, 0, INF, 2, 2},
    {INF, 3, 0, INF, INF},
    {4, INF, 4, 0, INF},
    {INF, INF, 5, INF, 0},
};

void floydWarshall()
{
    int i, j, k;

    for (k = 0; k < V; k++)
    {
        for (i = 0; i < V; i++)
        {
            for (j = 0; j < V; j++)

            {
                if(i==k||j==k){
                    d[i][j]=d[i][j];
                }
                else if (i==j)
                {
                    d[i][j]=0;
                }
                else if(d[i][k] != INF && d[k][j] != INF && d[i][k] + d[k][j] < d[i][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = p[k][j]; // Update predecessor matrix
                }
            }
        }
    }
}

int main()
{
    floydWarshall();

    // Printing the distance matrix
    printf("Distance Matrix:\n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (d[i][j] == INF)
            {
                printf("INF\t");
            }
            else
            {
                printf("%d\t", d[i][j]);
            }
        }
        printf("\n");
    }

    // Printing the predecessor matrix
    printf("\nPredecessor Matrix:\n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            printf("%d\t", p[i][j]);
        }
        printf("\n");
    }

    return 0;
}
