#include<stdio.h>
void merge_sort(int a[],int l,int h);
void merge(int a[],int l,int mid,int h);

void main(){
    int n,i;
    printf("Enter the size of the array:");
    scanf("%d",&n);
    int a[n];
    printf("enter the elements of the array:");
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }

    merge_sort(a,0,n);
    printf("the sorted array is:");
    for(i=0;i<n;i++){
        printf("%d\t",a[i]);
    }
}
void merge_sort(int *a,int l,int h){
    int mid;
    if(l<h){
        int mid=(l+h)/2;
        merge_sort(a,l,mid);
        merge_sort(a,mid+1,h);
        merge(a,l,mid,h);
    }
}
void merge(int *a,int l,int mid,int h){
    int i,j,k,n1,n2;
    n1=mid-l+1;
    n2=h-mid;
    int L[n1],r[n2];
    for(i=0;i<n1;i++){
        L[i]=a[l+i];
    }
    for(j=0;j<n2;j++){
        r[j]=a[j+mid+1];
    }
    i=0;j=0;k=l;
    while(i<n1&&j<n2){
        if(L[i]<r[j]){
            a[k++]=L[i++];
        }
        else{
            a[k++]=r[j++];
        }
    }
    while(i<n1){
        a[k++]=L[i++];
    }
    while(j<n2){
        a[k++]=r[j++];
    }
}