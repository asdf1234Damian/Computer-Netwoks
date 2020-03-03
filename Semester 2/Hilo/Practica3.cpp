#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int **A;
int **B;
int **C;
int maxTh,rpt,excess;
int nA, nB, mA, mB;

void *matProd(void* arg){
    int start = *(int*)arg;
    int end = start+maxTh;
    
    if (start = maxTh){
        end += excess;
    }

    for (size_t i = start; i < end; i++){
        for (size_t j = 0; j < count; j++){
            for (size_t k = 0; k < count; k++){
                C[i][j] += A[i][j] * B[i][j];
            }
        }
    }
}

int main(int argc, char const *argv[]){
    /*
    arg[1] = maxThreads
    arg[2] = matrizA
    arg[3] = matrizB
    */
    if(argc < 4 && argv[1] == "0"){
        printf("Argumentos faltantes o invalidos");
        return 0;
    }
    //Extraer los datos de los archivos
    maxTh = strtol(argv[1], NULL,10);
    FILE *MatrA = fopen(argv[2], "r");
    FILE *MatrB = fopen(argv[3], "r");
    fscanf(MatrA,"%d,%d", &nA, &mA);
    fscanf(MatrB,"%d,%d", &nB, &mB);
    // Validar datos
    if(mA != nB){
        printf("Dimensiones no validas %d %d",mA,nB);
        return 0 ;
    }
    A = (int**)malloc(sizeof(int*)*mA);
    for (size_t i = 0; i < mA; i++){
        A[i] = (int*)malloc(sizeof(int)*nA);
        for (size_t j = 0; j < nA; j++){
            fscanf(MatrA,"%d ",&A[i][j]);;
        }
    }
    B = (int**)malloc(sizeof(int*)*mB);
    for (size_t i = 0; i < mB; i++){
        B[i] = (int*)malloc(sizeof(int)*nB);
        for (size_t j = 0; j < nB; j++){
            fscanf(MatrB,"%d ",&B[i][j]);;
        }
    }
    C = (int**)malloc(sizeof(int*)*mA);
    for (size_t i = 0; i < mA; i++){
        C[i] = (int*)malloc(sizeof(int)*nB);
        for (size_t j = 0; j < nB; j++){
            C[i][j]= 0;
        }
    }

    rpt = mA / maxTh;
    excess = mA % maxTh;
    pthread_t *thrd_arr = (pthread_t*)malloc(sizeof(pthread_t)*maxTh);
    int *threadIds = (int*)malloc(sizeof(int)*maxTh);
    for (size_t i = 0; i < maxTh; i++){
        threadIds[i] = i;
        if (pthread_create(&thrd_arr[i],NULL,matProd,(void*)&threadIds[i])){
            printf("error creating thread.");
            return 0;
        }   
    }
    
}

