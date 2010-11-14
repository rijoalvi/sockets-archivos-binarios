/*
 * Server.h
 *
 *  Created on: Oct 13, 2010
 *      Author: lucachaco
 */

#ifndef SERVER_H_
#define SERVER_H_

class Server {
public:
	virtual ~Server();
	int Lee_Socket (int fd, char *Datos, int Longitud);
	int Escribe_Socket (int fd, char *Datos, int Longitud);
	Server();
};

#endif /* SERVER_H_ */
