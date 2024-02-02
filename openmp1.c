//in gcc need to compile with gcc -fopenmp

#include<stdio.h>
#include<omp.h> //including openmp libraries

int main(){
    
    //specify the block is to be excecuted in parallel
    #pragma omp parallel
    {
        printf("Hello world\n");
    }

    return 0;
}