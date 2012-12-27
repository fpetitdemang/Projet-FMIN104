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
#include "Controleur.h"


#include <stdlib.h>





verrou mes_verrous;





char controleur[20] = "controleur";



using namespace std;






void *thread_client(void *p){
  
  SubjectClient client((int)p, &mes_verrous);
 
  int auth = client.Connexion();
  
  Controleur TraitementContr = Controleur(&client);
  Employe TraitementEmp = Employe(&client);
  

  switch(auth){
    
  case 0 :     //Employe
    client.Detach(&TraitementContr);
    cout<<"\""<<client.getNom()<<"\" vient de se connecter"<<endl;
    break;
  case 1:  //Controler
    client.Detach(&TraitementEmp);
    cout<<"\""<<client.getNom()<<"\" vient de se connecter"<<endl;
    break;
  default:
    cout<<"Echec identification client"<<endl;
    cout<<"Fermeture Thread de service"<<endl;
    close((int) p);
    pthread_exit(NULL);
    break;
    }
  
    client.run();

    //prévient client de la deconnexion
    int num = 7;
    send((int)p,&num,sizeof(int),0);
    
    close((int) p);
    cout<<"\""<<client.getNom()<<"\" est deconnecté"<<endl;
    pthread_exit(NULL);
}
  




/* 

Fonction main()

*/

int main(){
  
  vector<pthread_t> lThread;
  
  //initialisation des verrous
  pthread_mutex_init(&mes_verrous.VlEmploye, NULL);
  pthread_mutex_init(&mes_verrous.VlPdf, NULL);

  /* mes_verrous.lEmploye.push_back("nordine");
     mes_verrous.lEmploye.push_back("franck");*/



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
    //cout<<"Attend demande connexion"<<endl;
    int descBrCv = accept(descBrPub,(struct sockaddr*)&brCv,&lgbrCv);
    if (descBrCv < 0){
      perror("Traitement demande connexion");
      break;
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
  
  cout<<"Terminaison serveur"<<endl;
  
  return 0;
}
