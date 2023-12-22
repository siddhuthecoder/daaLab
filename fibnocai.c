#include <stdio.h>
int fibonacci();
int main()
{
    int n, t3 = 0, i = 1;
    do{
    printf("Enter the No Terms ");
    scanf("%d", &n);
    }while(n<0);
    while (i <= n)
    {
        printf("%d", fibonacci(i));
        i++;
    }
}
int fibonacci(int n)
{

    if (n == 1)
    {
        return 0;
    }
    if (n == 2)
    {
        return 1;
    }
    return fibonacci(n - 2) + fibonacci(n - 1);
}