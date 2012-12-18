/*
 * SubjectClient.h
 *
 *  Created on: 8 déc. 2012
 *      Author: franck
 */

#ifndef SUBJECTCLIENT_H_
#define SUBJECTCLIENT_H_

#include "Observer/Subject.h"
#include "Message.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

class SubjectClient : public Subject{
private :
	int descBr;
	Message msgR;

public:
	SubjectClient();
	SubjectClient(int pDescBr);
	virtual Message getMessage();
	virtual void run();
	virtual ~SubjectClient();

};

#endif /* SUBJECTCLIENT_H_ */
