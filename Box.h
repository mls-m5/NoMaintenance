/*
 * Box.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef BOX_H_
#define BOX_H_

#include "Solid.h"
#include <string>

class Box: public Solid {
public:
	double XPos; double YPos; double  XSpeed; double  YSpeed; long TimeLimit;
	int ItemNumber;
	std::string Item;
	long BoxType;
	Box();
	virtual ~Box();


	void Init(double X, double Y, double Xs, double Ys);
	void TimeTab();
	void Render();
};

#endif /* BOX_H_ */
