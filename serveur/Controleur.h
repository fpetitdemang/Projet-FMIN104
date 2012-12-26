#ifndef CONTROLEUR_H_
#define CONTROLEUR_H_

#include "Reponse.h"
#include "fournisSujet1/sauvegarde.h"

class Controleur : public Reponse{
public:
	Controleur();
	Controleur(SubjectClient* cli);
	virtual void TraitementMsg();
	virtual ~Controleur();
};

#endif /*CONTROLEUR_H_ */
