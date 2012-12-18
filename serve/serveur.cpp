#include <iostream>
#include <errno.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>
#include <pthread.h>

#include "Sock/sock.h"
#include "Sock/sockdist.h"
#include "Observer/Subject.h"
#include "Observer/Observer.h"
#include "Message.h"
#include "Employe.h"
#include "SubjectClient.h"


#include <stdlib.h>

char controleur[20] = "controleur";
char employe[20] = "employe";

bool recherche(char *chaine){
  return true;
}

using namespace std;


/**
 * Protocole d'autorisation connexion
 * int p : descripteur de la BR du circuit virtuel
 * retourne : -1 -> echec authentification
 * 			   0 -> controleur reconnu
 * 			   1 -> employe reconnu
 */
int AutorisationConnexion(int p){

	int compt = 0;

	int retour = -1;

	//3 tentatives d'authentification
	while (compt < 4){

		Message MsgR(p);

		//si paquet identification, traitement
		if (MsgR.type == 1){
			//verifie si controleur
			if (strcmp(MsgR.chaine,controleur) == 0) {
				retour = 6;
				send(p,&retour,sizeof(int),0);
				return 0;
			}
			//verifie si employe
			if (strcmp(MsgR.chaine,employe) == 0) {
				retour = 6;
				send(p,&retour,sizeof(int),0);
				return 1;
			}
		}

		//Envoie message d'echec
		retour = 5;
		send(p,&retour,sizeof(int),0);
		compt++;
	}


	//retourne -1 si client non identifier
	return -1;
}



void *thread_client(void *p){

	int auth = AutorisationConnexion((int)p);
	cout<<"retour authentification : "<<auth<<endl;
	if (auth == 1){
		SubjectClient client((int)p);
		Employe Traitement(&client);
		client.run();
	}else{
	cout<<"Fermeture connexion : identification incorrect"<<endl;
	close((int)p);
	}


}






int main(){

  int PORT;
  
  printf("n° BR : ");
  scanf("%i",&PORT);
  

  cout<<"\n"<<endl;
  cout<<"Serveur en route"<<endl;
  cout<<"================\n"<<endl;
  
  
  //Creation BR publique
  Sock brPub(SOCK_STREAM,(short)PORT,0);
  int descBrPub;
  if(brPub.good()){
    descBrPub=brPub.getsDesc();
    cout<<"Creation BR publique : Ok"<<endl;
  }else{
    perror("Creation BR publique");
    exit(1);
  }
  
  
  if (listen(descBrPub,1) < 0){
    perror("Creation liste attente");
    exit(1);
  }else{
    cout<<"Creation liste attente : Ok"<<endl;
  }

  struct sockaddr_in brCv;
  socklen_t lgbrCv = sizeof(struct sockaddr_in);
  

  printf("\n\n");
  while(1){
    cout<<"Attend demande connexion"<<endl;
    int descBrCv = accept(descBrPub,(struct sockaddr*)&brCv,&lgbrCv);
    if (descBrCv < 0){
      perror("Traitement demande connexion");
      exit(1);
    }else{
      cout<<"Traitement demande connexion : Ok"<<endl;
    }
    
    //Creation thread-client
    pthread_t t1;
    pthread_create(&t1,NULL,thread_client,(void*)descBrCv);
  }
  
  return 0;
}
