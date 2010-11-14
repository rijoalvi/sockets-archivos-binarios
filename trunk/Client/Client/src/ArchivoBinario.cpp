/*
 * archivoBinario.cpp
 *
 *  Created on: Nov 3, 2010
 *      Author: lucachaco
 */

#include "ArchivoBinario.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <sys/time.h>
using namespace std;

ArchivoBinario::ArchivoBinario() {


}

ArchivoBinario::ArchivoBinario(char * nombreArchivo) {
	this->nombreArchivo=nombreArchivo;
}

char * ArchivoBinario::getBuffer(){
	ifstream::pos_type size;
	char * memblock;
	ifstream infile (this->nombreArchivo,ios::in|ios::binary|ios::ate);
	if(infile.is_open()){
		infile.seekg(0,ifstream::end);
		size=infile.tellg();
		memblock=new char [size];
		infile.seekg(0,ios::beg);
		infile.read(memblock,size);

		infile.close();
		//cout<<"the complete file content is in memory "<<size;
	}
	else{
		cout<<"Unable to open file";
	}
	return memblock;
}
void ArchivoBinario::crearArchivoAPartirDeBuffer(char * nombreArchivo, char * buffer,int size){
	ofstream outfile (nombreArchivo,ofstream::binary);

	outfile.write(buffer,size);
	outfile.close();

}
ArchivoBinario::~ArchivoBinario() {
	// TODO Auto-generated destructor stub
}
