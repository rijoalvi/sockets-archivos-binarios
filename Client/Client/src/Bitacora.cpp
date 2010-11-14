/*
 * Bitacora.cpp
 *
 *  Created on: Nov 7, 2010
 *      Author: lucachaco
 */

#include "Bitacora.h"
#include <iostream>
#include <fstream>

Bitacora::Bitacora() {

}
Bitacora::Bitacora(char * nombreArchivo, char* encabezadao, int numeroRepeticiones) {

	myFile.open(nombreArchivo);
	myFile<<"Tamaño de archivos transmitidos: ["<<encabezadao<<"]"<<"\n";
	myFile<<"Número repeticiones: ["<<numeroRepeticiones<<"]"<<"\n";
}
void Bitacora::agregarEntrada(long double entrada){
	myFile<<entrada<<"\n";
}
void Bitacora::cerrar(){
	myFile.close();
}
Bitacora::~Bitacora() {
	// TODO Auto-generated destructor stub
}
