/*
 * Miligun.h
 *
 *  Created on: 6 feb 2013
 *      Author: mattias
 */

#ifndef MILIGUN_H_
#define MILIGUN_H_

#include "Weapon.h"

class Miligun: public Weapon {
public:
	virtual ~Miligun();
	void Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* MILIGUN_H_ */
