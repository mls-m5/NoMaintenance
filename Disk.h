/*
 * Disk.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef DISK_H_
#define DISK_H_

#include "Solid.h"

class Disk: public Solid {
	double XPos; double YPos; double XSpeed; double YSpeed; long HLeft;
public:
	Disk();
	virtual ~Disk();

	void Init(double X, double Y, double Xs, double Ys);
	void TimeTab();
	void Render();
};

#endif /* DISK_H_ */
