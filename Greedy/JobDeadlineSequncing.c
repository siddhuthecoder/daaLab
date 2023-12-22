#include <stdio.h>
#include <stdlib.h>

struct node {
    int job;
    int profit;
    int deadline;
};

void printArray(struct node Arr[], int n);
void bubbleSortByProfit(struct node Arr[], int n);
int findMaxDeadline(struct node Arr[], int n) {
    int max = -1;

    for (int i = 0; i < n; i++) {
        if (Arr[i].deadline > max) {
            max = Arr[i].deadline;
        }
    }

    return max;
}

int main() {
    int i, n=6, j;
    struct node *Arr = malloc(n * sizeof(struct node));

    Arr[0].job = 1;
    Arr[0].profit = 24;
    Arr[0].deadline = 5;

    Arr[1].job = 2;
    Arr[1].profit = 18;
    Arr[1].deadline = 3;

    Arr[2].job = 3;
    Arr[2].profit = 22;
    Arr[2].deadline = 3;

    Arr[3].job = 4;
    Arr[3].profit = 30;
    Arr[3].deadline = 2;

    Arr[4].job = 5;
    Arr[4].profit = 12;
    Arr[4].deadline = 4;
    
    Arr[5].job = 6;
    Arr[5].profit = 10;
    Arr[5].deadline = 2;

    printf("Original array:\n");
    printArray(Arr, n);

    bubbleSortByProfit(Arr, n);

    printf("\nSorted array by profit (descending order):\n");
    printArray(Arr, n);

    int maxProf = findMaxDeadline(Arr, n);
    printf("Max profit %d",maxProf);
    int result[maxProf];
    for (i = 0; i < maxProf; i++) {
        result[i] = -1;
    }
    for (i = 0; i < n; i++) {
        int deadline = Arr[i].deadline;
        for (j = deadline; j >= 0; j--) {
            if (result[j] == -1) { 
                result[j] = Arr[i].job;
                break;
            }
        }
    }

    printf("\nResult array:\n");
    for (i = 0; i < maxProf; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    free(Arr);
    
    return 0;
}

void printArray(struct node Arr[], int n) {
    printf("Contents of the array:\n");
    for (int i = 0; i < n; i++) {
        printf("Job: %d, Profit: %d, Deadline: %d\n", Arr[i].job, Arr[i].profit, Arr[i].deadline);
    }
}

void bubbleSortByProfit(struct node Arr[], int n) {
    int swapped;
    struct node temp;

    for (int i = 0; i < n - 1; i++) {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (Arr[j].profit < Arr[j + 1].profit) {
                temp = Arr[j];
                Arr[j] = Arr[j + 1];
                Arr[j + 1] = temp;
                swapped = 1;
            }
        }

       
        if (swapped == 0) {
            break;
        }
    }
}
