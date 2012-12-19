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
int	taille = 255;



/*************Fonction****************/

/******** Identification aupres du serveur *****/

int Identif(int brclient)
{

	int typeR;
  int tailleMsg;
  char chaine[20];
  int descBrCli = brclient;

	printf("n° identifiant : ");
  scanf("%s", chaine);
	tailleMsg = sizeof(chaine);
	typeR = 1;


/***** Envoi du message ***/

  int sendTy =  send(descBrCli, &typeR, sizeof(int), 0);	
	if(sendTy  < 0)
		{
		perror("1 envoi");
		return -1;
		}else{
					int sendTailleMsg = send(descBrCli, &tailleMsg, sizeof(int), 0);
					if(sendTailleMsg  < 0)
					{
					perror("2 envoi");
					return -1;
					}else{
							int sendChaine = send(descBrCli, chaine, sizeof(chaine), 0); 
							if(sendChaine  < 0)
							{
								perror(" 3 envoi");
								return -1;
								}else{

											cout<<" ******************* "<<endl;
											cout<<" Identifiant envoyé "<<endl;
											cout<<" ******************* "<<endl;

											int rep = recv(descBrCli, &typeR, sizeof(int), 0);
											if(rep  < 0)
											{
												//cout <<typeR<<endl;
												perror("Probleme reception dans focntion identification");
												return -1;
												}else{
															int retour = typeR;
															//cout <<rep<<endl;
															cout <<retour<<endl;
															return retour;
															}
										}
								}
						}
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

/*
	Demande de deconnection pour faire ça proprement 
	Envoi au serveur la deconnection
	type = 2
*/

	int typeR = 2;
  send(descBrCli, &typeR, sizeof(int), 0);


	cout<<" ******************************** "<<endl;
	cout<<" FERMETURE DE TOUTE COMMUNICATION "<<endl;
	cout<<" ******************************** "<<endl;

	exit(1);
}




/************************** Main ********************/

int main(int argc, char *argv[]){


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
  
	
  
  //Demande Boite Reseau Privée
  Sock brCli(SOCK_STREAM,PORTC,0);
  int descBrCli;
  if(brCli.good()){
    descBrCli = brCli.getsDesc();
  
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


	int faire;
	cout<<" **************************************** "<<endl;
	cout<<" Quoi faire taper le numero correspondant "<<endl;
	cout<<" **************************************** "<<endl;
	cout<<" 1 demande d'identification "<<endl;	


  scanf("%i", &faire);

/*******

 Traitement en fonction de l'entre clavier

 ******/

/*
	if(faire == 1)
	{
		int reDemmande = DemandeConnect();
		if(reDemmande != 1)
		{
   		 cout<<" ********************* "<<endl;
			 perror("Demande d'identication");
			 cout<<" ********************* "<<endl;
			 exit(1);
			
		}else
					{*/
				if(faire == 1)
				{
 					 int reponseIdent = Identif(descBrCli);
					 if(reponseIdent != 6)
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
										if(reponseRedac != 1)
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

								




  
  
  
  return 0;
}

  
