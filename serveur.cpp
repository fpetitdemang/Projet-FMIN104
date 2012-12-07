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

#include <stdlib.h>


bool recherche(char *chaine){
  return true;
}

using namespace std;


/**struct msg recu**/
struct msg{

  int type;
  int taille;
  char *msg;

};

void traitrement_requete_employe(msg myMsg)
{
 /********************
   *authentification**
   ********************/

  int compt = 0;
  bool authentif = false;

  char nomEmp[20];
  
  while(compt<=4 && authentif == false)
    {
      if (recherche("")){
	authentif == true;
	//recupere nomEmp
      }
      compt++;
    }

  //Echec authentification
  if (authentif == false){
    //envoie msg echec
    //fermer descritpeur
   
    //termine le thread
   

  }

  //Authentification réussi
  //envoie msg authentification reussi
  

  /**********************
   *Redaction rapport***
   *********************/
  
  //attente msg : demande redaction
  //teste si rapport non creer
  /******creer rapport*/
  /* OuvreRapport(nomEmp);
  char *section;

  do{
    


  }while(*/
  
  
}



void *thread_employe(void *p){

  
 int pBr = (int)p;
  do{
   

    msg msgR;


    //Lit type requete reçu
    int reception = recv( pBr, msgR.type, 4, 0);
    if (reception < 0){
      perror("recv");
      close(pBr);
      cout<<"Fermeture connection client"<<endl;
      pthread_exit(NULL);
    }

    if(reception == 0){
      perror("send");
      cout<<"Fermeture connection client"<<endl;
      pthread_exit(NULL);
    }
    
    //Lit taille msg a lire
     int reception = recv(pBr, msgR.taille, 4, 0);
    if (reception < 0){
      perror("recv");
      close(pBr);
      cout<<"Fermeture connection client"<<endl;
      pthread_exit(NULL);
    }

    if(reception == 0){
      perror("send");
      cout<<"Fermeture connection client"<<endl;
      pthread_exit(NULL);
    }

    //Lit msg de la requete
    int comptOctetLu = 0;
    msgR.msg =(char *) malloc(msgR.taille);
    
    int reception = recv(pBr, msgR, , 0);
    if (reception < 0){
      perror("recv");
      close(pBr);
      cout<<"Fermeture connection client"<<endl;
      pthread_exit(NULL);
    }
    
    if(reception == 0){
      perror("send");
      cout<<"Fermeture connection client"<<endl;
      pthread_exit(NULL);
    }

    
    /*
    if(reception > 0) {
      cout<<"rcv : Success"<<endl;
      cout<<msgR<<endl;
    }
    

    int envoie = send(pBr[1], msgR, 256, 0);
    if (envoie < 0){
      close(pBr[0]);
      close(pBr[1]);
      perror("send");
    }
    if (envoie == 0){
      close(pBr[0]);
      close(pBr[1]);
      perror("send");
    }

    if(envoie > 0){
      cout<<"send : Success"<<endl;
      cout<<msgR<<endl;
    }    
    */

  }while(1);
  
   
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
    pthread_create(&t1,NULL,thread_employe,NULL);
  }
  
  return 0;
}
