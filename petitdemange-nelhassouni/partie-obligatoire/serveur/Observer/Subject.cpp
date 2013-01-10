/*
 * Subject.cpp
 *
 *  Created on: 8 déc. 2012
 *      Author: franck
 */

#include "Subject.h"
#include <cstdio>

Subject::Subject(){};

void Subject::Attach(Observer* o){
  _observers.push_back(o);
}

void Subject::Detach(Observer* o){
 
   for(int i=0; i < _observers.size(); i++){
     if (_observers[i] == o){
       std::vector<Observer*>::iterator it=_observers.begin()+i;
     _observers.erase(it);
     }
  }
}


void Subject::Notify(){

  for(int i=0; i < _observers.size(); i++){
    _observers[i]->Update(this);
  }


}

Subject::~Subject() {
}



