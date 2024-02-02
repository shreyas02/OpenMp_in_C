#include<stdio.h>
#include<omp.h> 
#define Arr_size 1000000000
int a[Arr_size];

int main(){
    int i,sum = 0; 
    double t1,t2;

    //initialise the array 
    for(i=0;i<Arr_size;i++){
        a[i] = 1 ;
    }

    t1=omp_get_wtime();

    #pragma omp parallel default(shared)private(i)
    {
        int psum = 0 ;

        //pragma directive to distribute the for loop iterations

        #pragma omp for

        for(i=0;i<Arr_size;i++){ //i need not be declared private, openmp will do that 
            psum = psum +a[i];
        }

        #pragma omp critical
        sum = sum + psum;
    }
    t2 = omp_get_wtime();

    printf("sum of array elements = %d and time is = %g\n",sum,t2-t1);

    return 0;
}