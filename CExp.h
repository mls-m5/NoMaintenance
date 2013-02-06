/*
 * CExp.h
 *
 *  Created on: 6 feb 2013
 *      Author: mattias
 */

#ifndef CEXP_H_
#define CEXP_H_

#include "Solid.h"

class CExp: public Solid {
	double XPos, YPos;
	double mSize;
public:
	CExp();
	virtual ~CExp();
	void Init(double X, double Y, double Size);
	void TimeTab();
	void Render();
};

#endif /* CEXP_H_ */
