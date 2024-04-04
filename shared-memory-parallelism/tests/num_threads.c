#include <stdio.h>
#include <omp.h>

int main(){
    int n_threads;
    #pragma omp parallel
    {
        n_threads = omp_get_num_threads();
    }

    printf("%d\n", n_threads);
    
    return 0;
}