#include<stdio.h>
#include<omp.h> //including openmp libraries

//order is not deterministic   

int main(){
    #pragma omp parallel
    {
        //get the total number of omp threads
        int numt = omp_get_num_threads();
        //get the thread id of this thread
        int tid=omp_get_thread_num();
        printf("hello world from thread %d of %d \n",tid,numt);
    }
    return 0;
}