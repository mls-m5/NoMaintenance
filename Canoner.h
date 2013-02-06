/*
 * Canoner.h
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#ifndef CANONER_H_
#define CANONER_H_

#include "Weapon.h"

class Canoner: public Weapon {
public:
	virtual ~Canoner();
	virtual void Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* CANONER_H_ */
