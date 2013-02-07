/*
 * SolidLine.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "SolidLine.h"
#include "Screen.h"

SolidLine::SolidLine() {
	// TODO Auto-generated constructor stub

}

SolidLine::~SolidLine() {
	// TODO Auto-generated destructor stub
}

void SolidLine::Init(double X1, double Y1, double X2, double Y2, double width,
		double duration) {
	x1 = X1;
	y1 = Y1;
	x2 = X2;
	y2 = Y2;
	MaxDuration = Duration = duration;
	Width = width;
}

void SolidLine::TimeTab() {

	Duration --;
	if (Duration <= 0){
		frmScreen.RemoveObject(this);
	}
}

void SolidLine::Render() {
	double c  =  Duration / MaxDuration;
	frmScreen.DrawPlLine(x1, y1, x2, y2, Width * Duration / MaxDuration, Color(c, c , c ,c));
}


