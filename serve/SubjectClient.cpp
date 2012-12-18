/*
 * SubjectClient.cpp
 *
 *  Created on: 8 déc. 2012
 *      Author: franck
 */

#include "SubjectClient.h"

#include <iostream>
#include <string>
#include <cstdio>

SubjectClient::SubjectClient() {
	descBr = 0;
}

SubjectClient::SubjectClient(int pDescBr){
	descBr = pDescBr;
}

void SubjectClient::run(){
	//Se met en lecture sur la boite de reception//
	while(true){
		printf("Thread client en attente de reception :\n");
		msgR = Message(descBr);

	    //averti observeur de la reception du msg
	    Notify();
	}
}

Message SubjectClient::getMessage(){
	return msgR;
}

SubjectClient::~SubjectClient() {
	// TODO Auto-generated destructor stub
}

