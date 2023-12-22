#include <stdio.h>

struct Item {
    int profit;
    int weight;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int Knapsack(struct Item items[], int capacity, int n, int level, int weight, int profit, int chosen[]) {
    if (weight > capacity) {
        return 0;
    }
    if (level == n) {
        return profit;
    }

    int includeProfit = Knapsack(items, capacity, n, level + 1, weight + items[level].weight,
                                 profit + items[level].profit, chosen);
    int excludeProfit = Knapsack(items, capacity, n, level + 1, weight, profit, chosen);

    if (includeProfit > excludeProfit) {
        chosen[level] = 1; 
        return includeProfit;
    } else {
        chosen[level] = 0; 
        return excludeProfit;
    }
}

int main() {
    struct Item items[] = {{60, 10}, {100, 20}, {120, 30}};
    int capacity = 50;
    int n = 3;
    int chosen[n]; 
    
    int profit = Knapsack(items, capacity, n, 0, 0, 0, chosen);
    printf("Maximum Profit: %d\n", profit);
    printf("Objects chosen (1: Included, 0: Excluded): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", chosen[i]);
    }
    return 0;
}
