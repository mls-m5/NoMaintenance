/*
 * GasEel.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef GASEEL_H_
#define GASEEL_H_

#include "Weapon.h"

class GasEel: public Weapon {
	bool KeyDown; long Delay; double Ammo;
public:
	GasEel();
	virtual ~GasEel();
	void Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* GASEEL_H_ */
