/*
 * M7ton.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef M7TON_H_
#define M7TON_H_

#include "Weapon.h"

class M7ton: public Weapon {
public:
	M7ton();
	virtual ~M7ton();
	void Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* M7TON_H_ */
