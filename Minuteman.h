/*
 * Minuteman.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef MINUTEMAN_H_
#define MINUTEMAN_H_

#include "Weapon.h"

class Minuteman: public Weapon {
public:
	Minuteman();
	virtual ~Minuteman();

	void Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* MINUTEMAN_H_ */
