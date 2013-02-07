/*
 * Klachnikow.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef KLACHNIKOW_H_
#define KLACHNIKOW_H_

#include "Weapon.h"

class Klachnikow: public Weapon {
	double Delay;
public:
	Klachnikow();
	virtual ~Klachnikow();
	void Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* KLACHNIKOW_H_ */
