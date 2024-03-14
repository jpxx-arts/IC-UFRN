#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ROWS 3
#define COLUMNS 3

int create_matrix(int ***matrix, int rows, int columns);
void free_matrix(int **matrix, int rows);
void set_matrix(int **matrix, int rows, int columns);
int create_identity(int ***matrix, int rows, int columns);
void show_matrix(int **matrix, int rows, int columns);
int multiply_matrices(int **m1, int **m2, int **res, int m1R, int m1C, int m2R, int m2C);
int get_element(int **m1, int **m2, int row, int column, int tam);
int transpose(int ***matrix, int ***transpose_of, int rows_original, int columns_original);

int main() {
    int **m1 = NULL;
    create_matrix(&m1, ROWS, COLUMNS);
    printf("Set the m1 matrix\n");
    set_matrix(m1, ROWS, COLUMNS);
    printf("m1 matrix:\n");
    show_matrix(m1, ROWS, COLUMNS);

    int **m2 = NULL;
    create_matrix(&m2, ROWS, COLUMNS);
    printf("Set the m2 matrix\n");
    set_matrix(m2, ROWS, COLUMNS);
    printf("m2 matrix:\n");
    show_matrix(m2, ROWS, COLUMNS);

    int **res = NULL;
    create_matrix(&res, ROWS, COLUMNS);
    multiply_matrices(m1, m2, res, ROWS, COLUMNS, ROWS, COLUMNS);
    printf("Multiplication result:\n");
    show_matrix(res, ROWS, COLUMNS);

    free_matrix(m1, ROWS);
    free_matrix(m2, ROWS);
    free_matrix(res, ROWS);

    int **m3 = NULL;
    create_matrix(&m3, ROWS, COLUMNS);
    printf("Set the m3 matrix\n");
    set_matrix(m3, ROWS, COLUMNS);
    printf("m3 matrix:\n");
    show_matrix(m3, ROWS, COLUMNS);
    int **m3_t = NULL;
    transpose(&m3, &m3_t, ROWS, COLUMNS);
    printf("transpose of m3 matrix:\n");
    show_matrix(m3_t, COLUMNS, ROWS);

    free_matrix(m3, COLUMNS);
    free_matrix(m3_t, COLUMNS);

    int **identity = NULL;
    create_identity(&identity, ROWS, COLUMNS);
    printf("Identity of a matrix %dx%d:\n", ROWS, COLUMNS);
    show_matrix(identity, ROWS, COLUMNS);

    free_matrix(identity, ROWS);

    return 0;
}

int create_matrix(int ***matrix, int rows, int columns) {
    *matrix = (int **)malloc(rows * sizeof(int *));
    if (*matrix == NULL){
        printf("Allocation error");
        return -1;
    }

    int flag = 0;
    #pragma omp parallel for
    for (int i = 0; i < rows; ++i) {
        (*matrix)[i] = (int *)calloc(columns, sizeof(int));
        if ((*matrix)[i] == NULL){
            flag = 1;
        }
    }

    if(flag){
        printf("Allocation error");
        return -2;
    }

    return 0;
}

void free_matrix(int **matrix, int rows) {
    #pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }

    free(matrix);
}

void set_matrix(int **matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("Enter the element [%d, %d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("\n");
}

int create_identity(int ***matrix, int rows, int columns) {
    *matrix = (int **)malloc(rows * sizeof(int *));
    if (*matrix == NULL){
        printf("Allocation error");
        return -1;
    }

    int flag = 0;
    #pragma omp parallel for
    for (int i = 0; i < rows; ++i) {
        (*matrix)[i] = (int *)malloc(columns * sizeof(int));
        if ((*matrix)[i] == NULL){
            flag = 1;
        }
    }
    

    if(flag){
        printf("Allocation error");
        return -2;
    }

    #pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            (*matrix)[i][j] = (i == j);
        }
    }
    
    return 0;
}

void show_matrix(int **matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int get_element(int **m1, int **m2, int row, int column, int tam) {
    int sum = 0, i = 0;

    #pragma omp parallel for private(i) reduction(+ : sum)
    for (int x = 0; x < tam; x++) {
        sum += m1[row][x] * m2[x][column];
    }

    return sum;
}

int multiply_matrices(int **m1, int **m2, int **res, int m1R, int m1C, int m2R, int m2C) {
    if (m1C == m2R) {
        #pragma omp parallel for
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

int transpose(int ***matrix, int ***transpose_of, int rows_original, int columns_original){
    int valid = create_matrix(transpose_of, columns_original, rows_original);
    if (valid < 0)
        return -1;

    #pragma omp parallel for
    for (int i = 0; i < columns_original; i++) {
        for (int j = 0; j < rows_original; j++) {
            (*transpose_of)[i][j] = (*matrix)[j][i];
        }
    }

    return 0;
}