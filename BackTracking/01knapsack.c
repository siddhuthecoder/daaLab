#include <stdio.h>

struct Item
{
    int profit;
    int weight;
};

int maxProfit = 0; // Initialize maxProfit to 0
int chosenItems[100]; // Array to store chosen items

void printSolution(int chosen[], int n)
{
    printf("Chosen items (0/1):\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", chosen[i]);
    }
    printf("\n");
}

void backtracking(struct Item items[], int n, int level, int capacity, int weight, int chosen[], int value)
{
    if (weight > capacity || level == n)
    {
        if (value > maxProfit && weight <= capacity)
        {
            maxProfit = value;
            for (int i = 0; i < n; i++)
            {
                chosenItems[i] = chosen[i]; 
            }
        }
        return;
    }

    chosen[level] = 1;
    backtracking(items, n, level + 1, capacity, weight + items[level].weight, chosen, value + items[level].profit);
    chosen[level] = 0; 
    backtracking(items, n, level + 1, capacity, weight, chosen, value);
}

int main()
{
    struct Item items[] = {{60, 10}, {100, 20}, {120, 30}};
    int capacity = 50;
    int n = sizeof(items) / sizeof(items[0]);

    int chosen[n];
    backtracking(items, n, 0, capacity, 0, chosen, 0);

    printf("Maximum Profit: %d\n", maxProfit);
    printSolution(chosenItems, n);

    return 0;
}
