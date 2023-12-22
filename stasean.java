import java.util.Arrays;

public class stasean {

  public static void main(String[] args) {
    int[][] A = {
      { 1, 2, 3, 4 },
      { 1, 2, 3, 4 },
      { 1, 2, 3, 4 },
      { 1, 2, 3, 4 },
    };
    int[][] B = {
      { 1, 2, 3, 4 },
      { 1, 2, 3, 4 },
      { 1, 2, 3, 4 },
      { 1, 2, 3, 4 },
    };
    int[][] result = str(A, B);
    for (int[] row : result) {
      System.out.println(Arrays.toString(row));
    }
  }

  public static int[][] str(int[][] a, int[][] b) {
    int n = a.length;
    if (n <= 2) {
      return standardMatrixMultiplication(a, b);
    }
    int res = n / 2;
    int A11[][] = new int[res][res];
    int A12[][] = new int[res][res];
    int A21[][] = new int[res][res];
    int A22[][] = new int[res][res];

    int B11[][] = new int[res][res];
    int B12[][] = new int[res][res];
    int B21[][] = new int[res][res];
    int B22[][] = new int[res][res];
    //dividing a matrix
    divideMatrix(a, A11, 0, 0);
    divideMatrix(a, A12, 0, res);
    divideMatrix(a, A21, res, 0);
    divideMatrix(a, A22, res, res);
    //dividing b matrix
    divideMatrix(b, B11, 0, 0);
    divideMatrix(b, B12, 0, res);
    divideMatrix(b, B21, res, 0);
    divideMatrix(b, B22, res, res);

    //calculating formula
    int[][] p1 = str(A11, sub(B12, B22));
    int[][] p2 = str(Add(A11, A12), B22);
    int[][] p3 = str(Add(A21, A22), B11);
    int[][] p4 = str(A22, sub(B21, B11));
    int[][] p5 = str(Add(A11, A22), Add(B11, B22));
    int[][] p6 = str(sub(A12, A22), Add(B21, B22));
    int[][] p7 = str(sub(A11, A21), Add(B11, B12));

    int[][] C11 = sub(Add(Add(p5, p4), p6), p2);
    int[][] C12 = Add(p1, p2);
    int[][] C21 = Add(p3, p4);
    int[][] C22 = sub(Add(p5, p4), Add(p3, p7));
    //Conquer

    int rows = res * 2;
    int cols = res * 2;

    int[][] result = new int[rows][cols];
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (i < res && j < res) {
          result[i][j] = C11[i][j];
        } else if (i < res && j >= res) {
          result[i][j] = C12[i][j - res];
        } else if (i >= res && j < res) {
          result[i][j] = C21[i - res][j];
        } else {
          result[i][j] = C22[i - res][j - res];
        }
      }
    }
    return result;
  }

  public static int[][] standardMatrixMultiplication(int[][] a, int[][] b) {
    int n = a.length;
    int[][] result = new int[n][n];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        result[i][j] = 0;
        for (int k = 0; k < n; k++) {
          result[i][j] += a[i][k] * b[k][j];
        }
      }
    }
    return result;
  }

  public static int[][] Add(int[][] a, int[][] b) {
    int n = a.length;
    int[][] result = new int[a.length][b.length];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        result[i][j] = a[i][j] + b[i][j];
      }
    }
    return result;
  }

  public static int[][] sub(int[][] a, int[][] b) {
    int n = a.length;
    int[][] result = new int[a.length][b.length];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        result[i][j] = a[i][j] - b[i][j];
      }
    }
    return result;
  }

  public static void divideMatrix(
    int[][] MainMatrix,
    int[][] result,
    int r,
    int c
  ) {
    for (int i1 = 0, i2 = r; i1 < result.length; i1++, i2++) {
      for (int j1 = 0, j2 = c; j1 < result.length; j1++, j2++) {
        result[i1][j1] = MainMatrix[i2][j2];
      }
    }
  }
}
