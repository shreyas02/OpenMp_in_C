#include<stdio.h>
#include<omp.h> 

int main(){
    int a[1000];
    int i, sum = 0, prod = 1 , j;
    
    for(i=0;i<1000;i++){
        a[i] = 1;
    }

    #pragma omp parallel default(shared)
    {
        int psum = 0 , pprod = 1;
        #pragma omp for 
        for(i = 0; i<1000; i++){
            psum = psum + a[i];
            pprod = pprod * a[i];
        }

    #pragma omp critical(section1)
    {
        printf("In CS 1\n");
        for(j = 0; j< 10000000; j++);
        sum = sum +  psum;
        printf("Out CS 1\n");
    }

    #pragma omp critical(section2)
    {
        printf("In CS 2\n");
        for(j = 0; j< 10000000; j++);
        prod = prod * pprod;
        printf("Out CS 2\n");
    }
        

    }
      
    return 0;
}