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
#include <iostream>
#include <fstream>
#include <string>


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
		perror("1 Identif");
		return -1;
		}else{
					int sendTailleMsg = send(descBrCli, &tailleMsg, sizeof(int), 0);
					if(sendTailleMsg  < 0)
					{
					perror("2 Identif");
					return -1;
					}else{
							int sendChaine = send(descBrCli, chaine, sizeof(chaine), 0); 
							if(sendChaine  < 0)
							{
								perror(" 3 Identif");
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

int Redac(int brclient)
{

	int typeR;
  int tailleMsg;
  char chaine[255];
  int descBrCli = brclient;
	


  while (true)
	{
	printf("votre Redaction : ");
  scanf("%s", chaine);
	tailleMsg = sizeof(chaine);
	typeR = 9;
	
	if(strcmp(chaine,"fini") == 0)
		{
		cout<<" *****fini** "<<endl;
		return 1;
		}else
		{
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

											cout<<" **************** "<<endl;
											cout<<" Redaction Envoyé "<<endl;
											cout<<" **************** "<<endl;
											

}
			}
		}

	}
}
return 1;


}


/******** Demande de sauvegarde du rapport apres du serveur *****/

int SauvRapport(int brclient)
{
	int typeR;
  int tailleMsg;
  char chaine[20];
  int descBrCli = brclient;
	
	tailleMsg = sizeof(chaine);
	typeR = 10;

	int sendTy =  send(descBrCli, &typeR, sizeof(int), 0);	
		if(sendTy  < 0)
			{
			perror("1 Sauve rapport");
			return -1;
			}else{
						int sendTailleMsg = send(descBrCli, &tailleMsg, sizeof(int), 0);
						if(sendTailleMsg  < 0)
						{
						perror("2 Sauve rapport");
						return -1;
						}else{
								int sendChaine = send(descBrCli, chaine, sizeof(chaine), 0); 
								if(sendChaine  < 0)
								{
									perror(" 3 Sauve rapport");
									return -1;
									}else{

											cout<<" **************** "<<endl;
											cout<<" Sauvegarde envoyé "<<endl;
											cout<<" **************** "<<endl;
											return 1;
												}
									}
							}
}



/******** Demande d'Envoi du rapport apres du serveur *****/

int EnvoiRapport(int brclient)
{
	int typeR;
  int tailleMsg;
  char chaine[20];
  int descBrCli = brclient;
	
	tailleMsg = sizeof(chaine);
	typeR = 11;

/***** Envoi du message ***/

  	int sendTy =  send(descBrCli, &typeR, sizeof(int), 0);	
		if(sendTy  < 0)
			{
			perror("1 Envoirapport");
			return -1;
			}else{
						int sendTailleMsg = send(descBrCli, &tailleMsg, sizeof(int), 0);
						if(sendTailleMsg  < 0)
						{
						perror("2 Envoi rapport");
						return -1;
						}else{
								int sendChaine = send(descBrCli, chaine, sizeof(chaine), 0); 
								if(sendChaine  < 0)
								{
									perror(" 3 Envoi rapport");
									return -1;
									}else{

											cout<<" **************** "<<endl;
											cout<<" Envoi envoyé "<<endl;
											cout<<" **************** "<<endl;
										

 											//Recupere rapport
 											int typeRecept = 10;
  										cout<<"Demande rapport : "<<typeR<<endl;
  
  										cout<<recv(descBrCli, &typeRecept, sizeof(int), 0)<<endl;
  										cout<<"Type recut :"<<typeR<<endl;
  										cout<<recv(descBrCli, &tailleMsg, sizeof(int), 0)<<endl;
  										cout<<"Taille : "<<tailleMsg<<endl;
  
  
  										ofstream flux("teste.pdf");
  										char car;
  
  										while(tailleMsg >= 0)
											{
    
    									recv(descBrCli, &car, sizeof(char), 0);
    									flux<<car;
    									tailleMsg++;
  										}

										return 1;

								}
						}
					}

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
							 
							 cout<<"Connection non accorder "<<endl;
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
										int reponseRedac = Redac(descBrCli);
										if(reponseRedac != 1)
										{	
											 perror(" Demande de redaction ");
									 		 exit(1);
										}else
											{
												cout<<" ecriture du raport terminer ! "<<endl;
												while(1)
												
												{
												cout<<" **************************************** "<<endl;
												cout<<" Quoi faire taper le numero correspondant "<<endl;
												cout<<" **************************************** "<<endl;
												cout<<" 9 : Demande de redaction "<<endl;
												cout<<" 2 : Demande de  deconnection "<<endl;
												cout<<" 10 : Sauvegarde rapport "<<endl;
												cout<<" 11 : Envoie rapport "<<endl;
												scanf("%i", &faire);
												if(faire == 2)
												{
												Deconnection();
												}
			
												if(faire == 9)
												{
												Redac(descBrCli);
												}
											 
 												if(faire == 10)
												{
												int RepSauvRapport = SauvRapport(descBrCli);

												}
											
 												if(faire == 11 and RepSauvRapport == 1 )
												{
												 EnvoiRapport(descBrCli);
												}else
														 {
															cout<<"effectuer une sauvegarde avant"<<endl;
														 }
									}
}
}
									
										
								}
		}

								




  
  
  
  return 0;
}

  
