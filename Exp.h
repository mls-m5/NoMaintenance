/*
 * Exp.h
 *
 *  Created on: 29 jan 2013
 *      Author: mattias
 */

#ifndef EXP_H_
#define EXP_H_

#include "Solid.h"

class Exp: public Solid {
	double XPos, YPos;
	int Size;
	int i;
public:
	Exp();
	virtual ~Exp();

	void Init(double X, double Y, long nSize);
	void TimeTab();
	void Render();
};


#endif /* EXP_H_ */
