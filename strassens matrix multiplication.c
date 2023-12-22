#include <stdio.h>
#include <stdlib.h>



void deallocateMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);
}
int **addMatrix(int **A, int **B, int size,int a) {
    int **C = allocateMatrix(size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
        	if(a==1)
            	C[i][j] = A[i][j] + B[i][j];
            else
            	C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}
int **allocateMatrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
        matrix[i] = (int *)malloc(cols * sizeof(int));
    return matrix;
}
int **strassenMultiply(int **A, int **B, int size) {
    if (size == 1) {
        int **C = allocateMatrix(1, 1);
        C[0][0] = A[0][0] * B[0][0];
        return C;
    } else {
        int **C = allocateMatrix(size, size);
        int newSize = size / 2;
        int **A11 = allocateMatrix(newSize, newSize);
        int **A12 = allocateMatrix(newSize, newSize);
        int **A21 = allocateMatrix(newSize, newSize);
        int **A22 = allocateMatrix(newSize, newSize);
        int **B11 = allocateMatrix(newSize, newSize);
        int **B12 = allocateMatrix(newSize, newSize);
        int **B21 = allocateMatrix(newSize, newSize);
        int **B22 = allocateMatrix(newSize, newSize);
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + newSize];
                A21[i][j] = A[i + newSize][j];
                A22[i][j] = A[i + newSize][j + newSize];
                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + newSize];
                B21[i][j] = B[i + newSize][j];
                B22[i][j] = B[i + newSize][j + newSize];
            }
        }
        int **P1 = strassenMultiply(A11, addMatrix(B12, B22, newSize,0), newSize);
        int **P2 = strassenMultiply(addMatrix(A11, A12, newSize,1), B22, newSize);
        int **P3 = strassenMultiply(addMatrix(A21, A22, newSize,1), B11, newSize);
        int **P4 = strassenMultiply(A22, addMatrix(B21, B11, newSize,0), newSize);
        int **P5 = strassenMultiply(addMatrix(A11, A22, newSize,1), addMatrix(B11, B22, newSize,1), newSize);
        int **P6 = strassenMultiply(addMatrix(A12, A22, newSize,0), addMatrix(B21, B22, newSize,1), newSize);
        int **P7 = strassenMultiply(addMatrix(A11, A21, newSize,0), addMatrix(B11, B12, newSize,1), newSize);
        int **C11 = addMatrix(addMatrix(addMatrix(P5, P4, newSize,1), P6, newSize,1), P2, newSize,0);
        int **C12 = addMatrix(P1, P2, newSize,1);
        int **C21 = addMatrix(P3, P4, newSize,1);
        int **C22 = addMatrix(addMatrix(addMatrix(P5, P1, newSize,1), P3, newSize,0), P7, newSize,0);
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                C[i][j] = C11[i][j];
                C[i][j + newSize] = C12[i][j];
                C[i + newSize][j] = C21[i][j];
                C[i + newSize][j + newSize] = C22[i][j];
            }
        }
        deallocateMatrix(A11, newSize);
        deallocateMatrix(A12, newSize);
        deallocateMatrix(A21, newSize);
        deallocateMatrix(A22, newSize);
        deallocateMatrix(B11, newSize);
        deallocateMatrix(B12, newSize);
        deallocateMatrix(B21, newSize);
        deallocateMatrix(B22, newSize);
        deallocateMatrix(P1, newSize);
        deallocateMatrix(P2, newSize);
        deallocateMatrix(P3, newSize);
        deallocateMatrix(P4, newSize);
        deallocateMatrix(P5, newSize);
        deallocateMatrix(P6, newSize);
        deallocateMatrix(P7, newSize);
        return C;
    }
}
void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}
int main() {
    int n;
    printf("Enter the size of matrices (power of 2): ");
    scanf("%d", &n);
    if ((n & (n - 1)) != 0) {
        printf("Matrix size must be a power of 2 .\n");
        return 1;
    }
    int **A = allocateMatrix(n, n);
    int **B = allocateMatrix(n, n);
    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);
    printf("Enter elements of matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);
    int **C = strassenMultiply(A, B, n);
    printf("Matrix A:\n");
    printMatrix(A, n, n);
    printf("Matrix B:\n");
    printMatrix(B, n, n);
    printf("Matrix C (Result 💙):\n");
    printMatrix(C, n, n);
    deallocateMatrix(A, n);
    deallocateMatrix(B, n);
    deallocateMatrix(C, n);
    return 0;
}