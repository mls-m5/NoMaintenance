/*
 * HExp.h
 *
 *  Created on: 5 feb 2013
 *      Author: mattias
 */

#ifndef HEXP_H_
#define HEXP_H_

#include "Solid.h"

class HExp: public Solid {
	double XPos; double YPos; int Size; int i;
public:
	HExp();
	virtual ~HExp();

	void Init(double X, double Y);
	void TimeTab();
	void Render();
};

#endif /* HEXP_H_ */
