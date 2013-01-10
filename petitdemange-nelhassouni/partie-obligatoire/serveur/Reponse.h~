/*
 * ReponseEmploye.h
 *
 *  Created on: 8 déc. 2012
 *      Author: franck
 */

#ifndef REPONSEEMPLOYE_H_
#define REPONSEEMPLOYE_H_

#include "../Observer/Observer.h"
#include "SubjectClient.h"

class Reponse : public Observer {
protected :
	SubjectClient* _subjet;
public:
	Reponse();
	Reponse(SubjectClient* cli);
	virtual void Update(Subject *o);
	virtual void TraitementMsg();
	virtual ~Reponse();
};

#endif /* REPONSEEMPLOYE_H_ */
