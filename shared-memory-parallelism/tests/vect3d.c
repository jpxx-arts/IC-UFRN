#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#define X 2
#define Y 2
#define Z 2

int create_matrix(int **matrix, int x, int y, int z) {
    (*matrix) = (int *) malloc(x*y*z * sizeof(int));
    if (*matrix == NULL) return -1;

    return 0;
}

void free_matrix(int *matrix, int x, int y, int z) {
    if (matrix != NULL) free(matrix);
}

void auto_fill(int **matrix, int x, int y, int z, int seed){
    srand(seed);
    for(int i = 0; i < x*y*z; i++){
        (*matrix)[i] = rand() % 10;
    }
}

void show_matrix(int *matrix, int x, int y, int z) {
    for(int i = 0; i < x*y*z; i++){
        printf("%d ", matrix[i]);
    }
    printf("\n");
}

int get_element(int **m1, int **m2, int row, int column, int tam) {
    int sum = 0, x;

    #pragma omp parallel for private(x) reduction(+ : sum)
    for (x = 0; x < tam; x++) {
        sum += m1[row][x] * m2[x][column];
    }

    return sum;
}

int multiply_matrices(int **m1, int **m2, int **res, int m1R, int m1C, int m2R, int m2C) {
    if (m1C == m2R) {
        for (int i = 0; i < m1R; i++) {
            for (int j = 0; j < m2C; j++) {
                res[i][j] = get_element(m1, m2, i, j, m1C);
            }
        }        
        return 0;
    } else {
        printf("Multiplication Impossible");
        return -1;
    }
}

int main() {
    int *matrix;

    if (create_matrix(&matrix, X, Y, Z) == 0) {
        auto_fill(&matrix, X, Y, Z, 1);
        show_matrix(matrix, X, Y, Z);
        free_matrix(matrix, X, Y, Z);
    } else {
        return -1;
    }

    return 0;
}