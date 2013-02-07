/*
 * FloppyDisk.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef FLOPPYDISK_H_
#define FLOPPYDISK_H_

#include "Weapon.h"

class FloppyDisk: public Weapon {
public:
	FloppyDisk();
	virtual ~FloppyDisk();

	void Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire);
};

#endif /* FLOPPYDISK_H_ */
