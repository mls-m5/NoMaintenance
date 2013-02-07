/*
 * SolidLine.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef SOLIDLINE_H_
#define SOLIDLINE_H_

#include "Solid.h"

class SolidLine: public Solid {
	double x1, y1, x2, y2;
	double Width, Duration, MaxDuration;
public:
	SolidLine();
	virtual ~SolidLine();

	void Init(double X1, double Y1, double X2, double Y2, double width, double duration);
	void TimeTab();
	void Render();
};

#endif /* SOLIDLINE_H_ */
