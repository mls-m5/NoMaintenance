/*
 * FireBomb.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef FIREBOMB_H_
#define FIREBOMB_H_
#include "Solid.h"

class FireBomb: public Solid {
	double XPos; double YPos; double XSpeed; double YSpeed;
	long Action; long Power;
public:
	FireBomb();
	virtual ~FireBomb();


	void Init(double X, double Y, double Xs, double Ys, long Ammo);
	void TimeTab();
	void Render();
};

#endif /* FIREBOMB_H_ */
