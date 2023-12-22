#include <stdio.h>
#include <limits.h>

#define MAX_V 10 // Maximum number of cities

int minTourCost = INT_MAX;
int visited[MAX_V];
int WeightGraph[MAX_V][MAX_V];
int** reduction(int** a ){
    
}
void tsp(int pos, int count, int tourLength, int V)
{
    if (count == V)
    {
        tourLength += WeightGraph[pos][0];
        if (tourLength < minTourCost)
        {
            minTourCost = tourLength;
        }
    }
    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            tsp(i, count + 1, tourLength + WeightGraph[pos][i], V);
            visited[i] = 0;
        }
    }
}

int main()
{
    int V, source;
    printf("Enter the number of cities (max %d): ", MAX_V);
    scanf("%d", &V);

    if (V <= 0 || V > MAX_V)
    {
        printf("Invalid number of cities.\n");
        return 1;
    }

    printf("Enter the adjacency matrix for the graph:\n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            scanf("%d", &WeightGraph[i][j]);
        }
        visited[i] = 0;
    }

    printf("Enter the source vertex (0 to %d): ", V - 1);
    scanf("%d", &source);

    if (source < 0 || source >= V)
    {
        printf("Invalid source vertex.\n");
        return 1;
    }

    visited[source] = 1;
    tsp(source, 1, 0, V);
    printf("Minimum tour cost: %d\n", minTourCost);

    return 0;
}
