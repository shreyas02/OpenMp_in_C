#include<stdio.h>
#define MAX 50 
#include<omp.h> 

//matrix matrix multiply

void main(){
    int a[MAX][MAX], b[MAX][MAX], c[MAX][MAX] , c1[MAX][MAX] ;
    int arows, acolumns, brows, bcolumns;
    int i,j,k;
    double t1,t2;

    printf("Enter number of rows and columns of matrix a -\n");
    scanf("%d %d", &arows, &acolumns);

    /*printf ("Input Matrix A \n");

    for(i=0; i<arows; i++){
        for(j=0; j<acolumns; j++){
            scanf("%d",&a[i][j]);
        }
    }*/

    for(i=0; i<arows; i++){
        for(j=0; j<acolumns; j++){
            if(i==j){
                a[i][j]= 1;
            }
            else {
                a[i][j]=0;
            }
        }
    }

    printf("Enter number of rows and columns of matrix b -\n");
    scanf("%d %d", &brows, &bcolumns);
    printf ("Input Matrix B \n");

    /*for(i=0; i<brows; i++){
        for(j=0; j<bcolumns; j++){
            scanf("%d",&b[i][j]);
        }
    }*/

    for(i=0; i<brows; i++){
        for(j=0; j<bcolumns; j++){
            b[i][j] = (i+1)*(j+1) ;         }
    }

    //check condition for matrix multiplication
    if(acolumns != brows){
        printf("Multiplication not possible :(");
    }
    else{

    t1=omp_get_wtime();

    //#pragma omp parallel for schedule(dynamic) private(i,j,k) default(shared)
    for(i=0;i<arows;i++){
        for(j=0;j<bcolumns;j++){ 
            for (k=0; k<brows; k++){
                c[i][j] = c[i][j] + a[i][k] * b[k][j]; 
            } 
        }
    }

    t2=omp_get_wtime();

    printf("the time it took without omp - %g\n",t2 - t1);

    // multiply code with omp

    t1=omp_get_wtime();

    for(i=0;i<arows;i++){
        for(j=0;j<bcolumns;j++){ 
            #pragma omp parallel for private(k) default(shared) 
            for (k=0; k<brows; k++){
                c1[i][j] = c1[i][j] + a[i][k] * b[k][j]; 
            } 
        }
    }

    t2=omp_get_wtime();

    printf("the time it took with omp - %g\n",t2 - t1);

    // checking the results 

    int test = 0 ;
    for(i=0; i<arows; i++){
        for(j=0; j<bcolumns;j++){
            if(c[i][j]!=c1[i][j]){
                test = 1;
            }
        }
    if(test == 1) printf("Not sucessfull \n");
    }

    } 
}
