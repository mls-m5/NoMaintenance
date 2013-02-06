/*
 * MiniShot.h
 *
 *  Created on: 6 feb 2013
 *      Author: mattias
 */

#ifndef MINISHOT_H_
#define MINISHOT_H_

#include "Solid.h"

class MiniShot: public Solid {
	double XPos; double YPos; double XSpeed; double YSpeed;
public:
	virtual ~MiniShot();

	void Init(double X, double Y, double Xs, double Ys);
	void TimeTab();
	void Render();
};

#endif /* MINISHOT_H_ */
