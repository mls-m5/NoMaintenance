/*
 * EldFunkar.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef ELDFUNKAR_H_
#define ELDFUNKAR_H_

#include "Weapon.h"

class EldFunkar: public Weapon {
	int Delay;
public:
	EldFunkar();
	virtual ~EldFunkar();
	void Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* ELDFUNKAR_H_ */
