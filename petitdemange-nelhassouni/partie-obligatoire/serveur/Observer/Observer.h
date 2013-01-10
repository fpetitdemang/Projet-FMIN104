/*
 * Observer.h
 *
 *  Created on: 8 déc. 2012
 *      Author: franck
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include "Subject.h"

class Subject;

class Observer {
public:
	Observer();
	virtual void Update(Subject* theChangedSubject)=0;
	virtual ~Observer();
};

#endif /* OBSERVER_H_ */
