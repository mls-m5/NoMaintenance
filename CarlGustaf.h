/*
 * CarlGustaf.h
 *
 *  Created on: 6 feb 2013
 *      Author: mattias
 */

#ifndef CARLGUSTAF_H_
#define CARLGUSTAF_H_

#include "Weapon.h"

class CarlGustaf: public Weapon {
public:
	CarlGustaf();
	virtual ~CarlGustaf();

	virtual void Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* CARLGUSTAF_H_ */
