#include "Controleur.h"

Controleur::Controleur(SubjectClient* cli) : Reponse(cli){}

void Controleur::TraitementMsg() {
	Message msgR = _subjet->getMessage();
	switch(msgR.type){
	    
	  //Recuper employe devant rediger un rapport client->serveur
	case 1 : 
	  cout<<"ajout employe"<<endl;
	  _subjet->ajoutEmploye();
	  break;

	  //Envoie un pdf serveur->client
	case 2:
	  _subjet->envoieRapport((string)msgR.chaine);
	  break;
	  
	  //Envoie liste des rapports redigé serveur->client
	case 3:
	  _subjet->envoieLpdfRedige();
	  break;
	  
	  //Deconnexion
	case 7:
	  _subjet->Deconnexion();
	  break;

	default://cas d'erreur	  
	  cout<<"requete pas reconnu"<<endl;
	  break;

	}
}

Controleur::~Controleur() {}
