#include <stdio.h>
#include <stdlib.h>

struct item
{
    int object;
    float profit;
    float weight;
    float pwRatio;
    float takenWeight;
};

void merge(struct item *arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    struct item L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i].pwRatio >= R[j].pwRatio)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(struct item *arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main()
{

    int noOfObjects;
    printf("Enter the number of objects: ");
    scanf("%d", &noOfObjects);

    struct item Arr[noOfObjects];

    for (int i = 0; i < noOfObjects; i++)
    {
        printf("Enter profit and weight for object %d: ", i + 1);
        scanf("%f %f", &Arr[i].profit, &Arr[i].weight);
        Arr[i].object = i + 1;
        Arr[i].pwRatio = Arr[i].profit / Arr[i].weight;
        Arr[i].takenWeight = 0.0;
    }
    mergeSort(Arr, 0, noOfObjects - 1);
    float capcity;
    printf("Enter the capacity of the Knapsack");
    scanf("%f", &capcity);
    float RemainWeight = capcity;
    int i = 0;

    while (i < noOfObjects && RemainWeight > 0.0)
    {

        if (Arr[i].weight <= RemainWeight)
        {
            Arr[i].takenWeight = 1.0;
            RemainWeight = RemainWeight - Arr[i].weight;
        }
        else
        {
            float help = RemainWeight / Arr[i].weight;
            Arr[i].takenWeight = help;
            RemainWeight = 0;
        }
        i++;
    }
    for (int i = 0; i < noOfObjects - 1; i++)
    {
        for (int j = 0; j < noOfObjects - i - 1; j++)
        {
            if (Arr[j].object > Arr[j + 1].object)
            {

                struct item temp = Arr[j];
                Arr[j] = Arr[j + 1];
                Arr[j + 1] = temp;
            }
        }
    }

    // Print the sorted result based on object numbers
    printf("\nSorted Result based on Object Numbers:\n");
    for (int i = 0; i < noOfObjects; i++)
    {
        printf("Object No %d \t TakenWeight👝 %.2f\n", Arr[i].object, Arr[i].takenWeight);
    }

    float totalProfit = 0.0;
    for (int i = 0; i < noOfObjects; i++)
    {
        totalProfit += Arr[i].profit * Arr[i].takenWeight;
    }

    printf("Total Profit 💱: %.2f\n", totalProfit);

    return 0;
}
