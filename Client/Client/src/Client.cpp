/*
 * Client.cpp
 *
 *  Created on: Oct 13, 2010
 *      Author: lucachaco
 */

#include "Client.h"
#include "ArchivoBinario.h"

#include <ctime>
#include "Bitacora.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <sys/time.h>
#include <errno.h>
using namespace std;

Client::Client(int argc, char *argv[]) {

	int contador=0;

	if (argc < 3) {
		printf("Error en parámetros, recuerdo son 3:\nEl primero la dirección ip del servidor\nEl segundo la cantidad de repeticiones que desea transmitir el archivo \nEl tercera el nùmero que identifica el tamaño de los archivos a transmitir\n   1 para archivos de 1 KByte\n   2 para archivos de 10 KBytes\n   3 para archivos de 1 MByte\n   4 para archivos de 5 MBytes");
		exit(0);
	}
	int repeticiones=atoi(argv[2]);
	char * fileSize;
	switch(atoi(argv[3])){//identificador archivo
				case 0:
					break;
				case 1:
					fileSize = "1 KByte";
					break;
				case 2:
					fileSize = "10 KBytes";
					break;
				case 3:
					fileSize = "1 MByte";
					break;
				case 4:
					fileSize = "10 MBytes";
					break;
			   }

	if (argc = 4) {
		printf("Parametro correctos. Ud seleccionó:\nArchivos de %s y %d repeticiones",fileSize,repeticiones);
		exit(0);
	}
	Bitacora bitacora("bitacora.txt",fileSize,repeticiones);
	while(contador<repeticiones){

		int sockfd, portno, n, newsockfd;
		struct sockaddr_in serv_addr;
		struct hostent *server;

		portno = 44779;
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0){ //verifica si se creo el socket
			printf("ERROR opening socket");
		}
		server = gethostbyname(argv[1]);
		if (server == NULL) {
			fprintf(stderr, "ERROR, no such host\n");
			exit(0);
		}
		bzero((char *) &serv_addr, sizeof(serv_addr));//inicializa ser_addr a cero
		serv_addr.sin_family = AF_INET;//inicializa la variable sin_family, que contiene el codigo de la familia de direcciones
		bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
		serv_addr.sin_port = htons(portno);//esta variable de la struct contiene el numero del puerto, pero primero se debe convertir a un network byte order(no se me ocurre una traduccion apropiada) por medio de la funcion htons
		if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
			printf("ERROR connecting client, está seguro que servidor está corriendo?\n");//se intenta conectar con el servidor, sino puede tira un error y se sale
			return;
		}

		char * nombreArchivo = "Default";
		const int BYTES_1_KB=   1024;
		const int BYTES_10_KB=  10240;
		const int BYTES_1_MB  = 1048576;
		const int BYTES_5_MB  = 5242880;
		const int BYTES_10_MB = 10485760;
		const int BYTES_50_MB = 52428800;
		//******Cambiar aquí*************************************************************************************
		//*******************************************************************************************************
		//*******************************************************************************************************
		//*******************************************************************************************************
		int size=BYTES_5_MB;
		//*******************************************************************************************************
		//*******************************************************************************************************
		//*******************************************************************************************************
		//*******************************************************************************************************
		switch(size){
			case 0:
				break;
			case BYTES_1_KB:
				nombreArchivo = "1_KByte.txt";
				break;
			case BYTES_10_KB:
				nombreArchivo = "10_KBytes.txt";
				break;
			case BYTES_1_MB:
				nombreArchivo = "1_MByte.txt";
				break;
			case BYTES_5_MB:
				nombreArchivo = "5_Mbytes.txt";
				break;
			case BYTES_10_MB:
				nombreArchivo = "10_MBytes.txt";
				break;
			case BYTES_50_MB:
				nombreArchivo = "50_MBytes.txt";
				break;
			default:
				size=-1;
				break;
		   }
		ArchivoBinario* archivoBinario= new ArchivoBinario(nombreArchivo);
		 char * miBuffer=archivoBinario->getBuffer();
		timeval t1, t2;
		long double elapsedTime;


		gettimeofday(&t1,NULL);

		//**************************
		//n = send(sockfd, miBuffer, strlen(miBuffer),0);//escribe en el socket lo que hay en el buffer, y guarda el retorno de la funcion para escribir en el socket en n
		n= Escribe_Socket(sockfd,miBuffer, strlen(miBuffer));
		//**********************
		gettimeofday(&t2,NULL);
		if (n < 0){ //si n < 0 hubo error y sale
			printf("ERROR writing to socket cliente\n");
		}
		char buffer[5];//buffer donde guarda los caracteres que le entran desde el socket
		bzero(buffer, 5);
		//****************************
		//n = recv(sockfd, buffer, 5,0);         //lee el el socket y lo copia al buffer

		n= Lee_Socket(sockfd,buffer,5);
		//****************************
		if (n < 0){
			printf("ERROR reading from socket cliente\n");//error por si no pudo leerlo
		}
	//	printf("\nServidor me respondió: %s\n", buffer);//imprime el mensaje*/

		//elapsedTime = ((t2.tv_sec-t1.tv_sec)*1000.0)+((t2.tv_usec-t1.tv_usec)/1000.0);
		elapsedTime = ((t2.tv_sec-t1.tv_sec)*1000000.0)+((t2.tv_usec-t1.tv_usec));
		printf(" \n [%Lf] ms.", elapsedTime);
		bitacora.agregarEntrada(elapsedTime);
		contador++;
	}
	bitacora.cerrar();
}
int Client::Lee_Socket (int fd, char *Datos, int Longitud){
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
int Client::Escribe_Socket (int fd, char *Datos, int Longitud)
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

Client::~Client() {
	// TODO Auto-generated destructor stub
}
