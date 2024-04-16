#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "alg_lin.h"

int main(int argc, char const *argv[]) {
    if(argc != 5){
        printf("Use: %s <m1_rows> <m1_columns> <m2_rows> <m2_columns>\n", argv[0]);
        return -1;
    }

    int m1_rows = atoi(argv[1]);
    int m1_columns = atoi(argv[2]);
    int m2_rows = atoi(argv[3]);
    int m2_columns = atoi(argv[4]);

    int rank, size;
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *m1 = NULL;
    int *m2 = NULL;

    if(world_rank == 0) {
        create_matrix(&m1, m1_rows, m1_columns);
        auto_fill(m1, m1_rows, m1_columns, 1);
    }

    if(world_rank == 1) {
        create_matrix(&m2, m2_rows, m2_columns);
        auto_fill(m2, m2_rows, m2_columns, 2);
    }

    

    MPI_Finalize();

    free(local_m1);
    free(local_m2);
    free(local_res);
    if (world_rank == 0) {
        free(m1);
        free(m2);
        free(final_res);
    }

    return 0;
}