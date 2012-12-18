/*
 * ReponseEmploye.cpp
 *
 *  Created on: 8 déc. 2012
 *      Author: franck
 */

#include "Reponse.h"

Reponse::Reponse() {
	// TODO Auto-generated constructor stub
}

Reponse::Reponse(SubjectClient* cli){
	_subjet = cli;
	_subjet->Attach(this);
}

void Reponse::Update(Subject* theChangedSubject){

	if(theChangedSubject == _subjet)
	{
		TraitementMsg();
	}
}

void Reponse::TraitementMsg(){
	Message msgR = _subjet->getMessage();
	cout<<"Message Reçut :\n"<<endl;
	msgR.Affiche();
}

Reponse::~Reponse() {
	_subjet->Detach(this);
}

