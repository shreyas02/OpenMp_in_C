#include<stdio.h>
#include<omp.h> 

int tid;
#pragma omp threadprivate(tid)// thread private variables cannot do this in main 
int numt;

int main(){

    #pragma omp parallel default(shared)
    {
        int j;
        tid = omp_get_thread_num();

        if(tid == 0){
            for(j=0;j<100000000;j++); //long wait
            numt = omp_get_num_threads();
        }
    }

    #pragma omp parallel default(shared) //implicit barrier
    {
        printf("hello world from thread %d of %d \n",tid,numt);
    }


    #pragma omp parallel default(shared)
    {
        int j;
        tid = omp_get_thread_num();

        if(tid == 0){
            for(j=0;j<100000000;j++); //long wait
            numt = omp_get_num_threads();
        }

        //can use this function as well
        #pragma omp barrier  

        printf("hello world from thread %d of %d \n",tid,numt);

    }

    #pragma omp parallel default(shared)
    {
        int j;
        tid = omp_get_thread_num();

        #pragma omp single
        // above one also provides synchronisation 
        if(tid == 0){
            for(j=0;j<100000000;j++); //long wait
            numt = omp_get_num_threads();
        }

        printf("hello world from thread %d of %d \n",tid,numt);

    }

    #pragma omp parallel default(shared)
    {
        int j;
        tid = omp_get_thread_num();

        #pragma omp single nowait
        // allows other threads to contiue with the work. may cause error in this case
        if(tid == 0){
            for(j=0;j<100000000;j++); //long wait
            numt = omp_get_num_threads();
        }

        printf("hello world from thread %d of %d \n",tid,numt);

    }

    #pragma omp parallel default(shared)
    {
        int j;
        tid = omp_get_thread_num();

        #pragma omp single master
        // allows only master thread to do this 
        if(tid == 0){
            for(j=0;j<100000000;j++); //long wait
            numt = omp_get_num_threads();
        }

        printf("hello world from thread %d of %d \n",tid,numt);

    }

    return 0;
}