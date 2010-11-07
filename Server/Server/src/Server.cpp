/*
 * Server.cpp
 *
 *  Created on: Oct 13, 2010
 *      Author: lucachaco
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>//para el hilo

//para el socket
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "Server.h"
#include "TablaEnrutamiento.h"
#include "ArchivoBinario.h"

Server::~Server() {

}

Server::Server() {
	  int sockfd, newsockfd, portno, clilen;  //sockfd y portno son descriptores de archivo. estas variables
	                                             //guardan los valores retornados por la llamada al sistema del socket y
	                                             //la llamada al sistema de aceptacion.
	                      //buffer para almacenar el mensaje
	   struct sockaddr_in serv_addr, cli_addr; //sockaddr_in es una estructura que guarda una direccion de internet
	   int n;                                  // n guarda el valor de retorno de read() y write()

	   sockfd = socket(AF_INET, SOCK_STREAM, 0);//crea un socket continuo

	   if (sockfd < 0)                         //por si no se pudo abrir el socket
		   printf("ERROR opening socket");
	   bzero((char *) &serv_addr, sizeof(serv_addr));//inicializar en cero serv_addr
	   portno = 44779;                 //transforma en numero el numero de puerto

	   serv_addr.sin_family = AF_INET;         //inicializa la variable sin family con la constante AF_INET
	   serv_addr.sin_addr.s_addr = INADDR_ANY;
	   serv_addr.sin_port = htons(portno);
	   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		   printf("ERROR on binding");//verificando que la dir sea valida



	   while(1){
		   listen(sockfd,5);                       //se pone a escuchar el socket
		   clilen = sizeof(cli_addr);
		   newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, (socklen_t*)&clilen);//acepta el mensaje
		   if (newsockfd < 0)                      //error si no se completa
			   printf("ERROR on accept");


	      //int size=10;// 10 Bytes
	      int size=1024;// 1 KByte
	       //int size=1048576;// 1 MByte
	       //int size=10485760;// 10 MByte
		   char buffer[size];
	      bzero(buffer,size);
	      n = recv(newsockfd,buffer,size,0);
	       ArchivoBinario* archi= new ArchivoBinario();
	       archi->crearArchivoAPartirDeBuffer("fileCopiado.txt",buffer,size);
	      //******************

	  	TablaEnrutamiento* tabla=new TablaEnrutamiento();
	      if (n < 0) printf("ERROR reading from socket server\n");//error por si no pudo leerlo

	  	char * ip=tabla->getIPAccordingToSize("tabla_enrutamiento",buffer);

	      //******************


	      printf("Cliente tranfirió archivo de tamaño: %d\n",size);//imprime el mensaje
	      //n = send(newsockfd,ip,18,0);//devuelve que recibio el mensaje
	      n = send(newsockfd,"exito",5,0);//devuelve que recibio el mensaje
	      if (n < 0){
	    	  printf("Error\n");
	      }
			else{
			printf("Respuesta enviada\n");
		}

	      //wait(3000);
	   }
	     exit(0);

}
