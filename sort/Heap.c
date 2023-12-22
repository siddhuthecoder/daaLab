#include <stdio.h>

void heapify(int a[], int n, int i);
void heapsort(int a[], int n);
void swap(int *a, int *b);

int main() {
    int n;
    printf("Enter the size of an array: ");
    scanf("%d", &n);
    int a[n];
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    heapsort(a, n);
    printf("the Sorted array is: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}

void heapsort(int a[], int n) {
    for (int j = (n / 2) - 1; j >= 0; j--) {
        heapify(a, n, j);
    }
    for (int j = n - 1; j > 0; j--) {
        swap(&a[0], &a[j]);
        heapify(a, j, 0);
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int a[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && a[left] > a[largest]) {
        largest = left;
    }
    if (right < n && a[right] > a[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap(&a[i], &a[largest]);
        heapify(a, n, largest);
    }
}