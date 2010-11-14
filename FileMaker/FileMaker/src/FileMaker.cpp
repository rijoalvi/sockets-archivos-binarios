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

//#include <time.h>


using namespace std;

int main() {
	struct timespec clock_resolution;
	int stat;

	//stat=clock_getres(CLOCK_REALTIME, &clock_resolution);
	//printf("time returns %d seconds \n", time(NULL));
	//clock_gettime(CLOCK_REALTIME,&clock_resolution);

	//printf("Clock resolution is %d seconds, %ld nanoseconds\n",	clock_resolution.tv_sec, clock_resolution.tv_nsec);
//******************************************************************************************************
	timeval t1, t2;
	long double elapsedTime;
	gettimeofday(&t1,NULL);

//******************************************************************************************************

	ofstream myfile;

	myfile.open("nuevo.txt");
	int oneMB=1048576;
	int oneKB=1024;
	for(int i=0; i<oneMB*5; i++){
		myfile<<"*";
	}

	myfile.close();
//	cout<<"d "<<&ts;
	cout << "\n!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	gettimeofday(&t2,NULL);
	//elapsedTime = (t2.tv_usec-t1.tv_usec);

	elapsedTime = ((t2.tv_sec-t1.tv_sec)*1000.0)+((t2.tv_usec-t1.tv_usec)/1000.0);

	//cout<<elapsedTime<<" ms.";
	printf("%Lf ms.", elapsedTime);
	//printf("%ld\n",(t2.tv_sec-t1.tv_sec));
}
