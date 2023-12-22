#include <stdio.h>
struct Item {
    int value;
    int weight;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}
int knapsackRec(int capacity, struct Item items[], int n, int level, int weight, int value) {
   
}
int knapsack(int capacity, struct Item items[], int n) {
    return knapsackRec(capacity, items, n, 0, 0, 0);
}

int main(int argc, char const *argv[])
{

    int capacity = 50; 
    struct Item items[] = {{60, 10}, {100, 20}, {120, 30}}; 
    int n = sizeof(items) / sizeof(items[0]); 

    int maxProfit = knapsack(capacity, items, n);
    printf("Maximum profit: %d\n", maxProfit);
    return 0;
}
