#include<stdio.h>
#include<omp.h> //including openmp libraries

//order is not deterministic  
//race condition 

int main(){
    int numt,tid;
    //numt = omp_get_num_threads();
    #pragma omp parallel private(tid)shared(numt)
    {   
        //get the total number of omp threads
        numt = omp_get_num_threads();// this is slow as every thread will do this 
        //get the thread id of this thread

        /*if(tid ==0){
            numt=omp_get_num_threads();
        } // we can get some garbage from here */
        tid=omp_get_thread_num();
        printf("hello world from thread %d of %d \n",tid,numt);
    }

    #pragma omp parallel private(tid)shared(numt)
    {   
        if(tid ==0){
            numt=omp_get_num_threads();
        }
    }  

    #pragma omp parallel private(tid)shared(numt)
    {   
        tid=omp_get_thread_num();
        printf("hello world from thread %d of %d \n",tid,numt);
    }

    return 0;
}