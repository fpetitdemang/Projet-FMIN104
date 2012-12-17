/*
 * Employe.h
 *
 *  Created on: 11 déc. 2012
 *      Author: franck
 */

#ifndef EMPLOYE_H_
#define EMPLOYE_H_

#include "Reponse.h"
#include "fournisSujet1/sauvegarde.h"

class Employe : public Reponse{
public:
	Employe();
	Employe(SubjectClient* cli);
	virtual void Traitement();
	virtual ~Employe();
};

#endif /* EMPLOYE_H_ */
