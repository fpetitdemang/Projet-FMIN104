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

SubjectClient::SubjectClient(int pDescBr, verrou *m_verrou){
	descBr = pDescBr;
	descPdf = 0;
	connecter = true;
	mes_verrou = m_verrou;
	sauvRapport = false;

}


void SubjectClient::run(){
  //Se met en lecture sur la boite de reception//
  while(connecter){
    //printf("Thread client en attente de reception :\n");
    
    try{
      msgR = Message(descBr);
      //averti observeur de la reception du msg
      Notify();
    }catch(int  &descr){
      //perror("recv");
      break;
    }
  }
}

int SubjectClient::ecrireRapport(char* chaine){
  return Ecrit(msgR.chaine,nom);
}

int  SubjectClient::ouvreRapport(){
  int res = OuvreRapport(nom);
  
  pthread_mutex_lock(&mes_verrou->VlEmploye);
  mes_verrou->lPdf.push_back((string)nom);//ajout pdf à la liste de rapport redigé
  pthread_mutex_unlock(&mes_verrou->VlEmploye);
  
  sauvRapport=true;
  return res;
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
  envoieRapport((string)nom);
}

int SubjectClient::envoieRapport(string nom){

  //recupere descripteur en lecture sur le pdf 
  string cheminPdf = nom + "/" "temp.pdf";
  ifstream fichierPdf(cheminPdf.c_str());

  //calcule taille
  fichierPdf.seekg(0,ios::end);
  int taillePdf = fichierPdf.tellg();
  fichierPdf.seekg(0,ios::beg);


  cout<<"Taille pdf a envoyé : "<<taillePdf<<endl;
  
  //envoie typeRequete
  int typeR = 11;
  int envoie = send(descBr,&typeR,sizeof(int),0);
  if (envoie < 0) throw envoie;

  //envoie taillePdf
  envoie = send(descBr,&taillePdf,sizeof(int),0);
  if (envoie < 0) throw envoie;

  char car;
  //envoie pdf octet par octet
  while(fichierPdf.get(car))
    {
      envoie = send(descBr,&car,sizeof(char),0);
      if (envoie < 0) {
	throw envoie;
	return -1;
	break;
      }
    }
  fichierPdf.close();

  cout<<"\""<<this->nom<<"\" a recut le rapport \""<<nom<<"\""<<endl;
  
  return 0;
}

int SubjectClient::envoieLpdfRedige(){
  
  //envoie typeRequete
  int typeR = 12;
  int envoie = send(descBr,&typeR,sizeof(int),0);
  if (envoie < 0) throw envoie;
  
  pthread_mutex_lock(&mes_verrou->VlPdf);
  //envoie nb de rapport redige
  int nbElmt = mes_verrou->lPdf.size();
  envoie = send(descBr, &nbElmt,sizeof(int),0);
  if (envoie < 0) throw envoie;
  
  //envoie element vecteur 
  for(int i(0); i < mes_verrou->lPdf.size(); i++){
    envoie = send(descBr,mes_verrou->lPdf[i].c_str(),sizeof(char)*20,0);
  }
  pthread_mutex_unlock(&mes_verrou->VlPdf);
  
  return 0;
}

int SubjectClient::ajoutEmploye(){
  
  pthread_mutex_lock(&mes_verrou->VlEmploye);
  //Tests si l'employe n'est pas deja dans la liste
  for (int i(0); i< mes_verrou->lEmploye.size(); i++){
    if ( mes_verrou->lEmploye[i] == (string)msgR.chaine) return -1;
  }
  mes_verrou->lEmploye.push_back((string)msgR.chaine);
  cout<<nom<<" a ajouté \""<<msgR.chaine<<"\" dans la liste des employes"<<endl;
  pthread_mutex_unlock(&mes_verrou->VlEmploye);
  return 0;

}

int SubjectClient::Deconnexion(){
  connecter = false;
  if(!sauvRapport) ouvreRapport();
  return 0;
}

int SubjectClient::Connexion(){
	int compt = 0;
	int retour = -1;

	//3 tentatives d'authentification
	while (compt < 3){

	  try{
		Message MsgR(descBr);


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
			if(RechercheListeClientAuth(MsgR.chaine))  {
				retour = 6;
				strcpy(nom,MsgR.chaine);
				send(descBr,&retour,sizeof(int),0);
				return 1;
			}
		}


		//Envoie message d'echec
		if (compt < 2){  
		  //mauvais identifiant
		  retour = 5;
		  if (send(descBr,&retour,sizeof(int),0) <= 0) throw descBr;
		}
		
	
		
		compt++;

	  }catch(int  &descBr){
	    perror("recv ");
	    return -1;
	  }

	}

	//retourne -1 si client non identifier
	//Envoie message d'echec
	return -1;

	}

bool SubjectClient:: RechercheListeClientAuth(char* chaine){

  pthread_mutex_lock(&mes_verrou->VlEmploye);
  for(int i(0); i < mes_verrou->lEmploye.size(); ++i)
   {
     if ( mes_verrou->lEmploye[i] == (string)chaine) {
       pthread_mutex_unlock(&mes_verrou->VlEmploye);
       return true;
     }
   }
  pthread_mutex_unlock(&mes_verrou->VlEmploye);
  return false;
}

SubjectClient::~SubjectClient() {
	// TODO Auto-generated destructor stub
}

