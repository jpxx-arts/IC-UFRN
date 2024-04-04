#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#define X 2
#define Y 2
#define Z 2

int create_matrix(int ****matrix, int x, int y, int z) {
    (*matrix) = (int ***) malloc(x * sizeof(int **));
    if (*matrix == NULL) return -1;

    (*matrix)[0] = (int **) malloc(x * y * sizeof(int *));
    if ((*matrix)[0] == NULL) {
        free(*matrix);
        return -1;
    }

    for (int i = 1; i < x; i++) {
        (*matrix)[i] = (*matrix)[0] + i * y;
    }

    (*matrix)[0][0] = (int *) malloc(x * y * z * sizeof(int));
    if ((*matrix)[0][0] == NULL) {
        free(*matrix[0]);
        free(*matrix);
        return -1;
    }

    for (int i = 0; i < x; i++) {
        for (int j = 1; j < y; j++) {
            (*matrix)[i][j] = (*matrix)[i][0] + j * z;
        }
    }

    return 0;
}

void free_matrix(int ***matrix, int x, int y, int z) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            free(matrix[i][j]);
        }
        free(matrix[i]);
    }
    free(matrix);
}

void auto_fill(int ****matrix, int x, int y, int z, int seed){
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            for(int k = 0; k < z; k++){
                (*matrix)[i][j][k] = rand() % 10;
            }
        }
    }
}

void show_matrix(int ***matrix, int x, int y, int z) {
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            for(int k = 0; k < z; k++){
                printf("%d ", matrix[i][j][k]);
            }
        }
    }
    printf("\n");
}

int main() {
    int ***matrix;
    int x = 2, y = 3, z = 4;

    if (create_matrix(&matrix, x, y, z) == 0) {
        auto_fill(&matrix, x, y, z, 1);
        show_matrix(matrix, x, y, z);
        free_matrix(matrix, x, y, z);
    } else {
        return -1;
    }

    return 0;
}