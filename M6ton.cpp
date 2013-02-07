/*
 * M6ton.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "M6ton.h"
#include "aux.h"
#include "SolidLine.h"

struct Position{
	double X, Y;
};

M6ton::M6ton() {
	// TODO Auto-generated constructor stub

}

M6ton::~M6ton() {
	// TODO Auto-generated destructor stub
}

void M6ton::Fire(double X, double Y, double XAim, double YAim, int Turn,
		bool isFire) {
    if (!isFire) { return;;}
    if (MyPlayer->getItem(1) < 100 || MyPlayer->getItem(3) < 2) { return;;}
    MyPlayer->setItem (1, 0);
    MyPlayer->CalcItem(3, -2);
    long i; Position Speed; Position Pos;
    Speed.X = XAim / 10 * Turn;
    Speed.Y = YAim / 10;
    Pos.X = X + XAim / 3 * Turn;
    Pos.Y = Y + YAim / 3;
    for(i = 0; i <= 100; ++i){
        Pos.X = Pos.X + Speed.X;
        Pos.Y = Pos.Y + Speed.Y;
        if (FrmScreen.GetMap((Pos.X), (Pos.Y)) || FrmScreen.isPlayer((Pos.X), (Pos.Y))) { break; }
    }
    PlaySound(dsLaser);

    auto nLine = new SolidLine();
    nLine->Init(X, Y, Pos.X, Pos.Y, 3, 4);
    FrmScreen.AddObject(nLine);

    if (i == 101) { return;;}
    FrmScreen.Explosion((Pos.X), (Pos.Y), 1, 5, 20);
    FrmScreen.MakeSmoke((Pos.X), (Pos.Y), -Speed.X, -Speed.Y);

}


