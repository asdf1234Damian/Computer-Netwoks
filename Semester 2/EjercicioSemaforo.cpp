#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>


sem_t semProd,semCons;
pthread_t producer,consumer;
int critZ;

void* prodF(void* arg){
    for (size_t i = 1; i < 21; i++){
        sem_wait(&semProd);
        critZ = i;
        std::cout<<"Produciendo:"<<critZ<<std::endl;
        sem_post(&semCons);
    }
}

void* consF(void* arg){
    for (size_t i = 1; i < 21; i++){
        sem_wait(&semCons);
        std::cout<<"Consumiendo:"<<critZ<<std::endl;
        sem_post(&semProd);
    }
}


int main(int argc, char const *argv[]){
    //Paso 1: Crear semaforo
    if (sem_init(&semProd,0,1) && sem_init(&semCons,0,0)){
        std::cout<<"Valio verga el semaforo\n";
        return 0;
    }

    //Paso 2: Crear los hilos

    pthread_create(&producer,NULL,&prodF,NULL);
    pthread_create(&consumer,NULL,&consF,NULL);
    //Esperar a que terminen los hilos
    pthread_join(producer,NULL);
    pthread_join(consumer,NULL);

    sem_destroy(&semProd);
    sem_destroy(&semCons);

    return 0;
}
