/*
 * Missile.h
 *
 *  Created on: 6 feb 2013
 *      Author: mattias
 */

#ifndef MISSILE_H_
#define MISSILE_H_

#include "Solid.h"
#include "Player.h"

class Missile: public Solid {
	double XPos; double YPos; float XSpeed; float YSpeed; class Player * mTarget; long TimeLimit;
public:
	Missile();
	virtual ~Missile();

	void Init(double X, double Y, double Xs, double Ys, Player *Target);
	void TimeTab();
	void Render();
};

#endif /* MISSILE_H_ */
