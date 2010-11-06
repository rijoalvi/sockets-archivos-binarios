/*
 * TablaEnrutamiento.h
 *
 *  Created on: Oct 13, 2010
 *      Author: lucachaco
 */
#include <iostream>
#include <fstream>
using namespace std;

#ifndef TABLAENRUTAMIENTO_H_
#define TABLAENRUTAMIENTO_H_

class TablaEnrutamiento {
public:
	ifstream* myfile;

	TablaEnrutamiento();
	TablaEnrutamiento(char * nombreArchivo);
	void getIPAccordingToSize0(char * nombreArchivo);
	char * getIPAccordingToSize(char * nombreArchivo,char * fileSize);
	virtual ~TablaEnrutamiento();
};

#endif /* TABLAENRUTAMIENTO_H_ */
