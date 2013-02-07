/*
 * Meteor.h
 *
 *  Created on: 23 jan 2013
 *      Author: mattias
 */

#ifndef METEOR_H_
#define METEOR_H_
#include "Solid.h"


class Meteor: public Solid {
private:
public:
	Meteor();

	void Init(double X, double Y, double Xs, double Ys);
	void TimeTab();
	void Render();

	virtual ~Meteor();
	double XPos,  YPos,  XSpeed,  YSpeed;
};

#endif /* METEOR_H_ */
