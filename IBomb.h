/*
 * IBomb.h
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#ifndef IBOMB_H_
#define IBOMB_H_

#include "Solid.h"

class IBomb: public Solid {
public:
	IBomb();
	virtual ~IBomb();


	double XPos; double YPos; long TimeLimit;
	void Init(double X, double Y, long Limit);
	void TimeTab();
};

#endif /* IBOMB_H_ */
