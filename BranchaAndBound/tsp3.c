#include <stdio.h>
#include <stdbool.h>
#include<limits.h>

#define MAX_N 10

int n, cost[MAX_N][MAX_N], visited[MAX_N];
int mincost = INT_MAX;

void mincost(int city);
int calculate_bound(int city);

int main() {
    printf("Enter the number of cities: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
        visited[i] = 0;
    }

    mincost(0);

    printf("\nMinimum cost: %d\n", mincost);

    return 0;
}

void mincost(int city) {
    int i, ncity;

    visited[city] = 1;
    printf("%d -> ", city + 1);

    int current_cost = 0;
    for (i = 0; i < n; i++) {
        if (visited[i] == 0) {
            current_cost += cost[city][i];
        }
    }

    if (current_cost + calculate_bound(city) < mincost) {
        if (n == 1) {
            mincost = current_cost;
            printf("%d", city + 1);
        } else {
            for (i = 0; i < n; i++) {
                if (visited[i] == 0) {
                    mincost(i);
                }
            }
        }
    }

    visited[city] = 0;
    printf("\n");
}

int calculate_bound(int city) {
    int min = INT_MAX, min2 = INT_MAX, i;

    for (i = 0; i < n; i++) {
        if (visited[i] == 0) {
            if (cost[city][i] < min) {
                min2 = min;
                min = cost[city][i];
            } else if (cost[city][i] < min2) {
                min2 = cost[city][i];
            }
        }
    }

    if (min2 == INT_MAX) {
        return 0;
    } else {
        return min + min2;
    }
}
