/*
 * HExp.cpp
 *
 *  Created on: 5 feb 2013
 *      Author: mattias
 */

#include "HExp.h"
#include "aux.h"

HExp::HExp() {
	// TODO Auto-generated constructor stub

}

HExp::~HExp() {
	// TODO Auto-generated destructor stub
}

void HExp::Init(double X, double Y) {
	XPos = X;
	YPos = Y;
	i = 0;
	Size = 5;
}

void HExp::TimeTab() {
	if (i >= Size) {
		FrmScreen.RemoveObject(this);
	}
	i = i + 1;
}

void HExp::Render() {
	FrmScreen.DrawPlPic(ddhExp, XPos - 30, YPos - 30, i);
}


