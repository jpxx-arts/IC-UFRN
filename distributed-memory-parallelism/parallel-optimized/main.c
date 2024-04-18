#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "alg_lin.h"

int main(int argc, char **argv) {
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

    double start_time, end_time;
    if(rank == 0){
        start_time = MPI_Wtime(); 
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size < 2){
        printf("Use at least 2 processes for matrix multiplication\n");
        MPI_Finalize();
        return 1;
    }

    int *m1 = NULL;
    create_matrix(&m1, m1_rows, m1_columns);
    int *m2 = NULL;
    create_matrix(&m2, m2_rows, m2_columns);
    int *res = NULL;
    create_matrix(&res, m1_rows, m2_columns);

    int rows_per_process = m1_rows / size;
    int remainder = m1_rows % size;

    if(rank == 0){
        auto_fill(&m1, m1_rows, m1_columns, 1);
        auto_fill(&m2, m2_rows, m2_columns, 2);
    }

    MPI_Bcast(m2, m2_rows * m2_columns, MPI_INT, 0, MPI_COMM_WORLD);

    int *sub_m1 = NULL;
    create_matrix(&sub_m1, rows_per_process, m1_columns);

    MPI_Scatter(m1, rows_per_process * m1_columns, MPI_INT, sub_m1, rows_per_process * m1_columns, MPI_INT, 0, MPI_COMM_WORLD);

    int *sub_res = NULL;
    create_matrix(&sub_res, rows_per_process, m2_columns);

    multiply_matrices(sub_m1, m2, sub_res, rows_per_process, m1_columns, m2_rows, m2_columns);

    MPI_Gather(sub_res, rows_per_process * m2_columns, MPI_INT, res, rows_per_process * m2_columns, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        end_time = MPI_Wtime(); 
        printf("%f s\n", end_time - start_time); 
    }

    free(m1);
    free(m2);
    free(res);

    MPI_Finalize();

    return 0;
}