#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "alg_lin.h"

int main(int argc, char const *argv[]) {
    if (argc != 5) {
        printf("Use: %s <m1_rows> <m1_columns> <m2_rows> <m2_columns>\n", argv[0]);
        return -1;
    }
    
    double start = omp_get_wtime();
    int m1_rows = atoi(argv[1]); int m1_columns = atoi(argv[2]); int m2_rows = atoi(argv[3]); int m2_columns = atoi(argv[4]);

    int **m1 = NULL;
    create_matrix(&m1, m1_rows, m1_columns);
    auto_fill(&m1, m1_rows, m1_columns, 1);

    int **m2 = NULL;
    create_matrix(&m2, m2_rows, m2_columns);
    auto_fill(&m2, m2_rows, m2_columns, 2);

    int **res = NULL;
    create_matrix(&res, m1_rows, m2_columns);
    multiply_matrices(m1, m2, res, m1_rows, m1_columns, m2_rows, m2_columns);

    free_matrix(m1, m1_rows);
    free_matrix(m2, m2_rows);
    free_matrix(res, m1_columns);

    double end = omp_get_wtime();
    double time_spent = (end - start);
    printf("%f s\n", time_spent);

    return 0;
}