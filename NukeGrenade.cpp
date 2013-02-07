/*
 * NukeGrenade.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "NukeGrenade.h"
#include "aux.h"
#include "Fire.h"

NukeGrenade::NukeGrenade() {
	// TODO Auto-generated constructor stub

}

NukeGrenade::~NukeGrenade() {
	// TODO Auto-generated destructor stub
}



void NukeGrenade::Init(double X, double Y, double Xs, double Ys){
	XPos = X;
	YPos = Y;
	XSpeed = Xs;
	YSpeed = Ys;
	HLeft = (long) (40 + Rnd() * 10);
	Rotation = 3;
	NextSmoke = 0;
}

void NukeGrenade::TimeTab(){
	YSpeed = YSpeed + 0.2;
	XPos = XPos + XSpeed;
	YPos = YPos + YSpeed;
	HLeft = HLeft - 1;
	NextSmoke = NextSmoke - 1;
	Rotation = Rotation - 1;
	if (Rotation < 0) { Rotation = 9;}
	if (NextSmoke < 0) {
		NextSmoke = 2;
		FrmScreen.MakeSmoke(XPos, YPos, -XSpeed / 2, -YSpeed / 2, 3);
	}
	if (HLeft < 1) {
		long i;
		FrmScreen.RemoveObject(this);
		for(i = 0; i <= 3; ++i){
			FrmScreen.HugeExplosion(XPos + Rnd() * 50 - 25, YPos + Rnd() * 50 - 25, 15, 25);
		}
		for(i = 0; i <= 10; ++i){
			FrmScreen.MakeSmoke(XPos - XSpeed, YPos - YSpeed, Rnd() * 2 - 1, Rnd() * 2 - 1, 3);
		}
		for(i = 0; i <= 15; ++i){
			auto nFire = new Fire();
			nFire->Init(XPos - XSpeed, YPos - YSpeed, Rnd() * 4 - 2, Rnd() * 4 - 2);
			FrmScreen.AddObject(nFire);
		}
		PlaySound(dsExplosion);
		FrmScreen.MakeQuake(30);
	}
	if (FrmScreen.GetMapLine((XPos), (YPos), XSpeed, YSpeed) != 0) {
		XSpeed = -XSpeed / 1.5;
		YSpeed = -YSpeed / 1.5;
	}
	if (FrmScreen.GetMap(XPos + XSpeed, YPos - 2) != 0) {
		HLeft = HLeft - 10;
		XSpeed = -XSpeed / 2;
	}
	if (FrmScreen.GetMap(XPos + XSpeed, YPos + YSpeed) != 0) { HLeft = 0;}
	if (FrmScreen.isPlayer(XPos, YPos) != 0) { HLeft = 0;}
}

void NukeGrenade::Render(){
	FrmScreen.DrawPlPic(ddShell, XPos - 5, YPos - 3, Rotation / 3 + 15);
}
