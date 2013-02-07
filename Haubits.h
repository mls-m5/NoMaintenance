/*
 * Haubits.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef HAUBITS_H_
#define HAUBITS_H_

#include "Weapon.h"

class Haubits: public Weapon {
public:
	Haubits();
	virtual ~Haubits();
	void Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* HAUBITS_H_ */
