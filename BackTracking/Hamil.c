#include <stdio.h>
#include <stdbool.h>

#define N 6
bool hasCycle;
int path[N];
bool visited[N];

int graph[N][N] = {
    {0, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 0, 0},
    {0, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1},
    {1, 1, 0, 0, 1, 0},
};

bool isSafe(int pos, int v)
{
    if (!graph[path[pos - 1]][v])
        return false;

    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

void FindHamCycle(int pos)
{
    if (pos == N)
    {
        if (graph[path[pos - 1]][path[0]] != 0)
        {
            path[pos] = path[0];
            printf("Hamiltonian Cycle: ");
            for (int i = 0; i <= pos; i++)
                printf("%d ", path[i]);
            printf("\n");
            hasCycle = true;
        }
        return;
    }

    for (int v = 1; v < N; v++)
    {
        if (isSafe(pos, v) && !visited[v])
        {
            path[pos] = v;
            visited[v] = true;
            FindHamCycle(pos + 1);
            visited[v] = false;
        }
    }
}

int main()
{
    
    hasCycle = false;
    for (int i = 0; i < N; i++)
        visited[i] = false;

    path[0] = 0;
    visited[0] = true;

    FindHamCycle(1);

    if (!hasCycle)
    {
        printf("No Hamiltonian Cycle possible\n");
        return 1;
    }

    return 0;
}
