/*
 * Flashbang.cpp
 *
 *  Created on: 8 feb 2013
 *      Author: mattias
 */

#include "Flashbang.h"
#include "aux.h"
#include "SolidLine.h"
struct Position{
	double X, Y;
};

Flashbang::Flashbang() {

}

Flashbang::~Flashbang() {
}

void Flashbang::Fire(double X, double Y, double XAim, double YAim, int Turn,
		bool isFire) {
	if (!isFire) { return;;}
	Position Pos;
	long i;
//	long CurrentRot;
	Pos.X = X;
	Pos.Y = Y + 10;
	for(i = 0; i <= 10; ++i){
//		FrmScreen.DrawPlPic(ddFlashbang, Pos.X - 2, Pos.Y, CurrentRot);
		auto nLine = new SolidLine;
		auto oPos = Pos;
		Pos.Y = Pos.Y + 6;
		auto ti = (int)(Rnd() * 3);
		if (ti <= 0){
//			CurrentRot = Rnd() * 2;
		} else if (ti<= 1){
//			CurrentRot = 6 + Rnd() * 2;
			Pos.X = Pos.X - 3;
		} else if (ti <= 2){
//			CurrentRot = 3 + Rnd() + 2;
			Pos.X = Pos.X + 3;
		}
		nLine->Init(oPos.X, oPos.Y, Pos.X, Pos.Y, 1, 2);
		frmScreen.AddObject(nLine);
		if (FrmScreen.GetMap(Pos.X, Pos.Y)) {
			FrmScreen.Explosion(Pos.X, Pos.Y, 1, 5, 5);
			break;
		}
		if (FrmScreen.isPlayer(Pos.X, Pos.Y)) {
			FrmScreen.Explosion(Pos.X, Pos.Y, 1, 5, 5);
			break;
		}
	}

}


