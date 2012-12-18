/*
 * SubjectClient.cpp
 *
 *  Created on: 8 déc. 2012
 *      Author: franck
 */

#include "SubjectClient.h"

#include <iostream>
#include <string>
#include <cstdio>

SubjectClient::SubjectClient() {
	descBr = 0;
}

SubjectClient::SubjectClient(int pDescBr, char * nomClient){
	descBr = pDescBr;
	descPdf = 0;
	strcpy(nom,nomClient);
}


void SubjectClient::run(){
	//Se met en lecture sur la boite de reception//
	while(true){
		printf("Thread client en attente de reception :\n");
		msgR = Message(descBr);

	    //averti observeur de la reception du msg
	    Notify();
	}
}

int SubjectClient::ecrireRapport(char* chaine){
  //int Ecrit(const char *message, const char *employe);
  //retour -1 en cas d'erreur
  return -1;
}

int  SubjectClient::ouvreRapport(){
  //int OuvreRapport(const char *employe);
  return -1;
}

Message SubjectClient::getMessage(){
	return msgR;
}

int SubjectClient::getDescrPdf(){
  return descPdf;
}

char* SubjectClient::getNom(){
  return nom;
}

SubjectClient::~SubjectClient() {
	// TODO Auto-generated destructor stub
}
