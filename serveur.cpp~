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



using namespace std;

void *thread_client(void *p){
   
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
    pthread_create(&t1,NULL,thread_client,NULL);
  }
  
  return 0;
}
