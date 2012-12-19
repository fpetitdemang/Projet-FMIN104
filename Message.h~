/*
 * Message.h
 *
 *  Created on: 8 déc. 2012
 *      Author: franck
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_


#include <stdio.h>
#include <iostream>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

using namespace std;

class Message {
public:
	int type;
	int taille;
	char* chaine;
	Message();
	//Construit message à partir d'une BR
	Message(int descBr);
	Message(int type, int taille, char *chaine);
	virtual void Affiche();
	virtual ~Message();
};

#endif /* MESSAGE_H_ */
