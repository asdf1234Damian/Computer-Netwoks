#include <stdlib.h>
#include <iostream>
#include <string.h>
// #include <linux/in.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>


int main(int argc, char const *argv[]){
    //Recibir agumengos de IO
    if (argc<3){
        perror("Faltan Argumentos");
    }
    char *ipAddr = (char*)argv[1];
    int port = atoi(argv[2]);
    //Cliente 
    
    //--Socket
    int miSocket = socket(AF_INET,SOCK_STREAM,0);
    if (miSocket<-1){perror("Mamó el socket");exit(-1);}

    //--Connect
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(ipAddr);
    server.sin_family = AF_INET;
    server.sin_port = port;

    //Public ala direccion o puerto donde el server se va a ejecutar
    if (bind(miSocket,(sockaddr*)&server,sizeof(struct sockaddr_in))<0){
        perror("Error publishing");
    }
    if (connect(miSocket,(sockaddr*)&server,sizeof(struct sockaddr_in))<0){
        perror("Error connecting");
    }

    //--Listening for connections 
    listen(miSocket,2);
    struct sockaddr_in client;
    int sizeClient = sizeof(client) ;
    int chnnl = accept(miSocket,(struct sockaddr*)&client,sizeClient);
    if (chnnl < 0 ){
        perror("Error al crear conecion");
    }

    //--Comunicando
    char buffer[50];
    if (recv(miSocket,(void*)buffer,strlen(buffer),0) != strlen(buffer)<0){
        perror("Mamó el rcv");
    }

    strcpy(buffer,"Hola amigo");
    if (send(miSocket,(void*)buffer,strlen(buffer),0) != strlen(buffer)){
        perror("Mamó el send");
    }
    

    buffer[strlen(buffer)] = '\0';
    std::cout<<"Mensaje recibido del servidor "<<buffer;
    close(chnnl);

    return 0;

}
