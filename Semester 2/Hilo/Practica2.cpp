#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

//Hacer que funcione de forma dinamica?


void *foo(void *arg){
    printf("Hola desde el hilo: %d\n",*((int*)arg));
}

int main(int argc, char const *argv[]){
    if(argc==1){
        printf("Argumentos faltantes");
        return 0;
    }
    //Paso 1: Creacion de un hilo 
    int n = strtol(argv[1], NULL,10);
    printf("Numero de hilos a crear : %d\n", n);
    pthread_t  *thrad_Arr = (pthread_t*)malloc(sizeof(pthread_t)*n);
    int *threadIDS = (int*)malloc(sizeof(int)*n);
    for (size_t i = 0; i < n; i++){
        threadIDS[i]=i;
        if (pthread_create(&thrad_Arr[i],NULL,foo,(void*)&threadIDS[i])){
            printf("error creating thread.");
            return 0;
        }   
    }
    printf("Hola desde el padre\n");
    //Paso 2 El proceso padre espera al hilo
    for (size_t i = 0; i < n; i++){
        pthread_join(thrad_Arr[i],NULL);
    }
    return 0;
}
