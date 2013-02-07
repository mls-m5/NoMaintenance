/*
 * Jolt.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef JOLT_H_
#define JOLT_H_

#include "Weapon.h"

class Jolt: public Weapon {
	long Delay;
public:
	Jolt();
	virtual ~Jolt();
	void Fire(double X, double  Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* JOLT_H_ */
