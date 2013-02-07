/*
 * MiniShot.cpp
 *
 *  Created on: 6 feb 2013
 *      Author: mattias
 */

#include "MiniShot.h"
#include "aux.h"


MiniShot::~MiniShot() {
	// TODO Auto-generated destructor stub
}

void MiniShot::Init(double X, double Y, double Xs, double Ys) {
	XPos = X;
	YPos = Y;
	XSpeed = Xs;
	YSpeed = Ys;
}

void MiniShot::TimeTab() {
	YSpeed = YSpeed + 0.3;
	XPos = XPos + XSpeed;
	YPos = YPos + YSpeed;
	if (FrmScreen.GetMapLine((XPos), (YPos), XSpeed, YSpeed) != 0) {
		FrmScreen.RemoveObject(this);
		long i;
		for(i = 0; i <= 5; ++i){
			XPos = XPos - XSpeed / 6;
			YPos = YPos - YSpeed / 6;
			if (FrmScreen.GetMap(XPos, YPos) == mAir) { break; }
		}
		FrmScreen.Explosion(XPos, YPos, 0, 2, 1);
		return;
	}
	if (FrmScreen.isPlayer((XPos), (YPos)) != 0) {
		FrmScreen.RemoveObject(this);
		FrmScreen.CustomExplosion(XPos, YPos, 5, 10, 10);
	}
}

void MiniShot::Render() {
	FrmScreen.DrawPlLine (XPos, YPos, XPos - XSpeed, YPos - YSpeed, 1, 0xFFFFFF00);
}



