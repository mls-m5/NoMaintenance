/*
 * Zookaba.h
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#ifndef ZOOKABA_H_
#define ZOOKABA_H_

#include "Solid.h"

class Zookaba: public Solid {
	double XPos; double YPos; double XSpeed; double YSpeed;
public:
	Zookaba();
	virtual ~Zookaba();

	void Init(double X, double Y, double Xs, double Ys);
	void TimeTab();
	void Render();
};

#endif /* ZOOKABA_H_ */
