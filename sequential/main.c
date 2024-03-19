#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "alg_lin.h"

#define ROWS 3
#define COLUMNS 3

int main(int argc, char const *argv[]) {
    clock_t begin = clock();
    
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

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);

    return 0;
}