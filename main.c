#include <stdio.h>
#include <stdlib.h>
#include "alg_lin.h"

#define ROWS 2
#define COLUMNS 2

int main(int argc, char const *argv[]) {
    int **m1 = NULL;
    create_matrix(&m1, ROWS, COLUMNS);
    printf("Set the m1 matrix\n");
    set_matrix(m1, ROWS, COLUMNS);
    printf("m1 matrix:\n");
    show_matrix(m1, ROWS, COLUMNS);

    int **m2 = NULL;
    create_identity(&m2, ROWS, COLUMNS);
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
    free_matrix(m3_t, COLUMNS);

    return 0;
}