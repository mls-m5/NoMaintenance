/*
 * Fire.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "Fire.h"
#include "common.h"

Fire::Fire() {
	// TODO Auto-generated constructor stub

}

Fire::~Fire() {
	// TODO Auto-generated destructor stub
}



void Fire::Init(double X, double Y, double Xs, double Ys){
	CurrentRotate = 15;
	XPos = X;
	YPos = Y;
	XSpeed = Xs;
	YSpeed = Ys;
}

void Fire::TimeTab(){
	long i;
	CurrentRotate = CurrentRotate - 1;
	if (CurrentRotate < 0) {
		FrmScreen.RemoveObject(this);
	}
	XSpeed = XSpeed / 1.1;
	YSpeed = (YSpeed - 0.1) / 1.1;
	XPos = XPos + XSpeed;
	YPos = YPos + YSpeed;
	i = FrmScreen.isPlayer(XPos, YPos, 15 - CurrentRotate, 15 - CurrentRotate);
	if (FrmScreen.GetMap((XPos), (YPos)) != 0) {
		FrmScreen.RemoveObject(this);
		FrmScreen.Explosion(XPos, YPos, 1, 0, 0);
	}
	if (i != 0) {
		FrmScreen.RemoveObject(this);
		FrmScreen.HitPlayer((int) (i - 1), 10);
		FrmScreen.Explosion(XPos, YPos, 1, 0, 0);
	}
}
void Fire::Render(){
	FrmScreen.DrawPlPic(ddSmoke, XPos - 7, YPos - 7, 18 + CurrentRotate / 3);
}
