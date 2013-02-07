/*
 * M6ton.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef M6TON_H_
#define M6TON_H_

#include "Weapon.h"

class M6ton: public Weapon {
public:
	M6ton();
	virtual ~M6ton();

	void Fire(double X, double  Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* M6TON_H_ */
