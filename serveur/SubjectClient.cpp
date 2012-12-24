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

SubjectClient::SubjectClient(int pDescBr){
	descBr = pDescBr;
	descPdf = 0;
	connecter = true;
	//strcpy(nom,nomClient);
}


void SubjectClient::run(){
	//Se met en lecture sur la boite de reception//
  while(connecter){
    printf("Thread client en attente de reception :\n");
    
    try{
      msgR = Message(descBr);//generer exeption
      
      //averti observeur de la reception du msg
      Notify();
    }catch(int  &descr){
      perror("recv");
      close(descBr);
      cout<<"Fermeture connection client"<<endl;
      pthread_exit(NULL);
    }
  }
    //remettre dans un etat coherent la reception des msg

}

int SubjectClient::ecrireRapport(char* chaine){
  return 1;
  //return Ecrit(msgR.chaine,nom);
}

int  SubjectClient::ouvreRapport(){
  return 1;
  // return OuvreRapport(nom);
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

int SubjectClient::envoieRapport(){

  //recupere descripteur en lecture sur le pdf 
  string cheminPdf = (string)nom + "/" "temp.pdf";
  ifstream fichierPdf("nordine/temp.pdf");
  fichierPdf.seekg(0,ios::end);
  int taillePdf = fichierPdf.tellg();
  fichierPdf.seekg(0,ios::beg);
  //fichierPdfLecture.close();

  cout<<"taille pdf envoyé"<<taillePdf<<endl;

  //envoie typeRequete
  int typeR = 11;
  send(descBr,&typeR,sizeof(int),0);

  //envoie taillePdf
  send(descBr,&taillePdf,sizeof(int),0);

  char car;
  //envoie pdf octet par octet
  while(fichierPdf.get(car))
    {
      send(descBr,&car,sizeof(char),0);
    }

  
  return -1;
}

int SubjectClient::Deconnexion(){
  cout<<"Fermeture BR client"<<endl;
  connecter = false;
  int retour = close(descBr);

  return retour;
}

int SubjectClient::Connexion(vector<string> pListeClientAuth){
	int compt = 0;

	int retour = -1;
	cout<<"Authentification"<<endl;
	//3 tentatives d'authentification
	while (compt < 4){

	  //try{
		Message MsgR(descBr);
		/*}catch(int  &descBr){
	    perror("recv");
	    close(descBr);
	    cout<<"Phase authentification Fermeture connection client"<<endl;
	    pthread_exit(NULL);
	    }*/

		//si paquet identification, traitement
		if (MsgR.type == 1){
			//verifie si controleur
			if (strcmp(MsgR.chaine,"controleur") == 0) {
				retour = 6;
				strcpy(nom,"controleur");
				send(descBr,&retour,sizeof(int),0);
				return 0;
			}
			//verifie si employe
			if(RechercheListeClientAuth(pListeClientAuth, MsgR.chaine))  {
				retour = 6;
				strcpy(nom,MsgR.chaine);
				send(descBr,&retour,sizeof(int),0);
				return 1;
			}
		}

		//Envoie message d'echec
		retour = 5;
		send(descBr,&retour,sizeof(int),0);
		compt++;
	}


	//retourne -1 si client non identifier
	return -1;

	}

bool SubjectClient:: RechercheListeClientAuth(vector<string> pListeClientAuth, char* chaine){

  for(int i(0); i<pListeClientAuth.size(); ++i)
   {
     if (pListeClientAuth[i] == (string)chaine) return true;
   }
  return false;
}

SubjectClient::~SubjectClient() {
	// TODO Auto-generated destructor stub
}

