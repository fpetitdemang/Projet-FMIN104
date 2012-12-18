/*
 * Employe.cpp
 *
 *  Created on: 11 déc. 2012
 *      Author: franck
 */

#include "Employe.h"

Employe::Employe(SubjectClient* cli) : Reponse(cli){}

void Employe::TraitementMsg() {
	Message msgR = _subjet->getMessage();
	cout<<"Message Reçut :\n"<<endl;
	msgR.Affiche();

	switch(msgR.type){

	case 7://deconnexion
	  _subjet->Deconnexion();
	  break;
	  
	case 9://reception section rapport
	  _subjet->ecrireRapport(msgR.chaine);
	  break;

	case 10://sauvegarde + envoie rapport
	  _subjet->ouvreRapport();
	  _subjet->envoieRapport();
	  break;
	  
	
	default://cas d'erreur	  
	  cout<<"requete pas reconnu"<<endl;
	  break;

	}
}

Employe::~Employe() {}
