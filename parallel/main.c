#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "alg_lin.h"

#define ROWS 2000
#define COLUMNS 2000

int main(int argc, char const *argv[]) {
    double start = omp_get_wtime();

    int **m1 = NULL;
    create_matrix(&m1, ROWS, COLUMNS);
    auto_fill(&m1, ROWS, COLUMNS, 1);

    int **m2 = NULL;
    create_matrix(&m2, ROWS, COLUMNS);
    auto_fill(&m2, ROWS, COLUMNS, 2);

    int **res = NULL;
    create_matrix(&res, ROWS, COLUMNS);
    multiply_matrices(m1, m2, res, ROWS, COLUMNS, ROWS, COLUMNS);

    free_matrix(m1, ROWS);
    free_matrix(m2, ROWS);
    free_matrix(res, ROWS);

    double end = omp_get_wtime();
    double time_spent = (end - start);
    printf("%f s\n", time_spent);

    return 0;
}