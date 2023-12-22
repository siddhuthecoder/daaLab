#include <stdio.h>
#include <limits.h>
#define V 4 // Number of citie
int minTourCost = INT_MAX;
int visited[V];
int WeightGraph[V][V] = {
    {0, 10, 15, 20},
    {10, 0, 35,25},
    {15, 35, 0, 30},
    {20, 25, 30, 0}};

void tsp(int pos, int count, int tourLength)
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
            tsp(i, count + 1, tourLength + WeightGraph[pos][i]);
            visited[i] = 0;
        }
    }
}
int main()
{
    for (int i = 0; i < V; i++)
    {
        visited[i] = 0;
    }
    visited[0] = 1;
    tsp(0, 1, 0);
    printf("Minimum tour cost: %d\n", minTourCost);
    return 0;
}