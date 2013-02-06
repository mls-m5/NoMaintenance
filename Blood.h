/*
 * Blood.h
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#ifndef BLOOD_H_
#define BLOOD_H_

#include "Solid.h"

class Blood: public Solid {
public:
	double xpos, ypos;
	long timeLimit;

	Blood();
	virtual ~Blood();


	void Init(double x, double y, long limit);
	void TimeTab();
	void Render(){}
};

#endif /* BLOOD_H_ */
