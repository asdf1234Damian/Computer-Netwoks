#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_P[3],sem_C[2];
pthread_t thrd_P[3],thrd_C[2];
int p_ID[3],c_ID[2];
char start[] = {'0','A','!'};
char crt_Z,acc;

void* prodF(void* arg){
    int n = *((int*)arg);
    char s = start[n];
    for (int i = 0; i < 10; i++){
        sem_wait(&sem_P[n]);
        crt_Z = s+i;
        acc = n+1;
        std::cout<<"Produciendo: "<<crt_Z<<" desde "<<n<<std::endl;
        // std::cout<<" delegando a: " <<(n+i)%2<<std::endl; 
        sem_post(&sem_C[(n+i)%2]);
    }
}

void* consF(void* arg){
    int n = *((int*)arg);
    for (int i = 0; i < 15; i++){
        sem_wait(&sem_C[n]);
        std::cout<<"\tConsumiendo: "<<crt_Z<<" desde "<< n<<std::endl;
        // std::cout<<" regresando a: " <<acc%3<<std::endl; 
        sem_post(&sem_P[acc%3]);
    }

}

int main(int argc, char const *argv[]){
    std::cout<<"Creando semaforos \n";
    if(sem_init(&sem_P[0],0,1)){
            std::cout<<"Sem fail";
            return 0;
    }
    
    for (int i = 0; i < 2; i++){
        if (sem_init(&sem_C[i],0,0) && sem_init(&sem_P[i+1],0,0)){
            std::cout<<"Sem fail";
            return 0;
        }
    }
    std::cout<<"Creando hilos \n";
    for (int i = 0; i < 3; i++){
        p_ID[i] = i;
        pthread_create(&thrd_P[i],NULL,prodF,&p_ID[i]);
    }
    for (int i = 0; i < 2; i++){
        c_ID[i] = i;
        pthread_create(&thrd_C[i],NULL,consF,&c_ID[i]);
    }
    for (int i = 0; i < 3; i++){
        pthread_join(thrd_P[i],NULL);
    }

    std::cout<<"Terminaron Prod\n";
    for (int i = 0; i < 2; i++){
        pthread_join(thrd_C[i],NULL);
    }   
    
    return 0;
}