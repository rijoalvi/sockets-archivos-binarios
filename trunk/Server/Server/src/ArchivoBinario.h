/*
 * archivoBinario.h
 *
 *  Created on: Nov 3, 2010
 *      Author: lucachaco
 */

#ifndef ARCHIVOBINARIO_H_
#define ARCHIVOBINARIO_H_

class ArchivoBinario {
public:
	ArchivoBinario();
	ArchivoBinario(char *);
	char * getBuffer(char *);
	void crearArchivoAPartirDeBuffer(char * , char * ,int );
	virtual ~ArchivoBinario();
};

#endif /* ARCHIVOBINARIO_H_ */
