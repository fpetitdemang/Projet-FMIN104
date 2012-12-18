/*
 * Employe.cpp
 *
 *  Created on: 11 déc. 2012
 *      Author: franck
 */

#include "Employe.h"

Employe::Employe(SubjectClient* cli) : Reponse(cli){}

void Employe::Traitement() {
	Message msgR = _subjet->getMessage();
	cout<<"Message Reçut :\n"<<endl;
	msgR.Affiche();

	switch(msgR.type){
	  
	case 4://reçoit requete rapport	
	  //recupere contenu 
	  //ecrit dans le rapport
	  break;
	case 5:
	  break;
	default:
	  break;

	}


}

Employe::~Employe() {}
