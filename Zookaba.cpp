/*
 * Zookaba.cpp
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#include "Zookaba.h"
#include "aux.h"

Zookaba::Zookaba() {
	// TODO Auto-generated constructor stub

}

Zookaba::~Zookaba() {
	// TODO Auto-generated destructor stub
}

void Zookaba::Init(double X, double Y, double Xs, double Ys) {
	XPos = X;
	YPos = Y;
	XSpeed = Xs;
	YSpeed = Ys;
}

void Zookaba::TimeTab() {
	XPos = XPos + XSpeed;
	YPos = YPos + YSpeed;
	FrmScreen.MakeSmoke(XPos - XSpeed, YPos - YSpeed, -XSpeed / 1.5 + Rnd() * 2 - 1, -YSpeed / 1.5 + Rnd() * 2 - 1, 0);

	if (FrmScreen.GetMapLine((XPos), (YPos), XSpeed, YSpeed) != 0) {
		FrmScreen.RemoveObject(this);
		FrmScreen.HugeExplosion((XPos), (YPos), 30, 10);
		PlaySound(dsExplosion);
	}
	if (FrmScreen.isPlayer((XPos), (YPos))!= 0) {
		FrmScreen.RemoveObject(this);
		FrmScreen.HugeExplosion((XPos), (YPos), 30, 10);
		PlaySound(dsExplosion);
	}
}

void Zookaba::Render() {
	FrmScreen.DrawPlPic(ddMissile, XPos - 3, YPos - 3, 0);
	FrmScreen.DrawPlPic(ddMissile, XPos - 3 - XSpeed / 2, YPos - 3 - YSpeed / 2, 1);
	FrmScreen.DrawPlPic(ddMissile, XPos - 3 - XSpeed, YPos - 3 - YSpeed, 1);

}


