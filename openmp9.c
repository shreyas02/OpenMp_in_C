#include<stdio.h>
#include<omp.h> 
#define Arr_size 1000000
int a[Arr_size];
int b[Arr_size];

int main(){
    int i,dot = 0; 
    double t1,t2;

    //initialise the array 
    for(i=0;i<Arr_size;i++){
        a[i] = Arr_size - i ;
        b[i] = i ;
    }


    t1=omp_get_wtime();

    #pragma omp parallel for default(shared)private(i)reduction(+:dot)schedule(dynamic, 1000)
        //pragma directive to distribute the for loop iterations

        for(i=0;i<Arr_size;i++){ //i need not be declared private, openmp will do that 
            dot += +a[i] * b[i];
        }
        
    
    t2 = omp_get_wtime();

    printf("sum of array elements = %d and time is = %g\n",dot,t2-t1);

    return 0;
}