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

			int reception = recv(descBr, &type, sizeof(int), 0);

		    /*Traitement cas erreurs*/
		    if (reception < 0){
		      perror("recv");
		      close(descBr);
		      cout<<"Fermeture connection client"<<endl;
		      pthread_exit(NULL);
		    }

		    if(reception == 0){
		      perror("send");
		      cout<<"Fermeture connection client"<<endl;
		      pthread_exit(NULL);
		    }
		    /*Fin traitement cas erreurs*/

		    //Lit taille msg a lire//
		     reception = recv(descBr, &taille, sizeof(int), 0);

		     /*Traitement erreur*/
		    if (reception < 0){
		      perror("recv");
		      close(descBr);
		      cout<<"Fermeture connection client"<<endl;
		      pthread_exit(NULL);
		    }

		    if(reception == 0){
		      perror("send");
		      cout<<"Fermeture connection client"<<endl;
		      pthread_exit(NULL);
		    }

		    //Recupere msg de la requete
		    chaine =(char *) malloc(taille);

		    reception = recv(descBr, chaine, taille, 0);

		    /*Traitement erreur*/
		    if (reception < 0){
		      perror("recv");
		      close(descBr);
		      cout<<"Fermeture connection client"<<endl;
		      pthread_exit(NULL);
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

