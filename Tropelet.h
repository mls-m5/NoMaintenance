/*
 * Tropelet.h
 *
 *  Created on: 6 feb 2013
 *      Author: mattias
 */

#ifndef TROPELET_H_
#define TROPELET_H_

#include "Weapon.h"

class Tropelet: public Weapon {
public:
	Tropelet();
	virtual ~Tropelet();

	void Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire);
	void MakeWarp(long Player);
};

#endif /* TROPELET_H_ */
