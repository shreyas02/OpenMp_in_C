#include<stdio.h>
#include<omp.h> 
#define Arr_size 1000000000
int a[Arr_size];

// program on sum of array 

int main(){
    
    printf("omp_get_wtime() = %g\n",omp_get_wtime()); //starts time from a garbage time value
    printf("omp_get_wtime() = %g\n",omp_get_wtick()); // resolution of the timer
    
    int i,sum = 0;
    double t1,t2;
    int tid,numt;

    //initialise the array 
    for(i=0;i<Arr_size;i++){
        a[i] = 1 ;
    }

    t1 = omp_get_wtime();
    // sum up the array 
    for(i=0;i<Arr_size;i++){
        sum = sum + a[i];
    }
    t2 = omp_get_wtime();

    printf("sum of the array elements = %d and time = %g\n",sum,t2-t1);
    sum = 0;

    //paralleling the code 
    /*#pragma omp parallel default(shared) private(i,tid)
    {
        tid = omp_get_thread_num();
        numt = omp_get_num_threads();
        t1 = omp_get_wtime();
        // sum up the array 
        for(i=0;i<Arr_size;i++){
            sum = sum + a[i];
        }
        t2 = omp_get_wtime();
    }
    printf("sum of the array elements = %d and time = %g\n",sum,t2-t1);*/ // wrong way to parallelise

    t1 = omp_get_wtime();
    #pragma omp parallel default(shared) private(i,tid)
    {
        int from, to, psum=0;
        tid = omp_get_thread_num();
        numt = omp_get_num_threads();
        //distribute the work 
        from= (Arr_size/numt)*tid;
        to=(Arr_size/numt)*(tid+1)-1;
        if(tid==numt-1){
            to = Arr_size -1;
        }
        //printf("Hello from %d of %d, my range is from %d to %d\n",tid,numt,from,to);

        // sum up the array 
        for(i=from;i<=to;i++){
            
            psum = psum + a[i];
        }
            //synchronise to sum up partial sums 
            #pragma omp critical // can be excecuted by only one thread at a time
            sum = sum + psum;
    }
    t2 = omp_get_wtime();

    printf("sum of array elements = %d and time is = %g\n",sum,t2-t1);

    return 0;
}