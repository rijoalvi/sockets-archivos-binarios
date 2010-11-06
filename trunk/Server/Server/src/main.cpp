//============================================================================
// Name        : Server.cpp
// Author      : lucachaco@gmail.com
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Server.h"
#include "TablaEnrutamiento.h"
using namespace std;

int main() {
	//TablaEnrutamiento* tabla=new TablaEnrutamiento("tabla_enrutamiento");
	//TablaEnrutamiento* tabla=new TablaEnrutamiento();
//	char * ip=tabla->getIPAccordingToSize("tabla_enrutamiento","102401");
//	printf("\nIp a mandar: %s",ip);
	Server * server=new Server();
	//cout << "!!!Hello World222!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
