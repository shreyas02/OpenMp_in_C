#include<stdio.h>
#define MAX 50 
#include<omp.h> 

void main(){
    int a[MAX][MAX], b[MAX], c[MAX];
    int arows;
    int i,j,k;
    double t1,t2;

    printf("Enter number of rows of matrix a -\n");
    scanf("%d", &arows);

    printf ("Input Matrix A \n");

    for(i=0; i<arows; i++){
        for(j=0; j<arows; j++){
            scanf("%d",&a[i][j]);
        }
    }

    printf ("Input Matrix B \n");


    for(j=0; j<arows; j++){
            scanf("%d",&b[j]);
    }

    t1=omp_get_wtime();

    int sum = 0;
    #pragma omp parallel for schedule(dynamic,16)
    for(i=0;i<arows;i++){
        for(j=0;j<arows;j++){ 
                c[i] = c[i] + a[i][j] * b[j]; 
        }
    }

    t2 = omp_get_wtime();
    
    // print matrix c
    printf("Mtrix C is and time taken is = %g\n",t2-t1);

    for(j=0; j<arows;j++){
            printf("%d \n",c[j]);
        }

}