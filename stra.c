#include <stdio.h>

void add(int n, int A[][n], int B[][n], int C[][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int n, int A[][n], int B[][n], int C[][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int n, int A[][n], int B[][n], int C[][n]) {
    if (n < 2) {
        for (int i = 0; i < n; i++) {
           for (int j = 0; j < n; j++) {
                C[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        } 
        return;
    }

    int res = n / 2;
    int A11[res][res], A12[res][res], A21[res][res], A22[res][res];
    int B11[res][res], B12[res][res], B21[res][res], B22[res][res];
    int C11[res][res], C12[res][res], C21[res][res], C22[res][res];
    int P1[res][res], P2[res][res], P3[res][res], P4[res][res], P5[res][res], P6[res][res], P7[res][res];
    int temp1[res][res], temp2[res][res];

    for (int i = 0; i < res; i++){
        for (int j = 0; j < res; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + res];
            A21[i][j] = A[i + res][j];
            A22[i][j] = A[i + res][j + res];
            
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + res];
            B21[i][j] = B[i + res][j];
            B22[i][j] = B[i + res][j + res];
        }}
    add(res, A11, A22, temp1);
    add(res, B11, B22, temp2);
    strassen(res, temp1, temp2, P1);

    add(res, A21, A22, temp1);
    strassen(res, temp1, B11, P2);

    subtract(res, B12, B22, temp1);
    strassen(res, A11, temp1, P3);

    subtract(res, B21, B11, temp1);
    strassen(res, A22, temp1, P4);

    add(res, A11, A12, temp1);
    strassen(res, temp1, B22, P5);

    subtract(res, A21, A11, temp1);
    add(res, B11, B12, temp2);
    strassen(res, temp1, temp2, P6);

    subtract(res, A12, A22, temp1);
    add(res, B21, B22, temp2);
    strassen(res, temp1, temp2, P7);

    add(res, P5, P4, temp1);
    add(res, temp1, P6, temp2);
    subtract(res, temp2, P2, C11);

    add(res, P1, P2, C12);
    add(res, P3, P4, C21);

    add(res, P5, P1, temp1);
    subtract(res, temp1, P3, temp2);
    subtract(res, temp2, P7, C22);

    for (int i = 0; i < res; i++){
        for (int j = 0; j < res; j++)
        {
            C[i][j] = C11[i][j];    
            C[i][j + res] = C12[i][j];
            C[i + res][j] = C21[i][j];
            C[i + res][j + res] = C22[i][j];
        }
    }
}

int main() {
    int n;

    printf("Please Enter the Size of the Matrix: ");
    scanf("%d", &n);

    if (n < 2) {
        printf("Matrix size should be at least 2x2 for Strassen's algorithm.\n");
        return 1;
    }

    int A[n][n], B[n][n], C[n][n];

    printf("Enter values for matrix A (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter values for matrix B (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    strassen(n, A, B, C);

    printf("Resultant matrix C (A * B):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }
     for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", B[i][j]);
        printf("\n");
    }

    return 0;
}
