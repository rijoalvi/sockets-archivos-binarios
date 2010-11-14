//============================================================================
// Name        : Client.cpp
// Author      : Client
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Client.h"
#include "ArchivoBinario.h"

using namespace std;

int main(int argc, char *argv[]) {
	//ArchivoBinario* archi= new ArchivoBinario();
	/*int size=10;
	char * buffer=new char[size];
	buffer=archi->getBuffer("example.txt");
	archi->crearArchivoAPartirDeBuffer("nuevoss.txt",buffer,size);
	delete [] buffer;*/

	Client* client=new Client(argc, argv);

	cout << "!!!Terminado exitosamente!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
