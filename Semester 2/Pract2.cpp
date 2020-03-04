#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>


const int SLEEPCONST = 0;
sem_t semWriteA[4], semWriteB[4], semRead[8];
pthread_t thrd_P[5],thrd_C[5];
int p_ID[5],c_ID[5];
char crt_ZA[4],crt_ZB[4];


void* prodF(void* arg){
    int n = *((int*)arg);
    // std::cout<<"Proceso" <<n+1<<"creado";
    int m = 0;
    bool zoneA = true;
    for (int i = 0; i < 20000;){
        if(zoneA){
            if (sem_trywait(&semWriteA[m])<0){
                // std::cout<<"\t\t\t\tsem"<<m<<"ocupado     \n";
                m = (m+1)%4;
            }else{
                // std::cout<<"sem"<<m<<"libre     \n";
                crt_ZA[m] = char(n+'a');
                // std::cout<<"Produciendo: "<<crt_ZA[m]<<" en zonaA "<<m<<std::endl;
                zoneA = !zoneA;i++;
                sem_post(&semRead[m]);
            }
        }else{
            if (sem_trywait(&semWriteB[m])<0){
                // std::cout<<"\t\t\t\tsem"<<m<<"ocupado     \n";
                m = (m+1)%4;
            }else{
                // std::cout<<"sem"<<m<<"libre     \n";
                crt_ZB[m] = char(n+'1');
                // std::cout<<"Produciendo: "<<crt_ZB[m]<<" en zonaA "<<m<<std::endl;
                zoneA = !zoneA;i++;
                sem_post(&semRead[m+4]);
            }
        }
        // sleep(SLEEPCONST);
    }
}

void* consF(void* arg){
    int  n = *(int*) arg, m = 0;
    std::string pth;
    pth +="./out/";pth +=char(n+'0');pth+=".txt";
    FILE *Output;
    char c;
    for (int i = 0; i < 20000;){
        if (sem_trywait(&semRead[m])<0){
            // std::cout<<"Sem ocupado cons "<<m<<std::endl;
            m = (m+1)%8;
        }else{
            c = (m<4?crt_ZA[m]:crt_ZB[m%4]);
            // semIndex = c - (m<4?'a':'1'-4);
            pth = "./out/";pth += c;pth += ".txt";
            // if (sem_wait(&semWriteFile[semIndex])==0){
                Output = fopen(pth.c_str(),"a+");
                if (Output==NULL){perror(0);}
                fprintf(Output,"%c\n",c); 
                fclose(Output);
                i++;
                if(m<4){
                    sem_post(&semWriteA[m]);
                }else{
                    sem_post(&semWriteB[m%4]);
                }
                // sem_post(&semWriteFile[semIndex]);
            // }
        }
        // sleep(SLEEPCONST);
    }
}


int main(int argc, char const *argv[]){
    // std::cout<<"Creando semaforos\n";
    for (int i = 0; i < 8; i++){
        if (sem_init(&semRead[i],0,0)){std::cout<<"Sem fail";return 0;}
        if (i<4){
            if (sem_init(&semWriteA[i]  ,0,1)){std::cout<<"Sem fail";return 0;}
            if (sem_init(&semWriteB[i],0,1)){std::cout<<"Sem fail";return 0;}
        }
        
    }
    // for (size_t i = 0; i < 10; i++){
    //     if (sem_init(&semWriteFile[i],0,1)){std::cout<<"Sem fail";return 0;}
    // }
    
    // std::cout<<"Todos los semaforos han sido creados\n";
    // std::cout<<"Creando proceso \n";
    for (int i = 0; i < 5; i++){
        p_ID[i] = i;
        pthread_create(&thrd_P[i],NULL,prodF,&p_ID[i]);
        c_ID[i] = i;
        pthread_create(&thrd_C[i],NULL,consF,&c_ID[i]);
    }
    // std::cout<<"Procesos creados\n";
    for (int i = 0; i < 5; i++){
        pthread_join(thrd_P[i],NULL);
        pthread_join(thrd_C[i],NULL);
    }
    for (int i = 0; i < 8; i++){
        if(i<4){
            sem_destroy(&semRead[i]);
            sem_destroy(&semWriteB[i]);
            sem_destroy(&semWriteA[i]);
        }
        // sem_destroy(&semWriteFile[i]);
    }
    // std::cout<<"Procesos terminado\n";
}


