/*
 * GaussGun.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef GAUSSGUN_H_
#define GAUSSGUN_H_

#include "Weapon.h"

class GaussGun: public Weapon {
	long NextShot;
public:
	GaussGun();
	virtual ~GaussGun();
	void Fire(double X, double  Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* GAUSSGUN_H_ */
