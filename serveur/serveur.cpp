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

#include "../Sock/sock.h"
#include "../Sock/sockdist.h"
#include "Observer/Subject.h"

#include "Employe.h"


#include <stdlib.h>


char employe[20] = "employe";


vector<string> lEmploye;
vector<string> lPdf;
verrou mes_verrous;



/*pthread_mutex_t VlEmploye = PTHREAD_MUTEX_INITIALIZER;//creation+initialisation verrou pour acces I/O sur la liste des employés
  pthread_mutex_t VlPdf = PTHREAD_MUTEX_INITIALIZER;//creation+initialisation verrou pour acces I/O sur la liste des pdf créer*/

char controleur[20] = "controleur";


bool recherche(char *chaine){
  return true;
}

using namespace std;






void *thread_client(void *p){
 
  SubjectClient client((int)p, &mes_verrous);
  Employe Traitement(&client);
  client.Connexion(lEmploye);
  cout<<client.getNom()<<" vient de se connecter"<<endl;
  
  /*switch(client.Connexion(lEmploye)){
    
 case 1 :     //Lance traitement msg Employe
   Traitement = Employe(&client);
     break;
  case 2:  //Lance traitement msg Controler
    break;
  default:
    cout<<"Echec identification client"<<endl;
    cout<<"Fermeture Thread de service"<<endl;
    close((int) p);
    pthread_exit(NULL);
    break;
    }*/
  
    client.run();
    close((int) p);
    cout<<client.getNom()<<" est deconnecté"<<endl;
    pthread_exit(NULL);
}
  




/* 

Fonction main()

*/

int main(){
  
  lEmploye.push_back("nordine");
  lEmploye.push_back("franck");
  vector<pthread_t> lThread;
  
  //initialisation des verrous
  pthread_mutex_init(&mes_verrous.VlEmploye, NULL);
  pthread_mutex_init(&mes_verrous.VlPdf, NULL);



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
    
    //Creation thread service
    pthread_t t1;
    if (pthread_create(&t1,NULL,thread_client,(void*)descBrCv) != 0){
      cout<<"Erreur création thread service"<<endl;
      close(descBrCv);
    }else{
      lThread.push_back(t1);
    }
  }
  
  //Attd fin execution thread pour terminer le programme
  for(int i=0; i<lThread.size(); i++){
    pthread_join(lThread[i],NULL);
  }
  
  return 0;
}
