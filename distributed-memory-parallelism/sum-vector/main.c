#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int create_vector(int **vector, int vector_size);
int free_vector(int *vector);
void fill_vector(int **vector, int vector_size, int seed);

int main(int argc, char **argv){
    if(argc != 2)
        return -1;

    int *vector = NULL;
    int vector_size = atoi(argv[1]);

    create_vector(&vector, vector_size);
    fill_vector(&vector, vector_size, 1);

    int rank, size, tag, sum, local_sum = 0;
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int elements_per_proc = vector_size/size;
    int remainder = vector_size%size;
    int local_elements = elements_per_proc + (rank < remainder);
    int local_start = (rank < remainder) ? rank * local_elements : rank * local_elements + remainder;

    for(int i = local_start; i < local_start + local_elements; i++) {
        local_sum += vector[i];
    }

    MPI_Reduce(&local_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0)
        printf("Vector's sum: %d\n", sum);

    MPI_Finalize();

    free_vector(vector);
    return 0;
}

int create_vector(int **vector, int vector_size){
    *vector = (int *) malloc(vector_size*sizeof(int));

    if(*vector == NULL)
        return -1;

    return 0;
}

int free_vector(int *vector){
    if(vector == NULL)
        return -1;

    free(vector);
    return 0;
}

void fill_vector(int **vector, int vector_size, int seed){
    srand(seed);

    for(int i = 0; i < vector_size; i++){
        (*vector)[i] = rand()%10;
    }
}