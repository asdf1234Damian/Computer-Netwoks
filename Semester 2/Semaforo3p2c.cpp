#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>


sem_t semCrit,semLttr,semSymb,semCons;
pthread_t prodNums,prodLttr,prodSymb,consumer;
char critZ;

void* prodNumF(void* arg){
    for (size_t i = 0; i < 10; i++){
        sem_wait(&semCrit);
        critZ = char(i+int('0'));
        std::cout<<"Produciendo:"<<critZ<<std::endl;
        sem_post(&semCons);
    }
    sem_wait(&semCrit);
    sem_post(&semLttr);
    sem_post(&semCrit);
}

void* prodLttrF(void* arg){
    sem_wait(&semLttr);
    for (size_t i = 0; i < 10; i++){
        sem_wait(&semCrit);
        critZ = char(i+int('A'));
        std::cout<<"Produciendo:"<<critZ<<std::endl;
        sem_post(&semCons);
    }
    sem_wait(&semCrit);
    sem_post(&semSymb);
    sem_post(&semCrit);
}

void* prodSymbF(void* arg){
    sem_wait(&semSymb);
    for (size_t i = 0; i < 10; i++){
        sem_wait(&semCrit);
        critZ = char(i+int('!'));
        std::cout<<"Produciendo:"<<critZ<<std::endl;
        sem_post(&semCons);
    }
}

void* consF(void* arg){
    for (size_t i = 0; i < 30; i++){
        sem_wait(&semCons);
        std::cout<<"Consumiendo:"<<critZ<<std::endl;
        sem_post(&semCrit);
    }
}


int main(int argc, char const *argv[]){
    //Paso 1: Crear semaforo
    if (sem_init(&semCrit,0,1) && sem_init(&semCons,0,0)
        && sem_init(&semLttr,0,1) && sem_init(&semSymb,0,1)){
        std::cout<<"Valio verga el semaforo\n";
        return 0;
    }

    //Paso 2: Crear los hilos

    pthread_create(&prodNums,NULL,&prodNumF,NULL);
    pthread_create(&prodLttr,NULL,&prodLttrF,NULL);
    pthread_create(&prodSymb,NULL,&prodSymbF,NULL);
    pthread_create(&consumer,NULL,&consF,NULL);
    //Esperar a que terminen los hilos
    pthread_join(prodNums,NULL);
    pthread_join(prodLttr,NULL);
    pthread_join(prodSymb,NULL);
    pthread_join(consumer,NULL);

    sem_destroy(&semCrit);
    sem_destroy(&semLttr);
    sem_destroy(&semSymb);
    sem_destroy(&semCons);

    return 0;
}

