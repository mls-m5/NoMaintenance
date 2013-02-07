/*
 * Nurb.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef NURB_H_
#define NURB_H_

#include "Weapon.h"

class Nurb: public Weapon {
public:
	Nurb();
	virtual ~Nurb();

	void Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* NURB_H_ */
