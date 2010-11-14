/*
 * Client.h
 *
 *  Created on: Oct 13, 2010
 *      Author: lucachaco
 */

#ifndef CLIENT_H_
#define CLIENT_H_

class Client {
public:

	Client(int argc, char *argv[]);
	int Lee_Socket (int fd, char *Datos, int Longitud);
	int Escribe_Socket (int fd, char *Datos, int Longitud);
	virtual ~Client();
};

#endif /* CLIENT_H_ */
