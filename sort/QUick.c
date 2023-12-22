#include <stdio.h>
void swap(int *p,int *q){
    int temp;
    temp = *p;
    *p = *q;
    *q = temp;
}
int partition(int a[],int l,int h){
    int i,j,pivot;
    pivot = a[h];
    i = l-1;
    for(j = l;j<=h-1;j++){
        if(a[j]<pivot){
            i++;
            swap(&a[i],&a[j]);
        }
    }
    swap(&a[i+1],&a[h]);
    
    return i+1;
}

void Quick_sort(int a[],int l,int h){
    int PI;
    if(l<h){
        PI =partition(a,l,h);
        Quick_sort(a,l,PI-1);
        Quick_sort(a,PI+1,h);
    }
}
int main(){
    int N;
    printf("enter the size of the array:");
    scanf("%d",&N);
    int arr[N];
    printf("enter the elements of the array:");

    for(int i=0;i<N;i++){
        scanf("%d",&arr[i]);
    }
    Quick_sort(arr,0,N-1);
    printf("sorted array:\n");
    for (int i=0;i<N;i++){
        printf("%d\t",arr[i]);
    }
    return 0 ;
}
