#include <stdio.h>
#include <stdlib.h>
int MAX = 10;
struct Item
{
    float profit;
    float weight;
};
struct Node
{
    struct Item *item;
    int level;
    float upperBound;
    int path[10];
    int exclude[10];
    float lowerBound;
};
struct Item items[] = {{-10.00, 2.00}, {-10.00, 4.00}, {-12.00, 6.00}, {-18.00, 9.00}};

void printNode(struct Node *node,int n)
{
    float Profit=0.00;
    printf("\n");
    printf("Solution Vector: ");
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", node->exclude[i]);
        if(node->exclude[i]==1){
            Profit=Profit+(-(items[i].profit));
        }
    }
    printf("Profit is %.2f",Profit);
    printf("\n");
}
struct Node *createNode(struct Item *item, int n, int level, float upperBound, float lowerBound, int path[], int exclude[])
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node) + n * sizeof(int));
    if (node == NULL)
    {
        printf("Memory allocation error.\n");
        exit(0);
    }
    node->item = item;
    node->upperBound = upperBound;
    node->lowerBound = lowerBound;
    node->level = level;
    for (int i = 0; i < n; i++)
    {
        node->path[i] = path[i];
        node->exclude[i] = exclude[i];
    }
    return node;
}

void BothBoundCalculation(struct Node *node, int excluded[], int n, int KnapsackCapacity)
{
    int RemainWeight = KnapsackCapacity;
    float upperBound = 0, lowerBound = 0;
    for (int i = 0; i < n; i++)
    {
        if (excluded[i] != 0 && RemainWeight >= 0)
        {
            if (RemainWeight >= items[i].weight)
            {
                upperBound += items[i].profit;
                lowerBound += items[i].profit;
                RemainWeight = RemainWeight - items[i].weight;
            }
            else
            {
                float fraction = RemainWeight / items[i].weight;
                lowerBound += fraction * items[i].profit;
                RemainWeight = 0;
            }
        }
    }
    node->upperBound = upperBound;
    node->lowerBound = lowerBound;
}
void knapsackUsingBranchAndBound(int KnapsackCapacity, int noOfObjects)
{
    int patht[noOfObjects], excluded[noOfObjects];
    for (int i = 0; i < noOfObjects; i++)
    {
        patht[i] = 0;
        excluded[i] = 1;
    }
    struct Node *listofItems[2 * noOfObjects];
    int listofItemsN = 0;
    struct Node *root = createNode(NULL, noOfObjects, 0, 0, 0, patht, excluded);
    BothBoundCalculation(root, root->exclude, noOfObjects, KnapsackCapacity);
    listofItems[listofItemsN++] = root;
    while (listofItemsN > 0)
    {
        struct Node *min = listofItems[0];
        int index = 0;
        for (int i = 0; i < listofItemsN; i++)
        {
            if (listofItems[i]->upperBound < min->upperBound)
            {
                min = listofItems[i];
                index = i;
            }
        }
        listofItems[index] = listofItems[--listofItemsN];
        for (int i = 0; i < noOfObjects; i++)
        {
            patht[i] = min->path[i];
            excluded[i] = min->exclude[i];
        }
        if(min->level==noOfObjects){
            printf("HI this is siddhu from srikakulam ");
            printNode(min,noOfObjects);
            return ;
        }
        struct Node *IncludedObject = createNode(&items[min->level], noOfObjects, min->level + 1, min->upperBound, min->lowerBound, patht, excluded);
        listofItems[listofItemsN++] = IncludedObject;

        patht[min->level] = 0;
        excluded[min->level] = 0;
        struct Node *ExcludedObject = createNode(&items[min->level], noOfObjects, min->level + 1, min->upperBound, min->lowerBound, patht, excluded);
        BothBoundCalculation(ExcludedObject, ExcludedObject->exclude, noOfObjects, KnapsackCapacity);
        listofItems[listofItemsN++] = ExcludedObject;
       
        
    }

    free(root);
}
int main()
{

    int n = sizeof(items) / sizeof(items[0]);
    int KnapsackCapacity ;
    printf("Enter the KnapsaCK Capacity");
    scanf("%d",&KnapsackCapacity);
    int excluded[n];
    knapsackUsingBranchAndBound(KnapsackCapacity, n);
    return 0;
}
