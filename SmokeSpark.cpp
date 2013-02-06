/*
 * SmokeSpark.cpp
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#include "SmokeSpark.h"
#include "aux.h"

SmokeSpark::SmokeSpark() {
	// TODO Auto-generated constructor stub

}

SmokeSpark::~SmokeSpark() {
	// TODO Auto-generated destructor stub
}



void SmokeSpark::Init(double X, double Y, double Xs, double Ys, int Smoke){
	XPos = X;
	YPos = Y;
	XSpeed = Xs;
	YSpeed = Ys;
	SmokeType = Smoke;
}

void SmokeSpark::TimeTab(){
	YSpeed = YSpeed + 0.3;
	XPos = XPos + XSpeed;
	YPos = YPos + YSpeed;
	if (FrmScreen.GetMapLine((XPos), (YPos), XSpeed, YSpeed) != 0) {
		FrmScreen.RemoveObject(this);
		long i;
		for(i = 0; i <= 5; ++i){
			XPos = XPos - XSpeed / 6;
			YPos = YPos - YSpeed / 6;
			if (FrmScreen.GetMap(XPos, YPos) == mAir) { break;}
		}
		FrmScreen.Explosion(XPos, YPos, 0, 2, 1);
		return;
	}
	if (FrmScreen.isPlayer((XPos), (YPos))!= 0) {
		FrmScreen.RemoveObject(this);
		FrmScreen.Explosion((XPos), (YPos), 1, 4, 1);
	}
	FrmScreen.MakeSmoke(XPos, YPos, 0, 0, SmokeType);
}
