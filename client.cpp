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




#include "Sock/sock.h"
#include "Sock/sockdist.h"

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
  
	
  
  do{

  }while(1);
  
  
  return 0;
}

  
