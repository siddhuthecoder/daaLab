#include <stdio.h>

#define v 5

int rank[v];
int parent[v];
int A[v];
int listofEdges[6][3] = {{1, 2, 10}, {1, 3, 30}, {2, 5, 60}, {2, 4, 50}, {4, 5, 60}, {2, 3, 40}};

int findSet(int i) {
    if (parent[i] == i) {
        return i;
    } else {
        int res = findSet(parent[i]);
        parent[i] = res;
        return res;
    }
}

void makeSet() {
    int i;
    for (i = 0; i < v; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

void Union(int v1, int v2) {
    int r1 = rank[v1];
    int r2 = rank[v2];
    if (r1 > r2) {
        parent[v2] = parent[v1];
    } else if (r1 < r2) {
        parent[v1] = parent[v2];
    } else {
        parent[v2] = parent[v1];
        rank[v1] = rank[v1] + 1;
    }
}

void merge(int arr[][3], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1][3], R[n2][3];

    for (i = 0; i < n1; i++) {
        L[i][0] = arr[left + i][0];
        L[i][1] = arr[left + i][1];
        L[i][2] = arr[left + i][2];
    }
    for (j = 0; j < n2; j++) {
        R[j][0] = arr[mid + 1 + j][0];
        R[j][1] = arr[mid + 1 + j][1];
        R[j][2] = arr[mid + 1 + j][2];
    }

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i][2] <= R[j][2]) {
            arr[k][0] = L[i][0];
            arr[k][1] = L[i][1];
            arr[k][2] = L[i][2];
            i++;
        } else {
            arr[k][0] = R[j][0];
            arr[k][1] = R[j][1];
            arr[k][2] = R[j][2];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k][0] = L[i][0];
        arr[k][1] = L[i][1];
        arr[k][2] = L[i][2];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k][0] = R[j][0];
        arr[k][1] = R[j][1];
        arr[k][2] = R[j][2];
        j++;
        k++;
    }
}

void mergeSort(int arr[][3], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void SortTheEdges() {
    mergeSort(listofEdges, 0, 5);
}

int main() {
    int i, index = 0;

    makeSet();
    SortTheEdges();

    for (i = 0; i < v; i++) {
        int v1 = listofEdges[i][0];
        int v2 = listofEdges[i][1];
        int w = listofEdges[i][2];

        if (findSet(v1) != findSet(v2)) {
            A[index++] = v1;
            A[index++] = v2;
            Union(v1, v2);
            printf("%d \t %d \t  ---> %d \n", v1, v2, w);
        }
    }

    return 0;
}
