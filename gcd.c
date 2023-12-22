#include <stdio.h>

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}



int main()
{
    int n,i;
    printf("Enter the no of elements");
    scanf("%d",&n);
    int arr[n];
    
    for (i = 0; i < n; i++)
    {
        printf("Enter the %d elemnt :");
        scanf("%d",&arr[i]);
        printf("\n");
    }
    printf("GCD of The given numbers",gcd4(arr));
}