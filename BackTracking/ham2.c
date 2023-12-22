#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Number of vertices in the graph
#define V 5

void printSolution(int path[], int pathSize);

/* A utility function to check if the vertex v can be added at
   index 'pos' in the Hamiltonian Path constructed so far (stored
   in 'path[]') */
bool isSafe(int v, bool graph[V][V], int path[], int pos)
{
    /* Check if this vertex is an adjacent vertex of the previously
       added vertex. */
    if (graph[path[pos - 1]][v] == 0)
        return false;

    /* Check if the vertex has already been included.
      This step can be optimized by creating an array of size V */
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

/* A recursive utility function to solve Hamiltonian path problem */
bool hamPathUtil(bool graph[V][V], int path[], int pos)
{
    /* base case: If all vertices are included in Hamiltonian Path */
    if (pos == V)
    {
        // Print the current path
          // first vertex
        if (graph[path[pos - 1]][path[0]] == 1){
        printSolution(path, V);
        }
        return false; // Continue the search for more paths
    }

    // Try different vertices as a next candidate in Hamiltonian Path.
    for (int v = 0; v < V; v++)
    {
        /* Check if this vertex can be added to Hamiltonian Path */
        if (isSafe(v, graph, path, pos))
        {
            path[pos] = v;

            /* recur to construct the rest of the path */
            if (hamPathUtil(graph, path, pos + 1))
                return true;

            /* If adding vertex v doesn't lead to a solution,
               then remove it */
            path[pos] = -1;
        }
    }

    /* If no vertex can be added to Hamiltonian Path constructed so far,
       then return false */
    return false;
}

/* This function solves the Hamiltonian Path problem using Backtracking.
  It mainly uses hamPathUtil() to solve the problem. */
void hamPath(bool graph[V][V])
{
    int *path = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++)
        path[i] = -1;

    /* Let us put vertex 0 as the first vertex in the path. */
    path[0] = 0;
    hamPathUtil(graph, path, 1);

    free(path); // Release memory
}

/* A utility function to print a solution */
void printSolution(int path[], int pathSize)
{
    printf("Hamiltonian Path: ");
    for (int i = 0; i < pathSize; i++)
        printf("%d ", path[i]);
    printf("\n");
}

// Driver program to test the above function
int main()
{
    /* Let us create the following graph
       (0)--(1)--(2)
        |   / \   |
        |  /   \  |
        | /     \ |
       (3)-------(4)    */
    bool graph1[V][V] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0},
    };

    printf("Paths in Graph 1:\n");
    hamPath(graph1);

    /* Let us create the following graph
       (0)--(1)--(2)
        |   / \   |
        |  /   \  |
        | /     \ |
       (3)       (4)    */
    bool graph2[V][V] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {1, 1, 0, 0, 0},
        {0, 1, 1, 0, 0},
    };

    printf("\nPaths in Graph 2:\n");
    hamPath(graph2);

    return 0;
}
