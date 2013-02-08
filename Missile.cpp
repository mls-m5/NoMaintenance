/*
 * Missile.cpp
 *
 *  Created on: 6 feb 2013
 *      Author: mattias
 */

#include "Missile.h"
#include "common.h"
#include "Screen.h"

Missile::Missile() {
	// TODO Auto-generated constructor stub

}

Missile::~Missile() {
	// TODO Auto-generated destructor stub
}



void Missile::Init(double X, double Y, double Xs, double Ys, Player* Target) {
	XPos = X;
	YPos = Y;
	XSpeed = Xs;
	YSpeed = Ys;
	mTarget = Target;
	TimeLimit = 60 + Rnd() * 15;
}

void Missile::TimeTab(){
	long TotalSpeed;
	double ToTargetX, ToTargetY;
	XPos = XPos + XSpeed;
	YPos = YPos + YSpeed;
	ToTargetX = mTarget->XPos - XPos;
	ToTargetY = mTarget->YPos - YPos;
	if (ToTargetX > 0) {
		if (ToTargetY > 0) { TotalSpeed = ToTargetX + ToTargetY; }else{ TotalSpeed = ToTargetX - ToTargetY;}
	}else{
		if (ToTargetY > 0) { TotalSpeed = -ToTargetX + ToTargetY; }else{ TotalSpeed = -ToTargetX - ToTargetY;}
	}
	if (TotalSpeed) { XSpeed = XSpeed + ToTargetX / TotalSpeed * 2;}
	if (TotalSpeed) { YSpeed = YSpeed + ToTargetY / TotalSpeed * 2;}
	if (XSpeed > 0) {
		if (YSpeed > 0) {
			TotalSpeed = XSpeed + YSpeed;
		}else{
			TotalSpeed = XSpeed - YSpeed;
		}
	}else{
		if (YSpeed > 0) {
			TotalSpeed = -XSpeed + YSpeed;
		}else{
			TotalSpeed = -XSpeed - YSpeed;
		}
	}
	if (TotalSpeed) {
		XSpeed = XSpeed / TotalSpeed * 9;
		YSpeed = YSpeed / TotalSpeed * 9;
	}
	long i;
	;
	if (FrmScreen.GetMapLine((XPos), (YPos), XSpeed, YSpeed)) {
		FrmScreen.RemoveObject(this);
		FrmScreen.Explosion((XPos), (YPos), 1, 10, 5);
		PlaySound(dsExplosion);
	}
	if (FrmScreen.isPlayer((XPos), (YPos))) {
		FrmScreen.RemoveObject(this);
		FrmScreen.Explosion((XPos), (YPos), 1, 10, 5);
		PlaySound(dsExplosion);
	}
	TimeLimit = TimeLimit - 1;
	if (TimeLimit < 0) {
		FrmScreen.RemoveObject(this);
		for(i = 0; i <= 30; ++i){
			FrmScreen.Explosion((XPos) + Rnd() * 50 - 25, (YPos) + Rnd() * 50 - 25, 1, 10, 5);
		}
		PlaySound(dsExplosion);
	}
}

void Missile::Render(){
	FrmScreen.DrawPlPic(ddMissile, XPos - 3, YPos - 3, 0);
	FrmScreen.DrawPlPic(ddMissile, XPos - 3 - XSpeed / 2, YPos - 3 - YSpeed / 2, 1);
	FrmScreen.DrawPlPic(ddMissile, XPos - 3 - XSpeed, YPos - 3 - YSpeed, 1);
	FrmScreen.DrawPlPic(ddMissile, XPos - 3 - XSpeed * 1.6, YPos - 3 - YSpeed * 1.5, 1);
	FrmScreen.MakeSmoke(XPos - XSpeed, YPos - YSpeed, -XSpeed / 2 + Rnd() * 2 - 1, -YSpeed / 2 + Rnd() * 2 - 1);
}

