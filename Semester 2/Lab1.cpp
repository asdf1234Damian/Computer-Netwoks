#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

//Hacer que funcione de forma dinamica?
struct myStruct{
    char cadena[60];
    int  nums[2];
    float x;
} ;

void *foo(void *arg){
    struct myStruct argument = *((struct myStruct*)arg);
    printf("Datos recibidos en hilo %d: \n\tCadena recibida: %s\n\tArreglo: [%d,%d]\n\tFlotante: %.4f\n",argument.nums[1],argument.cadena,argument.nums[0],argument.nums[1],argument.x);
    strcpy((*((struct myStruct*)arg)).cadena,"Hola desde el hijo");
    (*((struct myStruct*)arg)).nums[0] = (*((struct myStruct*)arg)).nums[1];
    (*((struct myStruct*)arg)).x = 3.1416;
    // return (void *)&argument;
}

int main(int argc, char const *argv[]){
    if(argc==1){
        printf("Argumentos faltantes");
        return 0;
    }
    srand((unsigned) time(NULL));
    //Paso 1: Creacion de hilos
    int n = strtol(argv[1], NULL,10);
    printf("Numero de hilos a crear : %d\n", n);
    pthread_t  *thrad_Arr = (pthread_t*)malloc(sizeof(pthread_t)*n);
    struct myStruct  *structs = (struct myStruct*)malloc(sizeof(myStruct)*n);
    int *threadIDS = (int*)malloc(sizeof(int)*n);
    struct myStruct *auxPtr = NULL;
    for (size_t i = 0; i < n; i++){
        threadIDS[i]=i; 
        structs[i] = {{},{rand(),(int)i},(float)(rand()/3.4)};
        strcpy(structs[i].cadena,"mensaje escrito por el padre");
        if (pthread_create(&thrad_Arr[i],NULL,foo,(void*)&structs[i])){
            printf("error creating thread.");
            return 0;
        }   
    }
    printf("Hola desde el padre\n");
    //Paso 2 El proceso padre espera a los hilos
    for (size_t i = 0; i < n; i++){
        pthread_join(thrad_Arr[i],NULL);
    }
    //Se imprime los resultados modificados
    printf("Modificaciones de los hijos\n");
    for (size_t i = 0; i < n; i++){
        struct myStruct argument  = structs[i]; 
        printf("Datos [%d]: \n\tCadena recibida: %s\n\tArreglo: [%d,%d]\n\tFlotante: %.4f\n",argument.nums[1],argument.cadena,argument.nums[0],argument.nums[1],argument.x);
    }
    
    return 0;
}