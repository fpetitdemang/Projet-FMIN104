#include <iostream>
#include <errno.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <strings.h>
#include <string.h>


#include "../Sock/sock.h"
#include "../Sock/sockdist.h"
#include <stdlib.h>

	

using namespace std;


//retourne la taille de la donnée à lire
//retourne -1 en cas d'erreur
int infoReception(int descBr, int *num){
  int taille;
  
  int retour = recv(descBr, num, sizeof(int), 0);
  if (retour <= 0) return -1;

  retour = recv(descBr, &taille, sizeof(int), 0);
  if (retour <= 0) return -1;
  
  return taille;  
}

//retourne -1 en cas d'erreur, 0 sinon
int envoieRequete(int descBr, int num, int taille, char *chaine){
 //envoie requete

  //type
  int envoie = send(descBr, &num, sizeof(int), 0);
  if (envoie < 1) {
    perror("send");
    return -1;
    }
 
  //taille
  envoie = send(descBr, &taille, sizeof(int), 0);
  if (envoie < 1) {
    perror("send");
    return -1;
  }
  
  //chaine
  envoie = send(descBr, chaine, sizeof(char)*taille, 0);
  if (envoie < 1) {
    perror("send");
    return -1;
  }

  return 0;
}



int RecupererRapportRedige(int descBr){
  int typeR = 2;
  int tailleMsg = 20;
  char chaine[20];

  printf("nom rapport : ");
  scanf("%s", chaine);

  //demande envoie d'un rapport
  if (envoieRequete(descBr, typeR, tailleMsg, chaine) != 0 ){
    perror("send");
    return -1;
  }

  //reception rapport
  int typeRR;
  int taillePdf = infoReception(descBr, &typeRR);
  
  string nomRapport = (string)chaine + ".pdf"; 
  ofstream flux(nomRapport.c_str());
  
  char car;
  
  cout<<"Encours de téléchargement"<<endl;
  while(taillePdf > 0){
    if (recv(descBr, &car, sizeof(char), 0) <= 0) perror("rcv");
    flux<<car;
    taillePdf--;
  }
   cout<<"Pdf télécharger"<<endl;
  flux.close();
}


int listeRapportRedige(int descBr){
  vector<string> lPdfDispo;
  int typeR = 3;
  int tailleMsg = 1;
  char chaine[2] = "c";
  
  //envoie requete
  if (envoieRequete(descBr, typeR, tailleMsg, chaine) != 0 ){
    perror("send");
    return -1;
  }
 
  
  int typeRR;
  int nbPdf;

  int reception = recv(descBr, &typeRR, sizeof(int), 0);
  if (reception <= 0) {
    perror("rcv");
    return -1;
  }
  
  //serveur s'est deconnecté
  if (typeRR == 7) return -1;
  
  if (typeRR == 12){

    reception = recv(descBr, &nbPdf, sizeof(int), 0);
    if (reception <= 0) {
      perror("rvc");
      return -1;
    }
    

    char tmp[20];
    while(nbPdf > 0){
      reception = recv(descBr, &tmp, sizeof(char)*20, 0);
      if (reception <= 0) {
	perror("listeRapport");
	return -1;
      }
      cout<<tmp<<endl;
      lPdfDispo.push_back(tmp);
      nbPdf--;
    }

    //affiche liste rapport redige
    if (lPdfDispo.size() == 0){
      cout<<"Aucun rapport n'est encore rédigé"<<endl;
    }else{
      cout<<"\n\n\n\nLISTE DES RAPPORTS REDIGES"<<endl;
      for (int i(0); i < lPdfDispo.size(); i++){
	cout<<"\t-"<<lPdfDispo[i]<<endl;
      }
    }
    sleep(5);
    cout<<"\n\n\n\n"<<endl;
    return 0;
  }
  
  return -1;
    

  
  
} 

