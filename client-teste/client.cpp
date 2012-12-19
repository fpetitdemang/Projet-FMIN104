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




#include "../Sock/sock.h"
#include "../Sock/sockdist.h"

#include <stdlib.h>




using namespace std;

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
  
	
  
 //Authentif
  int typeR = 1;
  int tailleMsg = 20;
  char chaine[20]="employe";
  int retour;

  send(descBrCli, &typeR, sizeof(int), 0);
  send(descBrCli, &tailleMsg, sizeof(int), 0);	
  send(descBrCli, chaine, sizeof(chaine), 0);
  
  //recueper reponse authentif
  recv(descBrCli, &typeR, sizeof(int), 0);

  
  //Envoie requete demande rapport
  typeR = 10;
  send(descBrCli, &typeR, sizeof(int), 0);
  send(descBrCli, &tailleMsg, sizeof(int), 0);	
  send(descBrCli, chaine, sizeof(chaine), 0);
  
  
  //Recupere rapport
  cout<<recv(descBrCli, &typeR, sizeof(int), 0)<<endl;
  cout<<"Type recut :"<<typeR<<endl;
  cout<<recv(descBrCli, &tailleMsg, sizeof(int), 0)<<endl;
  cout<<"Taille : "<<tailleMsg<<endl;
  
  
  ofstream flux("teste.pdf");
  char car;
  
  while(tailleMsg > 0){
    cout<<"attend reception"<<endl;
    if (recv(descBrCli, &car, sizeof(char), 0) != 0) perror("rcv");
    flux<<car;
    tailleMsg--;
    cout<<tailleMsg<<endl;
  }
  
  flux.close();
  close(descBrCli);

  return 0;
}

  
