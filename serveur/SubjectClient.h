/*
 * SubjectClient.h
 *
 *  Created on: 8 déc. 2012
 *      Author: franck
 */

#ifndef SUBJECTCLIENT_H_
#define SUBJECTCLIENT_H_

#include "../Observer/Subject.h"
#include "Message.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include "structures.cpp"
#include <fstream>
#include <iostream>
#include "fournisSujet1/sauvegarde.h"

class SubjectClient : public Subject{
private :
  int descBr;//descritpeur sur la BR du CV
  Message msgR;
  char nom[20];
  int descPdf;//file descritpeur sur le fichier pdf
  bool connecter;
  bool sauvRapport;
  verrou *mes_verrou;

public:
	SubjectClient();
	SubjectClient(int pDescBr, verrou *m_verrou);
	virtual Message getMessage();
	virtual char* getNom();
	virtual int getDescrPdf();
	virtual void run();
	virtual int ecrireRapport(char* chaine);
	virtual int  ouvreRapport();
	virtual int envoieRapport();
	virtual int envoieRapport(string nom);
	//rajoute msg.chaine dans liste des employe
	//retourne -1 en cas erreur, 0 sinon
	virtual int ajoutEmploye();
	virtual int envoieLpdfRedige();
	virtual int Connexion();
	virtual int Deconnexion();
	virtual bool RechercheListeClientAuth(char* chaine);
	virtual ~SubjectClient();

};

#endif /* SUBJECTCLIENT_H_ */
