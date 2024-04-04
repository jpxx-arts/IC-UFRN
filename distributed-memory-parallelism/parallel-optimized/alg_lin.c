#include <stdio.h>
#include <stdlib.h>

int create_matrix(int **matrix, int rows, int columns) {
    (*matrix) = (int *) malloc(rows*columns * sizeof(int));
    if ((*matrix) == NULL) {
        printf("Allocation error");
        free(*matrix);
        return -1;
    }

    return 0;
}

void free_matrix(int *matrix, int rows) {
    if(matrix == NULL){
        return;
    }

    free(matrix);
}

void set_matrix(int *matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("Enter the element [%d, %d]: ", i, j);
            scanf("%d", &matrix[j + (i*columns)]);
        }
    }
    printf("\n");
}

int create_identity(int **matrix, int rows, int columns) {
    (*matrix) = (int *) malloc(rows*columns * sizeof(int));
    if ((*matrix) == NULL) {
        printf("Allocation error");
        free(*matrix);
        return -1;
    }

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            (*matrix)[(rows*i) + j] = (i == j);
        }
    }
    
    return 0;
}

void show_matrix(int *matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", matrix[j + (i*columns)]);
        }
        printf("\n");
    }
    printf("\n");
}

int get_element(int *m1, int *m2, int row, int column, int tam) {
    int sum = 0, x;

    #pragma omp parallel for private(x) reduction(+ : sum)
    for (x = 0; x < tam; x++) {
        sum += m1[(row*tam) + x] * m2[(x*tam) + column];
    }

    return sum;
}

int multiply_matrices(int *m1, int *m2, int *res, int m1Rows, int m1Columns, int m2Rows, int m2Columns) {
    if (m1Columns == m2Rows) {
        #pragma omp parallel for collapse(2)
        for (int i = 0; i < m1Rows; i++) {
            for (int j = 0; j < m2Columns; j++) {
                res[j + (i*m2Columns)] = get_element(m1, m2, i, j, m1Columns);
            }
        }        
        return 0;
    } else {
        printf("Multiplication Impossible");
        return -1;
    }
}

void auto_fill(int **matrix, int rows, int columns, int seed){
    srand(seed);

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            (*matrix)[j + (i*columns)] = rand() % 10;
        }
    }
}