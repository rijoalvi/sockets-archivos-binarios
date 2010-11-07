/*
 * Client.cpp
 *
 *  Created on: Oct 13, 2010
 *      Author: lucachaco
 */

#include "Client.h"
#include "ArchivoBinario.h"

#include <ctime>

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <sys/time.h>

using namespace std;

Client::Client(int argc, char *argv[]) {
    int sockfd, portno, n, newsockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;


    if (argc < 2) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = 44779;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) //verifica si se creo el socket
    	printf("ERROR opening socket");

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));//inicializa ser_addr a cero
    serv_addr.sin_family = AF_INET;//inicializa la variable sin_family, que contiene el codigo de la familia de direcciones
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);//esta variable de la struct contiene el numero del puerto, pero primero se debe convertir a un network byte order(no se me ocurre una traduccion apropiada) por medio de la funcion htons
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    	printf("ERROR connecting client");//se intenta conectar con el servidor, sino puede tira un error y se sale
    //while(1){

    	//printf("Que tamaño de paquete desea enviar? ");//si se conecta pide el mensaje

       char * fileSize="102400";




       char * nombreArchivo = "1K_Byte.txt";

       ArchivoBinario* archi= new ArchivoBinario();
       //int size=10;
       int size=1024;// 1 KByte
       //int size=1048576;// 1 MByte
       //int size=10485760;// 10 MByte





       char * miBuffer=archi->getBuffer(nombreArchivo);

       timeval t1, t2;
       long double elapsedTime;
       gettimeofday(&t1,NULL);
       elapsedTime=strlen(miBuffer);
       printf("[tamaño: [%d] .", strlen(miBuffer));
       n = send(sockfd, miBuffer, strlen(miBuffer),0);//escribe en el socket lo que hay en el buffer, y guarda el retorno de la funcion para escribir en el socket en n
       if (n < 0) //si n < 0 hubo error y sale
        	printf("ERROR writing to socket cliente\n");
       char buffer[5];//buffer donde guarda los caracteres que le entran desde el socket
        bzero(buffer, 5);
        n = recv(sockfd, buffer, 5,0);         //lee el el socket y lo copia al buffer
        if (n < 0){
        	printf("ERROR reading from socket server\n");//error por si no pudo leerlo
	}
        printf("\nServidor me respondió: %s\n", buffer);//imprime el mensaje*/
    	gettimeofday(&t2,NULL);

    	elapsedTime = ((t2.tv_sec-t1.tv_sec)*1000.0)+((t2.tv_usec-t1.tv_usec)/1000.0);

    	printf("[%Lf] ms.", elapsedTime);


}

Client::~Client() {
	// TODO Auto-generated destructor stub
}
