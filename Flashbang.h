/*
 * Flashbang.h
 *
 *  Created on: 8 feb 2013
 *      Author: mattias
 */

#ifndef FLASHBANG_H_
#define FLASHBANG_H_

#include "Weapon.h"

class Flashbang: public Weapon {
public:
	Flashbang();
	virtual ~Flashbang();

	void Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* FLASHBANG_H_ */
