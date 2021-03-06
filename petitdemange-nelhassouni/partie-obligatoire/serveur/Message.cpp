/*
 * Message.cpp
 *
 *  Created on: 8 déc. 2012
 *      Author: franck
 */

#include "Message.h"


Message::Message() {
	type = 0;
	taille = 255;
}

Message::Message(int type, int taille, char *chaine){
	this->type = type;
	this->taille = taille;
	this->chaine = chaine;
}

Message::Message(int descBr){

  //REcupere type de requete
  int reception = recv(descBr, &type, sizeof(int), 0);
  if (reception <= 0) throw reception;

  //Lit taille msg a lire//
  reception = recv(descBr, &taille, sizeof(int), 0);
  if (reception <= 0 || taille > 500) throw reception;
    

  //Recupere msg de la requete
  if (taille > 0){
    chaine =(char *) malloc(taille);
    reception = recv(descBr, chaine, taille, 0);
    if (reception <= 0) throw reception;
  }else{
    chaine = NULL;
  }

}

void Message::Affiche(){
	cout<<"Type : "<<type<<endl;
	cout<<"Taille : "<<taille<<endl;
	cout<<"Chaine : "<<chaine<<endl;
}

Message::~Message() {
	// TODO Auto-generated destructor stub
}

