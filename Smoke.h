/*
 * Smoke.h
 *
 *  Created on: 29 jan 2013
 *      Author: mattias
 */

#ifndef SMOKE_H_
#define SMOKE_H_

#include "Solid.h"

class Smoke: public Solid {
	double XPos; double YPos; double XSpeed; double YSpeed; int CurrentRotate;
	long mSmokeType;
public:
	Smoke();
	virtual ~Smoke();

	void Init(double X, double Y, double Xs, double Ys, long SmokeType);
	void TimeTab();
	void Render();
};

#endif /* SMOKE_H_ */
