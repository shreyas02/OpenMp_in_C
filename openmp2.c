#include<stdio.h>
#include<omp.h> //including openmp libraries

int main(){
    
    int tid;

    //specify the block is to be excecuted in parallel
    #pragma omp parallel private(tid)
    {
        /* Obtain and print thread id */
        tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);
    }

    return 0;
}