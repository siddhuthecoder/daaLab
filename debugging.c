#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 99999

int **graph;
int nofVer;
int pathIndex = 0;

int trc(int **G, int s);
int **rowmin(int **g1);
int **colmin(int **g2);
int minim(int **s, int i, int k);
int cost(int **t, int k);
int **am(int rows, int cols);
void dm(int **matrix, int rows);
void display(int **f);
int *intsp;
int *path;

int main()
{
    printf("Enter the number of vertices: ");
    scanf("%d", &nofVer);
    graph = am(nofVer, nofVer);

    // Input code for the graph matrix
    for (int i = 0; i < nofVer; i++)
    {
        for (int j = 0; j < nofVer; j++)
        {
            if (i == j)
            {
                graph[i][j] = INF;
            }
            else
            {
                printf("Enter element m[%d][%d]: ", i, j);
                scanf("%d", &graph[i][j]);
            }
        }
    }

    for (int i = 0; i < nofVer; i++)
    {
        for (int j = 0; j < nofVer; j++)
        {
            printf("%d  ", graph[i][j]);
        }
        printf("\n");
    }

    intsp = (int *)malloc(nofVer * sizeof(int));
    path = (int *)malloc(nofVer * sizeof(int));

    for (int j = 0; j < nofVer; j++)
    {
        intsp[j] = 0;
    }
    intsp[0] = 1;
    int final = trc(graph, 0);
    printf("Final cost: %d\n", final);
    printf("The path is: ");
    for (int w = 0; w < nofVer; w++)
    {
        printf("%d ", path[w]);
    }

    dm(graph, nofVer);
    free(intsp);
    free(path);

    return 0;
}

int trc(int **G, int s)
{
    printf("hi\n");
    path[pathIndex++] = s;
    intsp[s] = 1;
    int **m = am(nofVer, nofVer);
    int **m2 = am(nofVer, nofVer);
    int **m4 = am(nofVer, nofVer);
    int **m5 = am(nofVer, nofVer);
    int c = cost(G, 0);
    m2 = rowmin(G);
    c = c + cost(m2, 1);
    printf("the total cost is %d", c);
    m = colmin(m2);
    display(m);
    m2 = m;
    int fcost[nofVer];
    for (int i = 0; i < nofVer; i++)
    {
        fcost[i] = INF;
    }

    for (int j = 1; j < nofVer; j++)
    {
        if (intsp[j] == 0)
        {
            int x = m2[s][j];
            m2[s][j] = INF;

            for (int k = 0; k < nofVer; k++)
            {

                m2[s][k] = INF;
                m2[k][j] = INF;
            }

            int **m1 = am(nofVer, nofVer);
            int **m3 = am(nofVer, nofVer);
            int c2 = cost(m, 0);
            m1 = rowmin(m2);
            c2 = c2 + cost(m1, 1);
            m3 = colmin(m1);
            fcost[j] = c + c2 + x;
            printf(" the cost of %d matricx is %d", j, fcost[j]);
            dm(m3, nofVer);
        }
    }

    int l = 0, min = INF;
    for (int d = 0; d < nofVer; d++)
    {
        if (fcost[d] < min)
        {
            min = fcost[d];
            l = d;
        }
    }
    printf(" the min is%d ", min);

    if (intsp[l] == 0)
    {
        m2[s][l] = INF;
        for (int e = 0; e < nofVer; e++)
        {
            m[s][e] = INF;
            m[e][l] = INF;
        }
        display(m);
        m4 = rowmin(m);
        m5 = colmin(m4);
        display(m5);

        trc(m, l);
    }

    return min;
}

int **rowmin(int **g1)
{
    for (int i = 0; i < nofVer; i++)
    {
        int minval = minim(g1, i, 0);
        if (minval < 90000)
        {
            for (int j = 0; j < nofVer; j++)
            {
                g1[i][j] = g1[i][j] - minval;
            }
        }
    }
    return g1;
}
int **colmin(int **g2)
{
    for (int i = 0; i < nofVer; i++)
    {
        int minval2 = minim(g2, i, 1);
        //	printf("minval2 is %d",minval2);
        if (minval2 < 90000)
        {
            for (int j = 0; j < nofVer; j++)
            {
                if (g2[j][i] != INF)
                {
                    g2[j][i] = g2[j][i] - minval2;
                }
            }
        }
    }
    // display(g2);
    return g2;
}
int minim(int **s, int i, int k)
{
    int min = 0;
    if (k == 0)
    {
        min = s[i][0];
        for (int j = 0; j < nofVer; j++)
        {
            if (s[i][j] < min)
            {
                min = s[i][j];
            }
        }
        // printf("the min in row %d is %d \n",i,min);
        return min;
    }
    if (k == 1)
    {
        min = s[0][i];
        for (int j = 0; j < nofVer; j++)
        {
            if (s[j][i] < min)
            {
                min = s[j][i];
            }
        }
        //	printf("the min in col %d is %d \n",i,min);
        return min;
    }
}
int cost(int **t, int k)
{
    // printf("the cost is called\n");
    int c = 0;
    if (k == 0)
    {
        for (int i = 0; i < nofVer; i++)
        {
            //	printf("cost is called \n");
            int r1 = minim(t, i, 0);
            //	int c1=minim(t,i,1);
            if (r1 < 90000)
            {
                c = c + r1;
            }
        }
        //	printf ("the cost is %d \n",c);
        return c;
    }
    if (k == 1)
    {
        for (int i = 0; i < nofVer; i++)
        {
            // printf("cost is called \n");
            int r1 = minim(t, i, 1);
            //	int c1=minim(t,i,1);
            if (r1 < 90000)
            {
                c = c + r1;
            }
        }
        //	printf ("the cost is %d \n",c);
        return c;
    }
}
int **am(int rows, int cols)
{
    int *matrix = (int *)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
        matrix[i] = (int *)malloc(cols * sizeof(int));
    return matrix;
}
void dm(int **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);
}
void display(int **f)
{
    for (int i = 0; i < nofVer; i++)
    {
        for (int j = 0; j < nofVer; j++)
        {
            printf("%d  ", f[i][j]);
        }
        printf("\n");
    }
}