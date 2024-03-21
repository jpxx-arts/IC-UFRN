#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "alg_lin.h"

#define ROWS 2000
#define COLUMNS 2000

int main(int argc, char const *argv[]) {
    clock_t begin = clock();

    int *m1 = NULL;
    create_matrix(&m1, ROWS, COLUMNS);
    auto_fill(&m1, ROWS, COLUMNS, 1);

    int *m2 = NULL;
    create_matrix(&m2, ROWS, COLUMNS);
    auto_fill(&m2, ROWS, COLUMNS, 2);

    int *res = NULL;
    create_matrix(&res, ROWS, COLUMNS);
    multiply_matrices(m1, m2, res, ROWS, COLUMNS, ROWS, COLUMNS);

    free_matrix(m1, ROWS);
    free_matrix(m2, ROWS);
    free_matrix(res, ROWS);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f s\n", time_spent);

    return 0;
}