/*
 * TablaEnrutamiento.cpp
 *
 *  Created on: Oct 13, 2010
 *      Author: lucachaco
 */

#include "TablaEnrutamiento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>

TablaEnrutamiento::TablaEnrutamiento() {
	// TODO Auto-generated constructor stub

}
TablaEnrutamiento::TablaEnrutamiento(char * nombreArchivo) {
	/* ofstream myfile;
	  myfile.open ("example2.txt");
	  myfile << "Writing this to a file.\n";
	  myfile.close();*/

	this->myfile=new ifstream(nombreArchivo);
	string line;

	 if (myfile->is_open())
	  {
		 printf("archivo abierto");
		   while ( myfile->good() )
		    {
		      getline (*myfile,line);
		      cout << line << endl;
		    }
		    myfile->close();

	  }else {
		  printf("archivo no abierto");
	  }

	// TODO Auto-generated constructor stub

}
void TablaEnrutamiento::getIPAccordingToSize0(char * nombreArchivo) {


	this->myfile=new ifstream(nombreArchivo);
	string line;

	 if (myfile->is_open())
	  {
		 printf("archivo abierto222");
		   while ( myfile->good() )
		    {
		      getline (*myfile,line);

		     // char* buf="aaaaaaaaaaaaaaa";

		   //   line.su
		      char *buf=new char[strlen(line.c_str())];
		      strcpy(buf,line.c_str());


		     // strcpy(buf,line);



		     // cout << line << endl;

		      char * pch;
		      pch=strtok(buf,"\t ");
		      printf("[%s]",line.c_str());
		      while(pch!=NULL){
		    	  printf("{%s}",pch);
		    	  pch=strtok(NULL,"\t ");
		      }



		    }
		    myfile->close();

	  }else {
		  printf("archivo no abierto");
	  }

	// TODO Auto-generated constructor stub

}
char * TablaEnrutamiento::getIPAccordingToSize(char * nombreArchivo,char * fileSize) {

	int fileSizeNumber=0;
	char * pEnd;
	fileSizeNumber=strtol(fileSize,&pEnd,10);
	this->myfile=new ifstream(nombreArchivo);
	string line;

	 if (myfile->is_open())
	  {
		 printf("Leída tabla enrutamiento....\n");
		   while ( myfile->good() )
		    {
		      getline (*myfile,line);

		     // char* buf="aaaaaaaaaaaaaaa";

		   //   line.su
		      char *buf=new char[strlen(line.c_str())];
		      strcpy(buf,line.c_str());


		     // strcpy(buf,line);



		     // cout << line << endl;

		      char * pch;
		      pch=strtok(buf,"\t ");
		      if(0==strcmp(pch,"~")){//si se llegó al final de archivo
	    		  fileSize=pch;

		    	  pch=strtok(NULL,"\t ");

		    	  myfile->close();
		    	  return pch;
		      }
		      int contador=0;
		      //while(pch!=NULL){

		    	  //printf("\n%d {%s}",contador,pch);
		    	  int currentFileSizeNumber=0;
		    	  currentFileSizeNumber=strtol(pch,&pEnd,10);//paso a int el tamaño de la linea actual


		    	  if(fileSizeNumber<=currentFileSizeNumber){//match
		    		  fileSize=pch;

			    	  pch=strtok(NULL,"\t ");
			    	  contador++;
			    	  myfile->close();
			    	  return pch;
		    	  }

		    	  pch=strtok(NULL,"\t ");
		    	  contador++;
		    	//  printf("\n%d {%s}",contador,pch);

		      //}



		    }
		    myfile->close();

	  }else {
		  printf("archivo no abierto");
	  }

	// TODO Auto-generated constructor stub

}
TablaEnrutamiento::~TablaEnrutamiento() {
	// TODO Auto-generated destructor stub
}
