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

/*

int forgerPaquet(const int proto,const char msg){
	
  int tailleMsg = 0; 
	tailleMsg = strlen(msg);
	char * paquet = (char *)malloc(sizeof(char) * (tailleMsg);

	printf(Paquet);	
  return Paquet;

}

*/


int forgetPaget(const int proto, const char msg)
{
/*********************Struct que l'on va retourne ***/

typedef Paquet Paquet;
struct Paquet{
int num;
char message;
}

int taille = strlen(msg);

/*****************Controle que la taille est pas plus grande que 256 *********/

if(taille > 256)
{
	fprint (" taille trop grande ")
}

Paquet.num = proto;
Paquet.message = msg;

return Paquet;
}



using namespace std;

int main(int argc, char *argv[]){
  
  char msg [20] = "toto";
	forgerPaquet(2,msg);



  return 0;
}
