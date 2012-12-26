/*
 * Subject.cpp
 *
 *  Created on: 8 déc. 2012
 *      Author: franck
 */

#include "Subject.h"
#include <cstdio>

Subject::Subject(){
	printf("Création sujet\n");
};

void Subject::Attach(Observer* o){
	_observers.push_back(o);
}

void Subject::Detach(Observer* o){
  for (int(0); _observers.size(); i++){
    if (_observers[i] == o) _observers.erase(i);
  }
}


void Subject::Notify(){

	for(int i=0; i < _observers.size(); i++){
		_observers[i]->Update(this);

	}


}

Subject::~Subject() {
}



