#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int create_vector(int **vector, int vector_size);
int free_vector(int *vector);
void fill_vector(int *vector, int size, int seed);
int sum_vect(int *vector, int size);
void show_vect(int *vector, int size);

int main(int argc, char **argv){
    int rank, size, sum, local_sum, tag = 0;
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        if(argc != 2){
            printf("The parameters must be 2\n");
            return -1;
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);

    int vector_size = atoi(argv[1]);
    int *vector = NULL;

    double start_time, end_time;
    if(rank == 0){
        start_time = MPI_Wtime(); 

        create_vector(&vector, vector_size);
        fill_vector(vector, vector_size, 1);
    }

    int elements_per_proc = vector_size/size;
    int elements_int = size*elements_per_proc;
    int remainder = vector_size%size;
    int local_elements = elements_per_proc + (rank < remainder);

    int *sub_vector = NULL;
    create_vector(&sub_vector, local_elements);
    if(rank == 0){
        for(int i = 1; i < size; i++){
            MPI_Send(&(vector[elements_per_proc*i]), elements_per_proc, MPI_INT, i, ++tag, MPI_COMM_WORLD);
        }
        printf("rank: %d tag: %d\n",rank,tag);
        sub_vector = vector;
    } else{
        tag = rank;
        MPI_Recv(sub_vector, elements_per_proc, MPI_INT, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    show_vect(sub_vector, elements_per_proc);
    MPI_Barrier(MPI_COMM_WORLD);
    local_sum = sum_vect(sub_vector, elements_per_proc);
    
    if(remainder != 0 && rank == 0){
        for(int i = 1; i <= remainder; i++){
            MPI_Send(&(vector[elements_int+i-1]), 1, MPI_INT, i, tag++, MPI_COMM_WORLD);
        }
    } else if(remainder != 0 && rank <= remainder){
        int element_from_remainder;
        tag += rank;
        MPI_Recv(&element_from_remainder, 1, MPI_INT, 0, tag++, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        local_sum += element_from_remainder;
    }

    MPI_Reduce(&local_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        show_vect(vector, vector_size);
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

void fill_vector(int *vector, int size, int seed){
    srand(seed);

    for(int i = 0; i < size; i++){
        vector[i] = rand()%10;
    }
}

int sum_vect(int *vector, int size){
    int sum = 0;

    for(int i = 0; i < size; i++) {
        sum += vector[i];
    }

    return sum;
}

void show_vect(int *vector, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", vector[i]);
    }
    printf("\n");
}