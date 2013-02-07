/*
 * Blaster.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef BLASTER_H_
#define BLASTER_H_

#include "Weapon.h"

class Blaster: public Weapon {
	bool KeyDown; long Charge;
public:
	Blaster();
	virtual ~Blaster();

	void Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* BLASTER_H_ */
