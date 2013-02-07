/*
 * EldFunkarProj.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef ELDFUNKARPROJ_H_
#define ELDFUNKARPROJ_H_

#include "Solid.h"

class EldFunkarProj: public Solid {
	double XPos; double YPos; double XSpeed; double YSpeed;
public:
	EldFunkarProj();
	virtual ~EldFunkarProj();

	void Init(double X, double Y, double Xs, double Ys);
	void TimeTab();
	void Render();
};

#endif /* ELDFUNKARPROJ_H_ */
