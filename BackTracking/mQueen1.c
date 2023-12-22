#include <stdio.h>
#include <stdbool.h>

#define MAX 10 

int board[MAX][MAX];
int solutionCount = 0;

void printMatrix(int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 1) {
                printf("\033[1;37m👸\t\033[0m ");
            } else {
                printf(" 0\t");
            }
        }
        printf("\n");
    }
    printf("\n");
}

bool isSafe(int row, int col, int N) {
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

    for (i = row, j = col; j >= 0 && i < N; i++, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    return true;
}

void solveNQueensUtil(int N, int col) {
    if (col >= N) {
        solutionCount++;
        printMatrix(N);
        return;
    }

    for (int i = 0; i < N; i++) {
        if (isSafe(i, col, N)) {
            board[i][col] = 1;
            solveNQueensUtil(N, col + 1);
            board[i][col] = 0; 
        }
    }
}

void solveNQueens() {
    int N;
    printf("Enter the size of the board: ");
    scanf("%d", &N);

    if (N <= 0 || N > MAX) {
        printf("Invalid board size\n");
        return;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }

    solveNQueensUtil(N, 0);

    if (solutionCount == 0) {
        printf("No solutions found\n");
    } else {
        printf("Number of solutions: %d\n", solutionCount);
    }
}

int main() {
    solveNQueens();
    return 0;
}
