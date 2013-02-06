/*
 * Bomb.h
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#ifndef BOMB_H_
#define BOMB_H_

#include "Solid.h"

class Bomb: public Solid {
public:
	double XPos; double YPos; float XSpeed; float YSpeed;

	Bomb();
	virtual ~Bomb();
	void Init(double X, double Y, double Xs, double Ys);
	void TimeTab();
	void Render();
};

#endif /* BOMB_H_ */
