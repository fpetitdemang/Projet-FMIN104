/*
 * Subject.h
 *
 *  Created on: 8 déc. 2012
 *      Author: franck
 */

#ifndef SUBJECT_H_
#define SUBJECT_H_

class Observer;

#include "Observer.h"
#include <vector>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <strings.h>
#include <string.h>

using namespace std;

class Subject {
private:
	vector<Observer*> _observers;
public:
	Subject();

	virtual void Attach(Observer*);
	virtual void Detach(Observer*);
	virtual void Notify();
	virtual ~Subject();
};

#endif /* SUBJECT_H_ */
