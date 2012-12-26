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

int listeRapportRedige(int descBr){
  vector<string> lPdfDispo;
  int typeR = 3;
  int tailleMsg = 1;
  char *chaine = "c";
  
  //envoie requete
  int envoie = send(descBr, &typeR, sizeof(int), 0);
  if (envoie <= 0) {
    perror("listeRapport");
    return -1;
    }

  envoie = send(descBr, &tailleMsg, sizeof(int), 0);
  if (envoie <= 0) {
    perror("listeRapport");
    return -1;
  }
  
  envoie = send(descBr, &chaine, sizeof(int), 0);
  if (envoie <= 0) {
    perror("listeRapport");
    return -1;
  }
  
  int typeRR;
  int nbPdf;

  int reception = recv(descBr, &typeRR, sizeof(int), 0);
  if (reception <= 0) {
    perror("");
    return -1;
  }
  
  if (typeRR == 12){

    reception = recv(descBr, &nbPdf, sizeof(int), 0);
    if (reception <= 0) {
      perror("listeRapport");
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
    for (int i(0); lPdfDispo.size(); i++){
      cout<<lPdfDispo[i]<<endl;
    }
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
    
    int envoie = send(descBr, &typeR, sizeof(int), 0);
    if (envoie <= 0) {
      perror("ajout employe");
      return -1;
    }
    
    envoie = send(descBr, &tailleMsg, sizeof(int), 0);
    if (envoie <= 0) {
      perror("ajout employe");
      return -1;
    }
    
    envoie = send(descBr, &chaine, tailleMsg, 0);
    if (envoie <= 0) {
      perror("ajout employe");
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
  
  do{
    
    printf("Identifiant : ");
    scanf("%s", chaine);
    
    int envoie = send(descBr, &typeR, sizeof(int), 0);
    if (envoie <= 0) {
      perror("identification");
      return -1;
    }
    
    envoie = send(descBr, &tailleMsg, sizeof(int), 0);
    if (envoie < 0) {
      perror("identification");
      return -1;
    }
    
    envoie = send(descBr, &chaine, tailleMsg, 0);
    if (envoie <= 0) {
      perror("identification");
      return -1;
    }

    //reception reponse serveur
 
    int reception = recv(descBr, &typeRR, sizeof(int), 0);
    if (reception <= 0) {
      perror("identification");
      return -1;
    }
  }while(typeRR != 6);
  
 

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
  
	
  if (identification(descBrCli) == -1){
    cout<<"echec identification au serveur"<<endl;
    cout<<"Terminaison programme"<<endl;
    close(descBrCli);
    return -1;
  }
  
  int reponse = 0;
  
  cout<<" **************************************** "<<endl;
  cout<<" Vous etez identifier aupres du serveur ! "<<endl;
  cout<<" Quoi faire taper le numero correspondant "<<endl;
  cout<<" **************************************** "<<endl;

  cout<<"1 Envoie liste des employe "<<endl;
  cout<<"2 Consulter liste des rapports rediges"<<endl;

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
      cout<<"echec ajout du dernier employe"<<endl;
      cout<<"Terminaison programme"<<endl;
      close(descBrCli);
      return -1;
    }
    
  default:
    break;
    
    
    
  }
  
  

  close(descBrCli);
  cout<<"Terminaison programme"<<endl;
  return 0;
}

  
