/*
 * client.cpp
 *
 *  Created on: 26 déc. 2012
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
  int retour;



  printf("n° identifiant : ");
  scanf("%s", chaine);
  tailleMsg = sizeof(chaine);
  typeR = 1;


/***** Envoi de l'indentification ***/

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

					cout<<" **************************** "<<endl;
					cout<<" demande de Sauvegarde envoyé "<<endl;
					cout<<" **************************** "<<endl;
					return 1;
				      }
				}

			  
			}
			return 1;
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
									      cout<<recv(descBrCli, &typeR, sizeof(int), 0)<<endl;
									      cout<<"Type recut :"<<typeR<<endl;
									      cout<<recv(descBrCli, &tailleMsg, sizeof(int), 0)<<endl;
									      cout<<"Taille : "<<tailleMsg<<endl;
									      
									     // printf("Nom de fichier : ");
									     // scanf("%s", chaine);
									      ofstream flux("tol.pdf");
									      char car;
									      
									      while(tailleMsg > 0){
										cout<<"attend reception"<<endl;
										if (recv(descBrCli, &car, sizeof(char), 0) != 0) perror("rcv");
										flux<<car;
										tailleMsg--;
										cout<<tailleMsg<<endl;
									      }
									      
									      flux.close();
									      //close(descBrCli);
									      cout<<"fichier recu "<<endl;
									      void ouvrirDocument()

								

									      return 1;

								}
						}
					}

}


void LirefichierPdf()
{
// le constructeur de ifstream permet d'ouvrir un fichier en lecture
std::ifstream fichier( "tol.pdf" );

if ( fichier ) // ce test échoue si le fichier n'est pas ouvert
{
std::string ligne; // variable contenant chaque ligne lue

// cette boucle s'arrête dès qu'une erreur de lecture survient
while ( std::getline( fichier, ligne ) )
{
// afficher la ligne à l'écran
std::cout << ligne << std::endl;
}
}
system("pause");
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
				cout<<" 7 demande de  deconnection "<<endl;
				scanf("%i", &faire);
									
				if(faire == 7)
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
						  int RepSauvRapport = 0;
						  cout<<" **************************************** "<<endl;
						  cout<<" Quoi faire taper le numero correspondant "<<endl;
						  cout<<" **************************************** "<<endl;
						  cout<<" 9 : Demande de redaction "<<endl;
						  cout<<" 7 : Demande de  deconnection "<<endl;
						  cout<<" 10 : Sauvegarde rapport "<<endl;
						  cout<<" 11 : Envoie rapport "<<endl;
						  scanf("%i", &faire);
						
						  if(faire == 7)
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
											
						  if(faire == 11)
						  {
						    
						  int RepEnvoiRap = EnvoiRapport(descBrCli);
						  if(RepEnvoiRap == 1)
						  {
						    cout<<"fihier bien recu"<<endl;}
						  }
						  if(faire == 12)
						  {
						   LirefichierPdf();
						  
						  }
						}
}
}
									
										
				}
		}

								




  
  
  
  return 0;
}

  
