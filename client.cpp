/*
 * client.cpp
 *
 *  Created on: 13 déc. 2012
 *      Author: Nordine
 */



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
int identifier = 0;



/*************Fonction****************/


/********* Demande de connection ********/

int DemandeConnect()
{

	cout<<"  *************************************** "<<endl;
	cout<< " --------  DEMANDE DE CONNECTION -------"<<endl;
	cout<<"  *************************************** "<<endl;
	char HOST[255];
  int PORTC;
  int PORTS;
	

  printf("n° BR client : ");
	
  scanf("%i", &PORTC);

  printf("n° BR serveur : ");
  scanf("%i", &PORTS);

  printf("adresse serveur : ");
  scanf("%s", HOST);
	
	cout<<" ******************* "<<endl;
  cout << " Client en route " << endl;
  cout << " =============== \n" << endl;
  
	/*
  
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
*/
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
	cout<<" ******************* "<<endl;
	cout<<" Identifiant envoyé "<<endl;
	cout<<" ******************* "<<endl;
	//int reponse;
	//int rep = recv(descBrCli, &reponse, sizeof(reponse), 0); 
	int rep = 1;


	return rep;
}


/******** Demande de redaction aupres du serveur *****/

int DemandeRedac()
{


/*** 
		envoi de la demande de redac
		Et attente de retour 1 ou 0 
***/


	int typeR = 9;
  send(descBrCli, &typeR, sizeof(int), 0);
	cout<<" **************************** "<<endl;
	cout<<" Demande de redaction envoyer "<<endl;
	cout<<" **************************** "<<endl;
	
	//int rep = recv(descBrCli, &reponse, sizeof(reponse), 0); 
	int rep;

return rep;
}

/******** Redaction des bloc rapport aupres du serveur *****/

void Redac()
{
}

/******** Demande de sauvegarde du rapport apres du serveur *****/

void Sauvegarde()
{

}




/******** Demande de deconnection *****/

void Deconnection()
{
	cout<<" ******************************** "<<endl;
	cout<<" FERMETURE DE TOUTE COMMUNICATION "<<endl;
	cout<<" ******************************** "<<endl;
	exit(1);
}




/************************** Main ********************/

int main(int argc, char *argv[]){

//char Recep[256];
//int res = recv (descrBR
  
	int faire;
	cout<<" **************************************** "<<endl;
	cout<<" Quoi faire taper le numero correspondant "<<endl;
	cout<<" **************************************** "<<endl;
	cout<<" 1 demande de connection"<<endl;	
  //cout<<"9 demande de redaction "<<endl;

  scanf("%i", &faire);

/*******

 Traitement en fonction de l'entre clavier

 ******/


	if(faire == 1)
	{
		int reDemmande = DemandeConnect();
		if(reDemmande != 1)
		{
   		 cout<<" ********************* "<<endl;
			 perror("Demande de connection");
			 cout<<" ********************* "<<endl;
			 exit(1);
			
		}else
					{
 					 int reponseIdent = Identif();
					 if(reponseIdent != 1)
					 {
							 perror("Probleme d'Identification");
							 exit(1);
					 }else
								{
									cout<<" **************************************** "<<endl;
									cout<<" Vous etez identifier aupres du serveur ! "<<endl;
									cout<<" Quoi faire taper le numero correspondant "<<endl;
									cout<<" **************************************** "<<endl;
									cout<<" 9 demande de redaction "<<endl;
									cout<<" 2 demande de  deconnection "<<endl;
									scanf("%i", &faire);
									
									if(faire == 2)
									{
									Deconnection();
									}
			
									if(faire == 9)
									{
										int reponseRedac = DemandeRedac();
										if(reDemmande != 1)
										{	
											 perror(" Demande de redaction ");
									 		 exit(1);
										}else
											{
												cout<<" Demande de redaction autorise ! "<<endl;
												Redac();
											}
									}
									
										
								}

								
				
  				}
}



  
  
  
  return 0;
}

  
