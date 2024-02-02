#include<stdio.h>
#include<omp.h> //including openmp libraries

int main(){
    
    //specify the block is to be excecuted in parallel
    #pragma omp parallel(tid)
    {
        /* Obtain and print thread id */
        tid = omp_get_thread_num();
    }

    return 0;
}