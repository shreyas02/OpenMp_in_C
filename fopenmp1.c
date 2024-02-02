#include<stdio.h>
#include<omp.h> 
#define arrsize 600
#define stepsize 100


int main(){

    int a[arrsize];
    int i;
    int sum ;
    sum =0;

    for(i=0;i<arrsize;i++){
        a[i] = 1;
    }

    #pragma omp parallel shared(sum)
    #pragma omp for
        for(i=0; i<arrsize; i+= stepsize){
            int j, start = i, end = i + stepsize - 1;

            printf("Computing sum(%d,%d) from %d of %d\n", start,end,omp_get_thread_num(),omp_get_num_threads());
            #pragma omp task
            {
                int psum = 0;
                printf("Task computing sum(%d,%d) from %d of %d\n", start, end,omp_get_thread_num(),omp_get_num_threads());
                for(j=start; j<=end;j++){
                    psum = psum + a[j];
                }

                #pragma omp taskwait
                #pragma omp critical
                sum += psum;
                printf("%d \n",psum);
            }
        }
    printf("sum = %d\n", sum);
    return 0;
}