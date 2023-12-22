#include <stdio.h>
#include <stdbool.h>

#define V 4
int board[V][V] = {{0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0}};

void printMatrix() {
    int i, j;
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            printf("%d \t", board[i][j]);
        }
        printf("\n");
    }
}

bool isSafe(int row, int col) {
    int i, j;
    
    for (i = 0; i < col; i++) {
        if (board[row][i]) {
            return false;
        }
    }

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    for (i = row, j = col; j >= 0 && i < V; i++, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    return true;
}

bool solveNQueensUtil(int col) {
    if (col >= V) {
        return true;
    }

    for (int i = 0; i < V; i++) {
        if (isSafe(i, col)) {
            board[i][col] = 1;
            if (solveNQueensUtil(col + 1)) {
                return true;
            }
            board[i][col] = 0;
        }
    }
    return false;
}

bool solveNQueens() {
    if (!solveNQueensUtil(0)) {
        printf("Solution does not exist");
        return false;
    }
    printMatrix();
    return true;
}

int main() {
    solveNQueens();
    return 0;
}
