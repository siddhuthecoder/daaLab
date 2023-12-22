#include <stdio.h>
#include <stdbool.h>

#define N 6

// To check if there exists at least 1 Hamiltonian cycle
bool hasCycle;

// Function to check if a vertex v can be added at index pos in the Hamiltonian Cycle
bool isSafe(int v, int graph[N][N], int path[], int pos)
{
    // If the vertex is adjacent to the vertex of the previously added vertex
    if (graph[path[pos - 1]][v] == 0)
        return false;

    // If the vertex has already been included in the path
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    // Both the above conditions are not true, return true
    return true;
}

// Recursive function to find all Hamiltonian cycles
void FindHamCycle(int graph[N][N], int pos, int path[], bool visited[])
{
    // If all vertices are included in Hamiltonian Cycle
    if (pos == N)
    {
        // If there is an edge from the last vertex to the source vertex
        if (graph[path[pos - 1]][path[0]] != 0)
        {
            // Include source vertex into the path and print the path
            path[pos] = 0;
            for (int i = 0; i <= pos; i++)
            {
                printf("%d ", path[i]);
            }
            printf("\n");

            // Update the hasCycle as true
            hasCycle = true;
        }
        return;
    }

    // Try different vertices as the next vertex
    for (int v = 0; v < N; v++)
    {
        // Check if this vertex can be added to Cycle
        if (isSafe(v, graph, path, pos) && !visited[v])
        {
            path[pos] = v;
            visited[v] = true;

            // Recur to construct the rest of the path
            FindHamCycle(graph, pos + 1, path, visited);

            // Remove current vertex from path and process other vertices
            visited[v] = false;
        }
    }
}

// Function to find all possible Hamiltonian cycles
void hamCycle(int graph[N][N])
{
    // Initially value of boolean flag is false
    hasCycle = false;

    // Store the resultant path
    int path[N + 1];
    path[0] = 0;

    // Keeps the track of the visited vertices
    bool visited[N];

    for (int i = 0; i < N; i++)
        visited[i] = false;

    visited[0] = true;

    // Function call to find all Hamiltonian cycles
    FindHamCycle(graph, 1, path, visited);

    if (!hasCycle)
    {
        // If no Hamiltonian Cycle is possible for the given graph
        printf("No Hamiltonian Cycle possible\n");
        return;
    }
}

int main()
{
    int graph[N][N] = {
        {0, 1, 1, 0, 0, 1},
        {1, 0, 1, 0, 1, 1},
        {1, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1},
        {1, 1, 0, 0, 1, 0},
    };

    hamCycle(graph);

    return 0;
}
