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
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>


void afficherPaquet(){}

/**
 *num : type du msg
 *msg : chaine a concatener dans le message
 *Retourne paquet avec la semantique
 *              1er octet : type de message
 *              2eme octet : taille de la chaine a lire
 *              [3eme octet à taille] : message
 */
char* forgerPaquet(char *num, char *msg){
  
  int tailleMsg = sizeof(msg);

  char * paquet = (char *)malloc(sizeof(char) * (tailleMsg + 2));
  
 
  strcat(paquet,  htonl(num));//mettre little big indian
  strcat(paquet, "255");
  strcat(paquet, msg);
  //exit(1);
  return paquet;
}

using namespace std;

int main(int argc, char *argv[]){
  
  char msg [20] = "toto";
  cout<<forgerPaquet("3",msg)<<endl;

  return 0;
}
