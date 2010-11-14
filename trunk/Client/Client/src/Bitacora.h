/*
 * Bitacora.h
 *
 *  Created on: Nov 7, 2010
 *      Author: lucachaco
 */
#include <iostream>
#include <fstream>
using namespace std;
#ifndef BITACORA_H_
#define BITACORA_H_

class Bitacora {
public:
	char * nombreArchivo;
	ofstream myFile;
	Bitacora();
	Bitacora(char *);
	Bitacora(char * nombreArchivo, char* encabezadao, int numeroRepeticiones);
	void agregarEntrada(long double);
	void cerrar();

	virtual ~Bitacora();
};

#endif /* BITACORA_H_ */
