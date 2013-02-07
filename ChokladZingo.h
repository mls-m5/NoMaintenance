/*
 * ChokladZingo.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef CHOKLADZINGO_H_
#define CHOKLADZINGO_H_

#include "Weapon.h"

class ChokladZingo: public Weapon {
public:
	ChokladZingo();
	virtual ~ChokladZingo();
	void Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* CHOKLADZINGO_H_ */
