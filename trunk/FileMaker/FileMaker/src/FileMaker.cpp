//============================================================================
// Name        : FileMaker.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main() {

	ofstream myfile;
	timespec ts;
	myfile.open("10MB.txt");
	for(int i=0; i<1000000000; i++){
		myfile<<"*";
	}

	myfile.close();
	cout<<"d "<<&ts;
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
}
