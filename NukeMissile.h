/*
 * NukeMissile.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef NUKEMISSILE_H_
#define NUKEMISSILE_H_

#include "Solid.h"

class NukeMissile: public Solid {
	double XPos; double YPos; long YSpeed;
public:
	NukeMissile();
	virtual ~NukeMissile();

	void Init(double X);
	void TimeTab();
	void Render();
};

#endif /* NUKEMISSILE_H_ */
