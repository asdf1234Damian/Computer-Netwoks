#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

sem_t sem[4];
pthread_t thrd_P[4],thrd_C[4];
int p_ID[4],c_ID[4];
char footprint[] = {'A','B','C','D'};
char crt_Z[2];

void* prodF(void* arg){
    int n = *((int*)arg);
    char c = footprint[n];
    for (int i = 0; i < 20;){
        if (1+sem_trywait(&sem[0])){
            crt_Z[0] = c;
            // std::cout<<"\nProduciendo en cz 0";
            i++;
            sem_post(&sem[2]);
        }
        if(1+sem_trywait(&sem[1])){
            crt_Z[1] = c;
            // std::cout<<"\nProduciendo: en cz 1";
            i++;
            sem_post(&sem[3]);
        }
    }
}

void* consF(void* arg){
    int n = *((int*)arg);
    for (int i = 0; i < 20;){
        if (1+sem_wait(&sem[2])){
            std::cout<<"Consumiendo: "<<crt_Z[0]<<'\n';
            i++;
            sem_post(&sem[0]);
        }

        if(1+sem_wait(&sem[3])){
            std::cout<<"Consumiendo: "<<crt_Z[1]<<'\n';
            i++;
            sem_post(&sem[1]);
        }
    }
}


int main(int argc, char const *argv[]){
    for (int i = 0; i < 4; i++){
        if (sem_init(&sem[i],0,1)){
            std::cout<<"Sem fail";
            return 0;
        }
    }

    for (int i = 0; i < 4; i++){
        p_ID[i] = i;
        pthread_create(&thrd_P[i],NULL,prodF,&p_ID[i]);
        c_ID[i] = i;
        pthread_create(&thrd_C[i],NULL,consF,&c_ID[i]);
    }

    for (int i = 0; i < 4; i++){
        pthread_join(thrd_P[i],NULL);
        pthread_join(thrd_C[i],NULL);
    }
}


