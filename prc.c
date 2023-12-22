#include <stdio.h>

void swap(int arr[], int a, int b)

{

    int temp = arr[a];

    arr[a] = arr[b];

    arr[b] = temp;

}

int main()

{

    int total;

    printf("Enter the total number of containers : ");

    scanf("%d", &total);

    int sol_vec[total];

    int items[total];

    int weight[total];

    int capacity;

    for (int i = 0; i < total; i++)

    {

        items[i] = i + 1;

        printf("Enter Weight %d: ", i + 1);

        scanf("%d", &weight[i]);

    }

    printf("Enter Capacity: ");

    scanf("%d", &capacity);

    for (int i = 0; i < total; i++)

    {

        for (int j = i; j < total; j++)

        {

            if (weight[i] > weight[j])

            {

                swap(items, i, j);

                swap(weight, i, j);

            }

        }

    }

    printf("\n");

    printf("After Sorting: \n");

    printf("Items\tWeight\n");

    for (int i = 0; i < total; i++)

    {

        printf("%d\t%d", items[i], weight[i]);

        printf("\n");

    }

    for (int i = 0; i < total; i++)

    {

        if (capacity < weight[i])

        {

            sol_vec[items[i] - 1] = 0;

            continue;

        }

        else if (capacity >= weight[i])

        {

            sol_vec[items[i] - 1] = 1;

            capacity = capacity - weight[i];

        }

    }

    printf("\n");

    printf("Solution Vector: ");

    for (int i = 0; i < total; i++)

    {

        printf("%d\t", sol_vec[i]);

    }

}