int ajoutEmploye(int descBr){

  int typeR = 1;
  int tailleMsg = 20;
  char chaine[20];
  
  cout<<"Saisir les noms des employes qui doivent rediger leur rapport"<<endl;
  cout<<"terminer avec la saisit du mot : fin"<<endl;
  
  do{
    
    printf("Nom Employe : ");
    scanf("%s", chaine);

    if (strcmp(chaine,"fin") == 0) return 0;

    //demande envoie d'un rapport
    if (envoieRequete(descBr, typeR, tailleMsg, chaine) != 0 ){
      perror("send");
      return -1;
    }
   
  }while(true);
  
}


//renvoie -1 en cas d'echec, 0 sinon
int identification(int descBr){

  int typeR = 1;
  int typeRR = 0;
  int tailleMsg = 20;
  char chaine[20];
  
  //boucle tant que le serveur valide pas connexion
  do{
    
    printf("Identifiant : ");
    scanf("%s", chaine);
    
    //demande envoie d'un rapport
    if (envoieRequete(descBr, typeR, tailleMsg, chaine) < 0 ){
      perror("send");
      return -1;
    }

    //reception reponse serveur
 
    int reception = recv(descBr, &typeRR, sizeof(int), 0);
    if (reception <= 0) {
      perror("recv");
      return -1;
    }
    
    //serveur s'est deconnecté
    if (typeRR == 7) return -1;

  }while(typeRR != 6);
  
  return 0;

}


int main(int argc, char *argv[]){
  
  char HOST[255];
  int PORTC;
  int PORTS;
  printf("n° BR client : ");
  scanf("%i", &PORTC);

  printf("n° BR serveur : ");
  scanf("%i", &PORTS);

  printf("adresse serveur : ");
  scanf("%s", HOST);

  cout << "\n\nClient en route" << endl;
  cout << "===============\n" << endl;
  

  
  //Demande Boite Reseau Privée
  Sock brCli(SOCK_STREAM,PORTC,0);
  int descBrCli;
  if(brCli.good()){
    descBrCli = brCli.getsDesc();
    perror("Creation BR privee");  
  }else{
    perror("Creation BR privee");  
    exit(1);
  }
  
  //BR distante
  SockDist brPub(HOST, (short)PORTS);
  struct sockaddr_in *adrBrPub= brPub.getAdrDist();
  int lgAdrBrPub=sizeof(struct sockaddr_in);

  
  //Demande de connexion
  if (connect(descBrCli,(struct sockaddr *)adrBrPub, lgAdrBrPub) < 0){
    perror("Demande connexion");
    exit(1);
  }else{
    perror("Demande connexion");
  }
  
	
  if (identification(descBrCli) != 0){
    cout<<"echec identification au serveur"<<endl;
    cout<<"Terminaison programme"<<endl;
    close(descBrCli);
    return -1;
  }
  
  int reponse = 0;
  
  cout<<" **************************************** "<<endl;
  cout<<" Vous etes identifier aupres du serveur ! "<<endl;
  cout<<" Saisir le numeros de l'action a effectuer"<<endl;
  cout<<" **************************************** "<<endl;

  do{
  cout<<"1 Saisir la liste des employes pour le rapport "<<endl;
  cout<<"2 Consulter la liste des rapports rediges"<<endl;
  cout<<"3 Recuperer un rapport"<<endl;
  cout<<"6 Terminer programme"<<endl;

  scanf("%i", &reponse);
  
  switch(reponse){
  case 1:
    if (ajoutEmploye(descBrCli) != 0){
      cout<<"echec ajout du dernier employe"<<endl;
      cout<<"Terminaison programme"<<endl;
      close(descBrCli);
    return -1;
    }
    break;

  case 2: 
    if (listeRapportRedige(descBrCli) != 0){
      cout<<"echec consultation des rapport"<<endl;
      cout<<"Terminaison programme"<<endl;
      close(descBrCli);
      return -1;
    }
    break;

  case 3: 
    if (RecupererRapportRedige(descBrCli) != 0){
      cout<<"echec recuperation rapport"<<endl;
      cout<<"Terminaison programme"<<endl;
      close(descBrCli);
      return -1;
    }
    break;
    
  default:
    break;
    
    
    
  }
  
  }while(reponse != 6);
  
  

  close(descBrCli);
  cout<<"Terminaison programme"<<endl;
  return 0;
}

  
