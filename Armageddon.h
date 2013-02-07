/*
 * Armageddon.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef ARMAGEDDON_H_
#define ARMAGEDDON_H_

#include "Weapon.h"

class Armageddon: public Weapon {
	long NextAttack;
public:
	Armageddon();
	virtual ~Armageddon();
	void Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* ARMAGEDDON_H_ */
