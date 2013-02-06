/*
 * SmokeSpark.h
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#ifndef SMOKESPARK_H_
#define SMOKESPARK_H_

#include "Solid.h"

class SmokeSpark: public Solid {
public:
	double XPos; double YPos; double XSpeed; double YSpeed;
	int SmokeType;
	SmokeSpark();
	virtual ~SmokeSpark();

	void Init(double X, double Y, double Xs, double Ys, int Smoke);

	void TimeTab();
	void Render(){}
};

#endif /* SMOKESPARK_H_ */
