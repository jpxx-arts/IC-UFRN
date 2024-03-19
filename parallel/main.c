#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include "alg_lin.h"

#define ROWS 5000
#define COLUMNS 5000

int main() {
    clock_t begin = clock();

    int **m1 = NULL;
    create_matrix(&m1, ROWS, COLUMNS);
    auto_fill(&m1, ROWS, COLUMNS, 1);
    printf("matrix m1:\n");
    show_matrix(m1, ROWS, COLUMNS);

    int **m2 = NULL;
    create_matrix(&m2, ROWS, COLUMNS);
    auto_fill(&m2, ROWS, COLUMNS, 2);
    printf("matrix m2:\n");
    show_matrix(m2, ROWS, COLUMNS);

    int **res = NULL;
    create_matrix(&res, ROWS, COLUMNS);
    multiply_matrices(m1, m2, res, ROWS, COLUMNS, ROWS, COLUMNS);
    printf("Matrix multiplication between m1 and m2:\n");
    show_matrix(res, ROWS, COLUMNS);

    free_matrix(m1, ROWS);
    free_matrix(m2, ROWS);
    free_matrix(res, ROWS);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f s\n", time_spent);

    return 0;
}