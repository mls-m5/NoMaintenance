/*
 * Plasma.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef PLASMA_H_
#define PLASMA_H_

#include "Solid.h"

class Plasma: public Solid {
	float XSpeed; float YSpeed; long XPos; long YPos;

public:
	Plasma();
	virtual ~Plasma();
	void Init(double X, double Y, double Xs, double Ys);
	void TimeTab();
	void Render();
};

#endif /* PLASMA_H_ */
