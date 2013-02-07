/*
 * Blast.h
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#ifndef BLAST_H_
#define BLAST_H_

#include "Solid.h"

class Blast: public Solid {
	double xspeed, yspeed, xpos, ypos;
	long charge;
public:
	Blast();
	virtual ~Blast();
	void Init(double x, double y, double xs, double ys, long charged);
	void TimeTab();
	void Render();
};

#endif /* BLAST_H_ */
