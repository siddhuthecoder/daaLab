#include <stdio.h>
#include <stdbool.h>
#define V 4

int M[V][V] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};

void printMatrix()
{
    printf("\n");
    int i, j;
    for (i = 0; i < V; i++)
    {
        for (j = 0; j < V; j++)
        {
            if (M[i][j] == 1)
            {
                printf("👸 \t");
                // printf("\033[1;37m👸\t\033[0m ");
            }
            else
            {
                printf("0\t");
            }
        }
        printf("\n");
    }
}

bool isSafe(int row, int col)
{
    int i, j;

    for (i = 0; i < col; i++)
    {
        if (M[row][i])
        {
            return false;
        }
    }

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (M[i][j])
        {
            return false;
        }
    }

    for (i = row, j = col; j >= 0 && i < V; i++, j--)
    {
        if (M[i][j])
        {
            return false;
        }
    }

    return true;
}

bool nQueenSol(int col)
{
    int i;
    if (col >= V)
    {
        printMatrix();
        return true;
    }
    for (i = 0; i < V; i++)
    {
        if (isSafe(i, col))
        {
            M[i][col] = 1;
            if (nQueenSol(col + 1))
            {
                return true;
            }
            M[i][col] = 0;
        }
    }
    return false;
}

int main()
{
    if (!nQueenSol(0))
    {
        printf("We can't find the Solution");
        return false;
    }
    

    return 0;
}
