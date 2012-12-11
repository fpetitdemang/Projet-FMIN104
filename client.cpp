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

// données global//

int descBrCli;



/*************Fonction****************/


/********* Demande de connection ********/

int DemandeConnect()
{

	cout<< " --------  DEMANDE DE CONNECTION -------"<<endl;
	

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
  if (connect(descBrCli,(struct sockaddr *)adrBrPub, lgAdrBrPub) < 0) {
    perror("Demande connexion");
    exit(1);
  }else{
    perror("Demande connexion");
  }

return 1;
  
}


/******** Identification aupres du serveur *****/


int Identif()
{
	int IDENT;
	printf("n° identifiant : ");
  scanf("%i", &IDENT);

// *** envoi de l'identifiant et attente de retour 1 ou 0 ***//
	int Num = IDENT;
	int typeR = 1;
  send(descBrCli, &typeR, sizeof(int), 0);
	send(descBrCli, &Num, sizeof(int), 0);

	cout<<" Identifiant envoyé "<<endl;
	
	int reponse;
	int rep = recv(descBrCli, &reponse, sizeof(reponse), 0); 
	


	return reponse;
}


/******** Demande de redaction aupres du serveur *****/

void DemandeRedac()
{


}

/******** Redaction des bloc rapport aupres du serveur *****/
void Redac()
{
}

/******** Demande de sauvegarde du rapport apres du serveur *****/

void Sauvegarde()
{

}



/************************** Main ********************/

int main(int argc, char *argv[]){

//char Recep[256];
//int res = recv (descrBR
  
	int faire;

	cout<<"Quoi faire taper le numero correspondant "<<endl;
	cout<<"1 demande de connection"<<endl;
	cout<<"9 demande de redaction "<<endl;
	
	
  scanf("%i", &faire);

	if(faire == 1)
	{
		while(1)
		{
			DemandeConnect();
		}
		Identif();
  }
	if(faire == 9)
	{
	}


  
  do{

  }while(1);
  
  
  return 0;
}

  
