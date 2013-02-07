/*
 * Zookaba.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef ZOOKABA_H_
#define ZOOKABA_H_

#include "Weapon.h"

class Zookaba: public Weapon {
	int Delay;
public:
	Zookaba();
	virtual ~Zookaba();
	void Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* ZOOKABA_H_ */
