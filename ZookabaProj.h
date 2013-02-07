/*
 * Zookaba.h
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#ifndef ZOOKABAPROJ_H_
#define ZOOKABAPROJ_H_

#include "Solid.h"

class ZookabaProj: public Solid {
	double XPos; double YPos; double XSpeed; double YSpeed;
public:
	ZookabaProj();
	virtual ~ZookabaProj();

	void Init(double X, double Y, double Xs, double Ys);
	void TimeTab();
	void Render();
};

#endif /* ZOOKABAPROJ_H_ */
