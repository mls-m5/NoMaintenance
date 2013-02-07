/*
 * SpastOLW.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef SPASTOLW_H_
#define SPASTOLW_H_

#include "Weapon.h"

class SpastOLW: public Weapon {
public:
	SpastOLW();
	virtual ~SpastOLW();

	void Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* SPASTOLW_H_ */
