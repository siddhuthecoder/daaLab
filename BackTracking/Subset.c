#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

int set[] = {1, 2, 1};
int sum = 3;
int n = sizeof(set) / sizeof(set[0]);
bool inclusion[MAX_SIZE];
int flag = 0;

void print_subset()
{
    printf("[");
    for (int i = 0; i < n; i++)
    {
        if (inclusion[i])
        {
            printf("%d ", set[i]);
        }
    }
    printf("]\n");
}

void helper(int i, int targetSum)
{
    flag = 0;

    if (targetSum == 0)
    {
        flag = 1;
        print_subset();
        return;
    }

    if (i == n || targetSum < 0)
    {
        return;
    }

    inclusion[i] = true;
    helper(i + 1, targetSum - set[i]);
    inclusion[i] = false;
    helper(i + 1, targetSum);
}

int main()
{
    helper(0, sum);
    if (flag == 0)
    {
        printf("hi this is siddhu from srikakulam");
    }
    return 0;
}
