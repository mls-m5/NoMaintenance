/*
 * Blood.cpp
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#include "Blood.h"
#include "common.h"

Blood::Blood() {
	// TODO Auto-generated constructor stub

}

Blood::~Blood() {
	// TODO Auto-generated destructor stub
}


void Blood::Init(double x, double y, long limit){

	xpos = x;
	ypos = y;
	timeLimit = limit;

}

void Blood::TimeTab() {
	for (int i = 0; i <= 2 + 3 * GamePlay.Blood / 100; ++i){

		FrmScreen.MakeSmoke( xpos, ypos, Rnd() * 6 - 3, Rnd() * 6 - 3, 2);
	}
	timeLimit = timeLimit - 1;
	if (timeLimit < 0 ){
		FrmScreen.RemoveObject(this);
	}
}
