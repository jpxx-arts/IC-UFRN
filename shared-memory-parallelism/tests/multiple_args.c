#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int create_matrix(int ***matrix, int rows, int columns) {
    (*matrix) = (int **) malloc(rows*sizeof(int *));
    if ((*matrix) == NULL) {
        free(*matrix);
        return -1;
    }

    (*matrix)[0] = (int *) malloc(rows*columns*sizeof(int));
    if ((*matrix)[0] == NULL) {
        free(*matrix);
        free((*matrix)[0]);
        return -2;
    }

    for(int i = 1; i < rows; i++){
        (*matrix)[i] = (*matrix)[0] + i*columns;
    }

    return 0;
}

void free_matrix(int **matrix, int rows) {
    if(matrix == NULL){
        return;
    }
    if(matrix[0] == NULL){
        return;
    }

    free(matrix[0]);
    free(matrix);
}

void auto_fill(int ***matrix, int rows, int columns, int seed){
    srand(seed);
    int element = rand() % 10;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            (*matrix)[i][j] = element;
            element = rand() % 10;
        }
    }
}

void show_matrix(int **matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    int **m1 = NULL;
    create_matrix(&m1, 2, 2);
    auto_fill(&m1, 2, 2, 1);
    show_matrix(m1, 2, 2);  
    for(int i = 0; i < 4; i++){
        printf("%d", m1[0][i]);
    }
    printf("\n");
    free_matrix(m1, 2);
    return 0;
}