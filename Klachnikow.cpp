/*
 * Klachnikow.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "Klachnikow.h"
#include "common.h"
#include "Musquash.h"

struct Position{
	double X, Y;
};

Klachnikow::Klachnikow() {
	Delay = 0;

}

Klachnikow::~Klachnikow() {
}

void Klachnikow::Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire){
	Delay ++;
	if (Delay < 5) { return;;}
	if (!isFire) { return;;}
	Delay = -2;
//	if (dynamic_cast<*Musquash>(MyPlayer) { Delay = -1;}
	Position Speed; Position Pos; long HitPlayer;
	FrmScreen.DrawPlPic(ddbExp, X - 15 + XAim / 4 * Turn, Y - 15 + YAim / 4, 0);
	PlaySound(dsFire1);
//	PlaySound(dsReload);
	for(int i = 0; i <= 2; ++i){
		Speed.X = XAim / 10 * Turn + Rnd() * 4 - 2;
		Speed.Y = YAim / 10 + Rnd() * 4 - 2;
		Pos.X = X + XAim / 3 * Turn;
		Pos.Y = Y + YAim / 3;
		for(int i2 = 0; i2 <= 20; ++i2){
			HitPlayer = FrmScreen.isPlayer((Pos.X), (Pos.Y));
			if (FrmScreen.GetMap((Pos.X), (Pos.Y)) || HitPlayer) { break;}
			Pos.X = Pos.X + Speed.X;
			Pos.Y = Pos.Y + Speed.Y;
		}
		if (i != 21) {
			if (HitPlayer) {
				FrmScreen.HitPlayer(HitPlayer- 1, 1);
			}
			Pos.X = Pos.X - Speed.X;
			Pos.Y = Pos.Y - Speed.Y;
			FrmScreen.Explosion((Pos.X - Speed.X), (Pos.Y - Speed.Y), 0, 1, 1);
		}
	}
}
