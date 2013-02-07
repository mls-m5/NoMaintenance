/*
 * NukeGrenade.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef NUKEGRENADE_H_
#define NUKEGRENADE_H_

#include "Solid.h"

class NukeGrenade: public Solid {
	double XPos; double YPos; double XSpeed; double YSpeed; long HLeft;
	long NextSmoke; long Rotation;

public:
	NukeGrenade();
	virtual ~NukeGrenade();

	void Init(double X, double Y, double Xs, double Ys);
	void TimeTab();
	void Render();
};

#endif /* NUKEGRENADE_H_ */
