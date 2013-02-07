/*
 * Fire.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef FIRE_H_
#define FIRE_H_

#include "Solid.h"

class Fire: public Solid {
	double XPos; double YPos; double XSpeed; double YSpeed; int CurrentRotate;
public:
	Fire();
	virtual ~Fire();
	void Init(double X, double Y, double Xs, double Ys);
	void TimeTab();
	void Render();
};

#endif /* FIRE_H_ */
