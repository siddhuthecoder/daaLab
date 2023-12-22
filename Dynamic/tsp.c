#include <stdio.h>
#include <limits.h>
int g(int start, int source, int count, int arr[], int E[][count])
{
    int min = INT_MAX, k = 0;
    arr[source] = 1;
    for (int i = 0; i < count; i++)
    {
        if (arr[i] != 1)
        {
            if (E[source][i])
            {
                int c = g(start, i, count, arr, E);
                arr[i] = 0;
                if (c != INT_MAX && min > (E[source][i] + c))
                    min = E[source][i] + c;
            }
            k++;
        }
    }
    if (k == 0)
    {
        if (E[source][start] || count == 1)
            return E[source][start];
        else
            return INT_MAX;
    }
    return min;
}
int main()

{
    int v;
    printf("Enter no of vertices: ");
    scanf("%d", &v);
    if (v > 0)
    {
        int S[v], E[v][v];
        printf("Enter adjacency matrix of graph\n");
        for (int i = 0; i < v; i++)
        {
            for (int j = 0; j < v; j++)
            {
                scanf("%d", &E[i][j]);
            }
            S[i] = 0;
        }
        int start;
        printf("Enter source vertex : ");
        scanf("%d", &start);
        if (start > 0 && start < v + 1)
        {
            int cost = g(start - 1, start - 1, v, S, E);
            if (cost != INT_MAX)
                printf("Minimum cost = %d\n", cost);
            else
                printf("There is no tour possible\n");
        }
        return 0;
    }
}