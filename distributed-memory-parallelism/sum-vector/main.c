#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int create_vector(int **vector, int vector_size);
int free_vector(int *vector);
void fill_vector(int *vector, int local_start, int local_end, int seed);
int sum_part(int *vector, int local_start, int local_end);

int main(int argc, char **argv){
    if(argc != 2)
        return -1;

    int *vector = NULL;
    int vector_size = atoi(argv[1]);

    create_vector(&vector, vector_size);

    int rank, size, sum, local_sum;
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double start_time, end_time;
    if(rank == 0){
        start_time = MPI_Wtime(); 
    }


    int elements_per_proc = vector_size/size;
    int remainder = vector_size%size;
    int local_elements = elements_per_proc + (rank < remainder);
    int local_start = (rank < remainder) ? rank * local_elements : rank * local_elements + remainder;

    fill_vector(vector, local_start, local_elements, 1);
    local_sum = sum_part(vector, local_start, local_elements);

    MPI_Reduce(&local_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("Vector's sum: %d\n", sum);

        end_time = MPI_Wtime(); 
        printf("%f s\n", end_time - start_time); 
    }

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

void fill_vector(int *vector, int local_start, int local_end, int seed){
    srand(seed);

    for(int i = local_start; i < local_start + local_end; i++){
        vector[i] = rand()%10;
    }
}

int sum_part(int *vector, int local_start, int local_end){
    int local_sum = 0;

    for(int i = local_start; i < local_start + local_end; i++) {
        local_sum += vector[i];
    }

    return local_sum;
}