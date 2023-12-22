#include <stdio.h>

int ary[10][10];
int completed[10];
int n, cost = 0;

void takeInput() {
    printf("Enter the number of villages: ");
    scanf("%d", &n);

    printf("\nEnter the Cost Matrix\n");

    for (int i = 0; i < n; i++) {
        printf("\nEnter Elements of Row: %d\n", i + 1);
        for (int j = 0; j < n; j++) {
            scanf("%d", &ary[i][j]);
        }
        completed[i] = 0;
    }

    printf("\n\nThe cost list is:");

    for (int i = 0; i < n; i++) {
        printf("\n");
        for (int j = 0; j < n; j++) {
            printf("\t%d", ary[i][j]);
        }
    }
}

void mincost(int city) {
    int ncity;
    completed[city] = 1;
    printf("%d--->", city + 1);
    ncity = least(city);
    if (ncity == 999) {
        ncity = 0;
        printf("%d", ncity + 1);
        cost += ary[city][ncity];
        return;
    }
    mincost(ncity);
}

int least(int c) {
    int nc = 999;
    int min = 999, kmin = 0;

    for (int i = 0; i < n; i++) {
        if (ary[c][i] != 0 && completed[i] == 0) {
            if (ary[c][i] < min) {
                min = ary[c][i];
                kmin = i;
                nc = i;
            }
        }
    }

    if (min != 999)
        cost += min;

    return nc;
}

int main() {
    takeInput();
    printf("\n\nThe Path is:\n");
    mincost(0); // passing 0 because starting vertex
    printf("\n\nMinimum cost is %d\n ", cost);

    return 0;
}
/*

  {0, 10, 15, 20},
    {10, 0, 35,25},
    {15, 35, 0, 30},
    {20, 25, 30, 0}};
*/