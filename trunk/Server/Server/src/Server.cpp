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
#include <errno.h>

Server::~Server() {

}
int Server::Lee_Socket (int fd, char *Datos, int Longitud){
	int Leido = 0;
	int Aux = 0;

	/*
	* Comprobacion de que los parametros de entrada son correctos
	*/
	if ((fd == -1) || (Datos == NULL) || (Longitud < 1))
		return -1;

	/*
	* Mientras no hayamos leido todos los datos solicitados
	*/
	while (Leido < Longitud)
	{
		Aux = read (fd, Datos + Leido, Longitud - Leido);
		if (Aux > 0)
		{
			/*
			* Si hemos conseguido leer datos, incrementamos la variable
			* que contiene los datos leidos hasta el momento
			*/
			Leido = Leido + Aux;
		}
		else
		{
			/*
			* Si read devuelve 0, es que se ha cerrado el socket. Devolvemos
			* los caracteres leidos hasta ese momento
			*/
			if (Aux == 0)
				return Leido;
			if (Aux == -1)
			{
				/*
				* En caso de error, la variable errno nos indica el tipo
				* de error.
				* El error EINTR se produce si ha habido alguna
				* interrupcion del sistema antes de leer ningun dato. No
				* es un error realmente.
				* El error EGAIN significa que el socket no esta disponible
				* de momento, que lo intentemos dentro de un rato.
				* Ambos errores se tratan con una espera de 100 microsegundos
				* y se vuelve a intentar.
				* El resto de los posibles errores provocan que salgamos de
				* la funcion con error.
				*/
				switch (errno)
				{
					case EINTR:
					case EAGAIN:
						usleep (100);
						break;
					default:
						return -1;
				}
			}
		}
	}

	/*
	* Se devuelve el total de los caracteres leidos
	*/
	return Leido;
}
int Server::Escribe_Socket (int fd, char *Datos, int Longitud)
{
	int Escrito = 0;
	int Aux = 0;

	/*
	* Comprobacion de los parametros de entrada
	*/
	if ((fd == -1) || (Datos == NULL) || (Longitud < 1))
		return -1;

	/*
	* Bucle hasta que hayamos escrito todos los caracteres que nos han
	* indicado.
	*/
	while (Escrito < Longitud)
	{
		Aux = write (fd, Datos + Escrito, Longitud - Escrito);
		if (Aux > 0)
		{
			/*
			* Si hemos conseguido escribir caracteres, se actualiza la
			* variable Escrito
			*/
			Escrito = Escrito + Aux;
		}
		else
		{
			/*
			* Si se ha cerrado el socket, devolvemos el numero de caracteres
			* leidos.
			* Si ha habido error, devolvemos -1
			*/
			if (Aux == 0)
				return Escrito;
			else
				return -1;
		}
	}

	/*
	* Devolvemos el total de caracteres leidos
	*/
	return Escrito;
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



			const int BYTES_1_KB = 1024;
			const int BYTES_10_KB = 10240;
			const int BYTES_1_MB  = 1048576;
			const int BYTES_5_MB  = 5242880;

			const int BYTES_10_MB = 10485760;
			const int BYTES_50_MB = 52428800;


			//******Cambiar aquí*************************************************************************************
			//*******************************************************************************************************
			//*******************************************************************************************************
			//*******************************************************************************************************
			int size=BYTES_5_MB;// 1 KByte
			//*******************************************************************************************************
			//*******************************************************************************************************
			//*******************************************************************************************************
			//*******************************************************************************************************

			char buffer[size];
	      bzero(buffer,size);
	      //******************
	      //n = recv(newsockfd,buffer,size,0);

	      n = Lee_Socket(newsockfd, buffer, size);
	      //*********************
	      if (n < 0) printf("ERROR reading from socket server\n");//error por si no pudo leerlo

	       ArchivoBinario* archi= new ArchivoBinario();
	       archi->crearArchivoAPartirDeBuffer("fileCopiado.txt",buffer,size);
	      //******************



	  	// printf("Servidor está corriendo para archivos");

	      //printf("Cliente tranfirió archivo de tamaño: %d\n",size);//imprime el mensaje
	      //n = send(newsockfd,ip,18,0);//devuelve que recibio el mensaje
	      //**************
	    //  n = send(newsockfd,"exito",5,0);//devuelve que recibio el mensaje

	      n=Escribe_Socket(newsockfd,"exito",5);
	      //***************
	      if (n < 0){
	    	  printf("Error\n");
	      }
			else{
			//printf("Respuesta enviada\n");
		}

	      //wait(3000);
	   }
	     exit(0);

}
