#include <stdio.h>

#include <limits.h>



#define MAX_VERTICES 1000



int graph[MAX_VERTICES][MAX_VERTICES];

int visited[MAX_VERTICES];

int parent[MAX_VERTICES];

int key[MAX_VERTICES];



void prim(int n) {

    int i, j, u, min;

    

    // Initialize all keys to infinity

    for (i = 0; i < n; i++) {

        key[i] = INT_MAX;

    }



    // Set the key of the first vertex to 0

    key[0] = 0;

    parent[0] = -1;



    // Find the MST

    for (i = 0; i < n - 1; i++) {

        // Find the vertex with the minimum key value

        min = INT_MAX;

        for (j = 0; j < n; j++) {

            if (!visited[j] && key[j] < min) {

                min = key[j];

                u = j;

            }

        }



        // Mark the vertex as visited

        visited[u] = 1;



        // Update the key values of adjacent vertices

        for (j = 0; j < n; j++) {

            if (graph[u][j] && !visited[j] && graph[u][j] < key[j]) {

                parent[j] = u;

                key[j] = graph[u][j];

            }

        }

    }



    // Print the MST

    printf("Edges in the MST:\n");

    for (i = 1; i < n; i++) {

        printf("(%d, %d) %d\n", parent[i], i, graph[parent[i]][i]);

    }

}



int main() {

    int n, i, j;



    printf("Enter the number of vertices: ");

    scanf("%d", &n);



    printf("Enter the adjacency matrix:\n");

    for (i = 0; i < n; i++) {

        for (j = 0; j < n; j++) {

            scanf("%d", &graph[i][j]);

        }

    }



    prim(n);



    return 0;

}
