/*
 * NukeMissile.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "NukeMissile.h"
#include "aux.h"
#include "IBomb.h"

NukeMissile::NukeMissile() {
	// TODO Auto-generated constructor stub

}

NukeMissile::~NukeMissile() {
	// TODO Auto-generated destructor stub
}


void NukeMissile::Init(double X){
	XPos = X;
	YPos = -1000;
	YSpeed = 10;
}

void NukeMissile::TimeTab(){
	YPos = YPos + YSpeed;
	FrmScreen.MakeSmoke(XPos, YPos - 30, 0., Rnd(), 1);
	if (FrmScreen.GetMapLine((XPos), (YPos), 0, (YSpeed)) != 0) {
		FrmScreen.RemoveObject(this);
		FrmScreen.HugeExplosion((XPos), (YPos), 92, 50);
		FrmScreen.HugeExplosion((XPos), (YPos) - 20, 92, 50);
		FrmScreen.HugeExplosion((XPos), (YPos) - 40, 92, 50);
		PlaySound(dsExplosion);

		IBomb* nBomb;
		nBomb = new IBomb();
		nBomb->Init((XPos), (YPos), 0);
		FrmScreen.AddObject(nBomb);
		FrmScreen.MakeQuake(40);
		long i;
		;
		for(i = 0; i <= 3; ++i){
			nBomb = new IBomb();
			nBomb->Init((XPos) - i * 20 - 20, (YPos), i * 15);
			FrmScreen.AddObject(nBomb);
			;
			nBomb = new IBomb();
			nBomb->Init((XPos) + i * 20 + 20, (YPos), i * 15);
			FrmScreen.AddObject(nBomb);
		}
	}

}

void NukeMissile::Render(){
	FrmScreen.DrawPlPic(ddNuke, XPos - 10, YPos - 40, 0);
}
