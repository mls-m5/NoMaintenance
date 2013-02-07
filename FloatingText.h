/*
 * FloatingText.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef FLOATINGTEXT_H_
#define FLOATINGTEXT_H_

#include "Solid.h"
#include <string>

class FloatingText: public Solid {
	double XPos, YPos, XSpeed, YSpeed, Friction;
	int PlayerNum; int left;
	std::string text;
public:
	FloatingText();
	virtual ~FloatingText();

	void Init(double X, double Y, double Xs, double Ys, std::string text, int duration = 10, int playerNum = -1, double friction = 0);
	void TimeTab();
	void Render();
};

#endif /* FLOATINGTEXT_H_ */
