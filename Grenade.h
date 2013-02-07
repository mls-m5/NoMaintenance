/*
 * Grenade.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef GRENADE_H_
#define GRENADE_H_

#include "Solid.h"

class Grenade: public Solid {
	double XPos; double YPos; double XSpeed; double YSpeed; long HLeft;
	long NextSmoke;
public:
	Grenade();
	virtual ~Grenade();


	void Init(double X, double Y, double Xs, double Ys);
	void TimeTab();
	void Render();
};

#endif /* GRENADE_H_ */
